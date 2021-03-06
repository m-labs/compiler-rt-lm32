//===-- sanitizer_posix.cc ------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is shared between AddressSanitizer and ThreadSanitizer
// run-time libraries and implements POSIX-specific functions from
// sanitizer_libc.h.
//===----------------------------------------------------------------------===//
#if defined(__linux__) || defined(__APPLE__)

#include "sanitizer_common.h"
#include "sanitizer_libc.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

namespace __sanitizer {

int GetPid() {
  return getpid();
}

void *MmapOrDie(uptr size, const char *mem_type) {
  size = RoundUpTo(size, kPageSize);
  void *res = internal_mmap(0, size,
                            PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANON, -1, 0);
  if (res == (void*)-1) {
    Report("ERROR: Failed to allocate 0x%zx (%zd) bytes of %s\n",
           size, size, mem_type);
    CHECK("unable to mmap" && 0);
  }
  return res;
}

void UnmapOrDie(void *addr, uptr size) {
  if (!addr || !size) return;
  int res = internal_munmap(addr, size);
  if (res != 0) {
    Report("ERROR: Failed to deallocate 0x%zx (%zd) bytes at address %p\n",
           size, size, addr);
    CHECK("unable to unmap" && 0);
  }
}

int internal_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int res = vsscanf(str, format, args);
  va_end(args);
  return res;
}

}  // namespace __sanitizer

#endif  // __linux__ || __APPLE_
