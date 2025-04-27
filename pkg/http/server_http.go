package bpf

import (
	"fmt"
	"log"

	"github.com/cilium/ebpf/link"
	"github.com/cilium/ebpf/rlimit"
)

//go:generate bpf2go -target bpfel,bpfeb -cc clang server ../../bpf/http_observe.bpf.c  -- -I../../bpf/bpfcore/ -Wall -O2

// memory offset of the function we are attaching UProbe to.
const SymbolName = "main.healthHandler"

// use `nm` to find the memory offset of your function.

func LoadUProbe() {
	if err := rlimit.RemoveMemlock(); err != nil {
		log.Fatal("error expanding the memory needs for the program", err)
	}

	var bpfObject serverObjects
	if err := loadServerObjects(&bpfObject, nil); err != nil {
		log.Fatal("error loading eBPF program objects", err)
	}

	defer bpfObject.Close()

	// In order to attach a uprobe, we first need the executable loaded.

	// currently we are hard-coding binary path, later on we will find it's path using
	// proc subsystem for runtime instrumentation, that way, once we write UProbe for
	// a function like ServeHTTP, we can re-use it for any binary running on our system,
	// that is written in Go and uses that standard library function.
	programPath := "examples/go/http-example/http_server"
	exe, err := link.OpenExecutable(programPath)
	if err != nil {
		log.Fatal("Unable to open executable", err)
	}

	// Attach a Uprobe to the given Symbol in our Binary.
	_, err = exe.Uprobe(SymbolName, bpfObject.serverPrograms.TrackRequest, &link.UprobeOptions{})
	if err != nil {
		log.Fatal("error attaching uprobe")
	}
	fmt.Println("Program Loaded successfully")

	// We need to make sure the program doesn't exit immediately, there are
	// multiple ways of doing it, but since we do not have maps for this example
	// implementation, we will just loop infinitely.
	log.Println("Waiting indefinitely (or until maps are read)... Press Ctrl+C to exit.")
	for {
	}

	// Once the programs are loaded and running, we can check the traces being generated
	// by `bpf_printk` function by doing `sudo cat /sys/kernel/tracing/trace_pipe`, since
	// the function writes logs into that pseudo file.
}
