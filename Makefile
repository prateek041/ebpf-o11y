# Get the version of cilium/ebpf from go.mod
# (Helper function to extract module version)
define gomod-version
$(shell go list -m -f '{{.Version}}' $(1))
endef

# Project setup
TARGET_BIN_NAME ?= ebpf-o11y
MAIN_GO_PKG ?= ./cmd/$(TARGET_BIN_NAME)
OUTPUT_BIN ?= bin/$(TARGET_BIN_NAME)

# Tools
TOOLS_DIR := $(shell pwd)/bin
TOOLS_BIN := $(TOOLS_DIR)/bpf2go
BPF2GO_VERSION ?= $(call gomod-version,github.com/cilium/ebpf)

# Default target executed when you just run `make`
.DEFAULT_GOAL := build

# Add bin directory to PATH for Make commands
export PATH := $(TOOLS_DIR):$(PATH)

# Target to install necessary tools
.PHONY: prereqs
prereqs: $(TOOLS_BIN)

# Rule to install bpf2go if missing or version changes
# Uses a marker file containing the version
$(TOOLS_BIN): go.mod go.sum
	@echo "+++ Installing bpf2go $(BPF2GO_VERSION) to $(TOOLS_DIR)..."
	@mkdir -p $(TOOLS_DIR)
	@# Install the tool
	@GOBIN=$(TOOLS_DIR) go install github.com/cilium/ebpf/cmd/bpf2go@$(BPF2GO_VERSION)
	@echo "bpf2go installation complete."

# Target to generate eBPF code
.PHONY: generate
generate: prereqs
	@echo "+++ Generating eBPF code..."
	@# Run go generate recursively from the project root
	@go generate ./...

# Target to build the Go application
.PHONY: build
build: generate
	@echo "+++ Building Go application $(OUTPUT_BIN)..."
	@# Build the main Go package
	@go build -o $(OUTPUT_BIN) $(MAIN_GO_PKG)
	@echo "Build complete: $(OUTPUT_BIN)"

# Target to run the application (optional)
.PHONY: run
run: build
	@echo "+++ Running $(OUTPUT_BIN)..."
	@sudo $(OUTPUT_BIN) # eBPF usually requires root

# Target to clean generated files and binaries
.PHONY: clean
clean:
	@echo "+++ Cleaning generated files and binaries..."
	@# Remove generated Go files and object files using find
	@find ./pkg -name '*_bpf*.go' -delete
	@find ./pkg -name '*_bpf*.o' -delete
	@# Remove the compiled binary
	@rm -f $(OUTPUT_BIN)
	@echo "Clean complete."

# Target to format Go code
.PHONY: fmt
fmt:
	@echo "+++ Formatting Go code..."
	@go fmt ./...

# Target to run linters (requires golangci-lint installed)
# You might want to add golangci-lint to prereqs using go install
.PHONY: lint
lint:
	@echo "+++ Linting Go code..."
	@golangci-lint run ./... || echo "Linting finished (may have errors)."

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make prereqs    - Install necessary build tools (bpf2go)."
	@echo "  make generate   - Generate eBPF Go bindings."
	@echo "  make build      - Generate eBPF code and build the Go application (default)."
	@echo "  make run        - Build and run the Go application (requires sudo)."
	@echo "  make clean      - Remove generated files and the compiled binary."
	@echo "  make fmt        - Format Go source code."
	@echo "  make lint       - Run golangci-lint."
	@echo "  make help       - Show this help message."
