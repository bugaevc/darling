#define __SYSCALL_32BIT_ARG_BYTES 20
#include "SYS.h"

#ifndef SYS_open_dprotected_np
#error "SYS_open_dprotected_np not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__i386__)
__SYSCALL2(__open_dprotected_np, open_dprotected_np, 5, cerror_nocancel)
#endif

