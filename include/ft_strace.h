#ifndef FT_STRACE_H
#define FT_STRACE_H

// for process_vm_readv
#define _GNU_SOURCE
#include <elf.h>
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "registers.h"

#define MAX_LEN_STR_ARG 32
#define MAX_ARGS 6
#define UNRECONGNIZE_SYSCALL                                                   \
  { "unrecognize_syscall", "%s(" }

#define FATAL(...)                                                             \
  do {                                                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  } while (0)

typedef struct syscall_s {
  char *name;
  char *format;
} syscall_t;

extern const char *prog_name;
extern syscall_t   syscalls_64[];
extern syscall_t   syscalls_32[];
extern char       *errno_ent[];
extern char       *signals_abbrev[];

void child_exec(char **argv, char **envp);
void handle_syscall_io(int pid);
int  trace_syscalls(int pid);
void print_regs(int pid, union user_regs_t regs, struct iovec io);
void print_in_kernel_space(int pid, struct x86_64_user_regs_struct registers,
                           syscall_t syscall);
void print_out_kernel_space(struct x86_64_user_regs_struct registers);
bool is_execve(bool *print, bool *in_kernel_space, const char *syscall_name);
void disable_signals(void);
void set_str_params_to_regs(int pid, struct x86_64_user_regs_struct *registers,
                            char *syscall_format,
                            char  str_params[MAX_ARGS][MAX_LEN_STR_ARG]);
syscall_t set_syscall_64(uint64_t syscall_number);
syscall_t set_syscall_32(uint64_t syscall_number);

#endif  // FT_STRACE_H
