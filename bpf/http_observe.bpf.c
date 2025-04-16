#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

// SEC macro defining which user-space function we want to attach
// track_request function to. We are attaching it to ServeHTTP
// standard function in the net/http library. Which get triggers
// on multiple occasions like.
// - When user hits our server (DefaultServeMux.ServeHTTP)
// - A Handler serves request for a route.
// You can read the net/http documentation for more.
SEC("uprobe/healthHandler")
int track_request() {
  // For simplicity,
  bpf_printk("serveHTTP triggered");
  return 0;
}

char __license[] SEC("license") = "Dual MIT/GPL";
