#define __SYSCALL_32BIT_ARG_BYTES 16
#include "SYS.h"

#ifndef SYS_shmsys
#error "SYS_shmsys not defined. The header files libsyscall is building against do not match syscalls.master."
#endif

#if defined(__x86_64__)
__SYSCALL2(__shmsys, shmsys, 4, cerror_nocancel)
#endif

#if defined(__x86_64__)
	.globl	shmsys
		shmsys = __shmsys
#endif

