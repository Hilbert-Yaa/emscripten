/*
 * Copyright 2016 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main() {
  int rtn = clock_gettime(-1, NULL);
  printf("rtn     : %d\n", rtn);
  printf("errno   : %d\n", errno);
  printf("strerror: %s\n", strerror(errno));
  return 0;
}
