package main

import (
	"fmt"
	"log"

	bpf "github.com/prateek041/ebpf-o11y/pkg/http"
)

func main() {
	fmt.Println("Starting the eBPF observability program...")

	// list of programs to load
	// bpf.LoadXDP()
	bpf.LoadUProbe()

	log.Println("Program Finished")
}
