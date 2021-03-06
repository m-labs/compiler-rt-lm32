//===-- sanitizer_placement_new.h -------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is shared between AddressSanitizer and ThreadSanitizer
// run-time libraries.
//
// The file provides 'placement new'.
// Do not include it into header files, only into source files.
//===----------------------------------------------------------------------===//
#ifndef SANITIZER_PLACEMENT_NEW_H
#define SANITIZER_PLACEMENT_NEW_H

#include "sanitizer_internal_defs.h"

#if __WORDSIZE == 64
inline void *operator new(__sanitizer::uptr sz, void *p) {
  return p;
}
#else
inline void *operator new(__sanitizer::u32 sz, void *p) {
  return p;
}
#endif

#endif  // SANITIZER_PLACEMENT_NEW_H
