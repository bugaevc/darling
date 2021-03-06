#define __SYSCALL_32BIT_ARG_BYTES 16
#include "SYS.h"

#ifndef SYS_quotactl
#error "SYS_quotactl not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__x86_64__)
__SYSCALL2(quotactl, quotactl, 4, cerror_nocancel)
#endif

