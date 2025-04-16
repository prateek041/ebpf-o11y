package main

import (
	"fmt"
	"log"

	bpf "github.com/prateek041/ebpf-o11y/pkg/xdp"
)

func main() {
	fmt.Println("Starting the eBPF observability program...")

	// list of programs to load
	bpf.LoadXDP()

	log.Println("Program Finished")
}
