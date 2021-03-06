//===----------- shared-lib-test.cc -----------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is a part of AddressSanitizer, an address sanity checker.
//
//===----------------------------------------------------------------------===//
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include <string>

using std::string;

typedef void (fun_t)(int x);

int main(int argc, char *argv[]) {
  string path = string(argv[0]) + "-so.so";
  printf("opening %s ... \n", path.c_str());
  void *lib = dlopen(path.c_str(), RTLD_NOW);
  if (!lib) {
    printf("error in dlopen(): %s\n", dlerror());
    return 1;
  }
  fun_t *inc = (fun_t*)dlsym(lib, "inc");
  if (!inc) return 1;
  printf("ok\n");
  inc(1);
  inc(-1);  // BOOM
  return 0;
}

// Check-Common: {{.*ERROR: AddressSanitizer global-buffer-overflow}}
// Check-Common: {{READ of size 4 at 0x.* thread T0}}
// Check-Common: {{    #0 0x.*}}
// Check-Common: {{    #1 0x.* in main .*shared-lib-test.cc:3[567]}}
