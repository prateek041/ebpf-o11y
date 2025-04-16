package bpf

import (
	"log"
	"net"
	"os"
	"os/signal"
	"time"

	"github.com/cilium/ebpf/link"
	"github.com/cilium/ebpf/rlimit"
)

//go:generate go run github.com/cilium/ebpf/cmd/bpf2go -target bpfel,bpfeb -cc clang counter ../../bpf/counter.bpf.c  -- -I../../bpf/headers -Wall -O2

func LoadXDP() {
	// remove rlimit for kernel versions <5.11
	if err := rlimit.RemoveMemlock(); err != nil {
		log.Fatal("Error expanding the memory needs of the program", err)
	}

	// load the compiled eBPF files.
	var bpfObject counterObjects
	if err := loadCounterObjects(&bpfObject, nil); err != nil {
		log.Fatal("error loading eBPF program objects", err)
	}
	defer bpfObject.Close()

	ifName := "wlan0" // we are watching wifi connection.
	iface, err := net.InterfaceByName(ifName)
	if err != nil {
		log.Fatal("Error getting interface %s: %s", iface, err)
	}
	link, err := link.AttachXDP(link.XDPOptions{
		Program:   bpfObject.CountPackets,
		Interface: iface.Index,
	})

	if err != nil {
		log.Fatal("Error attaching the eBPF program %s", err)
	}

	defer link.Close()

	log.Printf("Counting incoming packets on %s..", ifName)

	tick := time.Tick(time.Second) // watch every second
	stop := make(chan os.Signal, 5)
	signal.Notify(stop, os.Interrupt) // exit if interrupted

	for {
		select {
		case <-tick:
			var count uint64
			err := bpfObject.PktCount.Lookup(uint32(0), &count)

			if err != nil {
				log.Fatal("Map lookup:", err)
			}
			log.Printf("Received %d packets", count)
		case <-stop:
			log.Print("Received signal, exiting..")
			return
		}
	}

}
