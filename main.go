package main

import (
	"fmt"

	"github.com/prateek041/ebpf-o11y/pkg/xdp"
)

func main() {
	fmt.Println("Starting the program")
	xdp.LoadXDP()
}
