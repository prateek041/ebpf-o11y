#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include "bpfcore/utils.h"


enum { W3C_KEY_LENGTH = 11, W3C_VAL_LENGTH = 55 };

// SEC macro defining which user-space function we want to attach
// track_request function to. We are attaching it to healthHandler
// function in the source of sample http server. Which get triggers
// on multiple occasions like.
// - A Handler serves request for a route.
// You can read the net/http documentation for more.

SEC("uprobe/readContinuedLineSlice")
int track_request(struct pt_regs *ctx) {
  // For simplicity,
  // bpf_printk("HTTP header read: Len =  %d", len);
  __u64 len = (__u64)GO_PARAM2(ctx);
  __u8 *buf = (__u8 *)GO_PARAM1(ctx);


  bpf_printk("HTTP header read: Len =  %d", len);

  if (len > (11 + 55)) {
    __u8 temp[68];
    bpf_probe_read(temp, sizeof(temp), buf);
    // bpf_printk(*temp);
    bpf_printk("REACHED HERE");
  }

  return 0;
}

char __license[] SEC("license") = "Dual MIT/GPL";

// SEC("uprobe/readContinuedLineSlice")
// int beyla_uprobe_readContinuedLineSliceReturns(struct pt_regs *ctx) {
//     bpf_dbg_printk("=== uprobe/proc readContinuedLineSlice returns === ");
//
//     void *goroutine_addr = GOROUTINE_PTR(ctx);
//     u64 len = (u64)GO_PARAM2(ctx);
//     u8 *buf = (u8 *)GO_PARAM1(ctx);
//
//     if (len >= (W3C_KEY_LENGTH + W3C_VAL_LENGTH + 2)) {
//         u8 temp[W3C_KEY_LENGTH + W3C_VAL_LENGTH + 2];
//         bpf_probe_read(temp, sizeof(temp), buf);
//         bpf_dbg_printk("goroutine_addr %lx", goroutine_addr);
//         go_addr_key_t g_key = {};
//         go_addr_key_from_id(&g_key, goroutine_addr);
//
//         connection_info_t *existing =
//         bpf_map_lookup_elem(&ongoing_server_connections, &g_key); if
//         (existing) {
//             if (!bpf_memicmp((const char *)temp, "traceparent: ",
//             W3C_KEY_LENGTH + 2)) {
//                 server_http_func_invocation_t inv = {};
//                 decode_go_traceparent(
//                     temp + W3C_KEY_LENGTH + 2, inv.tp.trace_id,
//                     inv.tp.parent_id, &inv.tp.flags);
//                 bpf_dbg_printk("Found traceparent in header %s", temp);
//                 bpf_map_update_elem(&ongoing_http_server_requests, &g_key,
//                 &inv, BPF_ANY);
//             }
//         }
//     }
//
//     return 0;
// }

/*
 * bpf_probe_read
 *
 * 	For tracing programs, safely attempt to read *size* bytes from
 * 	kernel space address *unsafe_ptr* and store the data in *dst*.
 *
 * 	Generally, use **bpf_probe_read_user**\ () or
 * 	**bpf_probe_read_kernel**\ () instead.
 *
 * Returns
 * 	0 on success, or a negative error in case of failure.
 */
// static long (*const bpf_probe_read)(void *dst, __u32 size,
// const void *unsafe_ptr) = (void *)4;
