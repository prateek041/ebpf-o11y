#include <bpf/bpf_helpers.h>
#include <linux/bpf.h>

// SEC macro defining which user-space function we want to attach
// track_request function to. We are attaching it to healthHandler
// function in the source of sample http server. Which get triggers
// on multiple occasions like.
// - A Handler serves request for a route.
// You can read the net/http documentation for more.

SEC("uprobe/readContinuedLineSlice")
int track_request(struct pt_regs *ctx) {
  // For simplicity,
  bpf_printk("serveHTTP triggered");
  return 0;
}

char __license[] SEC("license") = "Dual MIT/GPL";
