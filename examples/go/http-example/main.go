package main

import (
	"fmt"
	"log"
	"net/http"
)

func healthHandler(rw http.ResponseWriter, r *http.Request) {
	fmt.Fprint(rw, "Health server check")
}

func main() {
	fmt.Println("Serve HTTP function")
	http.HandleFunc("/", healthHandler)

	port := ":9090"

	if err := http.ListenAndServe(port, nil); err != nil {
		log.Fatal("Error starting server", err)
	}
}
