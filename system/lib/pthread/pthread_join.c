/*
 * Copyright 2021 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#include "pthread_impl.h"
#include <pthread.h>

extern int __pthread_join_js(pthread_t thread, void **retval);

int __pthread_join(pthread_t thread, void **retval) {
  if (thread->self != thread) {
    // attempt to join a thread which does not point to a valid thread, or does
    // not exist anymore.
    return ESRCH;
  }
  // TODO(sbc): IIUC __pthread_join_js currently doesn't handle the case
  // when the thread becomes detached *during* the join.  This pre-check
  // can potentially be removed once it does.
  if (emscripten_atomic_load_u32((void*)&thread->detach_state) == DT_DETACHED) {
    // The thread is already detached and therefor not joinable
    return EINVAL;
  }
  if (thread == __pthread_self()) {
    // thread is attempting to join to itself.
    return EDEADLK;
  }
  return __pthread_join_js(thread, retval);
}

// Taken directly from system/lib/libc/musl/src/thread/pthread_join.c
int __pthread_tryjoin_np(pthread_t t, void **res)
{
  return t->detach_state==DT_JOINABLE ? EBUSY : __pthread_join(t, res);
}

weak_alias(__pthread_join, emscripten_builtin_pthread_join);
weak_alias(__pthread_tryjoin_np, pthread_tryjoin_np);
weak_alias(__pthread_join, pthread_join);
