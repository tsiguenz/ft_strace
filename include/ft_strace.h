#ifndef FT_STRACE_H
#define FT_STRACE_H

#include <elf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>

#define FATAL(...)                                                             \
  do {                                                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  } while (0)

typedef struct syscall_x86_64_s {
  char *name;
  char *format;
} syscall_x86_64_t;

#endif  // FT_STRACE_H
