#ifndef FT_STRACE_H
#define FT_STRACE_H

// for process_vm_readv
#define _GNU_SOURCE
#include <elf.h>
#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "registers.h"

#define MAX_LEN_STR_ARG 42
#define MAX_ARGS 6

#define FATAL(...)                                                             \
  do {                                                                         \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  } while (0)

typedef struct syscall_x86_64_s {
  char *name;
  char *format;
} syscall_x86_64_t;

extern const char      *prog_name;
extern syscall_x86_64_t syscalls_x86_64[];
extern char*            errno_ent[];

void child_exec(char **argv, char **envp);
void handle_syscall_io(int pid);
int  trace_syscalls(int pid);
void print_regs(int pid, union user_regs_t regs, struct iovec io);
void print_in_kernel_space_x86_64(int pid, struct x86_64_user_regs_struct registers,
                                  syscall_x86_64_t               syscall);
void print_out_kernel_space_x86_64(struct x86_64_user_regs_struct registers);
void print_in_kernel_space_i386(struct i386_user_regs_struct registers,
                                syscall_x86_64_t             syscall);
void print_out_kernel_space_i386(struct i386_user_regs_struct registers);
bool is_child_call(bool *print, bool *in_kernel_space,
                   const char *syscall_name);
void disable_signals(void);

void set_str_params_to_regs(int pid, struct x86_64_user_regs_struct *registers,
                    char *syscall_format,
                    char  str_params[MAX_ARGS][MAX_LEN_STR_ARG]);

#endif  // FT_STRACE_H
