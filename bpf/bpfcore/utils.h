// Copyright The OpenTelemetry Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef __UTILS_H__
#define __UTILS_H__

// #pragma clang diagnostic push // Comment out pragma lines for now
// #pragma clang diagnostic ignored "-Wpadded"
// #pragma clang diagnostic ignored "-Wpacked"
// #pragma clang diagnostic ignored "-Wunaligned-access"

// #if defined(__TARGET_ARCH_x86) // Comment out conditional inclusion

#define GO_PARAM1(x) ((void *)(x)->ax)
#define GO_PARAM2(x) ((void *)(x)->bx)
#define GO_PARAM3(x) ((void *)(x)->cx)
#define GO_PARAM4(x) ((void *)(x)->di)
#define GO_PARAM5(x) ((void *)(x)->si)
#define GO_PARAM6(x) ((void *)(x)->r8)
#define GO_PARAM7(x) ((void *)(x)->r9)
#define GO_PARAM8(x) ((void *)(x)->r10)
#define GO_PARAM9(x) ((void *)(x)->r11)
#define GOROUTINE_PTR(x) ((void *)(x)->r14)

// #elif defined(__TARGET_ARCH_arm64) // Comment out ARM64 part

// #define GO_PARAM1(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[0])
// #define GO_PARAM2(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[1])
// #define GO_PARAM3(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[2])
// #define GO_PARAM4(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[3])
// #define GO_PARAM5(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[4])
// #define GO_PARAM6(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[5])
// #define GO_PARAM7(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[6])
// #define GO_PARAM8(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[7])
// #define GO_PARAM9(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[8])
// #define GOROUTINE_PTR(x) ((void *)((PT_REGS_ARM64 *)(x))->regs[28])

// #endif /*defined(__TARGET_ARCH_arm64)*/ // Comment out #endif

#define bpf_clamp_umax(VAR, UMAX) ...

#endif /* __UTILS_H__ */
