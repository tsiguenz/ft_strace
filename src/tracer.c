#include "ft_strace.h"
#include <errno.h>

static void
set_regs32_to_current_regs(struct x86_64_user_regs_struct *current_regs,
                           struct i386_user_regs_struct   *regs32) {
  current_regs->orig_rax = regs32->orig_eax;
  current_regs->rax      = regs32->eax;
  current_regs->rdi      = regs32->ebx;
  current_regs->rsi      = regs32->ecx;
  current_regs->rdx      = regs32->edx;
  current_regs->rcx      = regs32->esi;
  current_regs->r8       = regs32->edi;
  current_regs->r9       = regs32->ebp;
}

void handle_syscall_io(int pid) {
  static bool       print           = false;
  static bool       in_kernel_space = false;
  union user_regs_t regs;
  struct iovec      io = {
           .iov_base = &regs,
           .iov_len  = sizeof(regs),
  };
  if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &io) == -1)
    FATAL("%s: ptrace(GETREGSET): %s\n", prog_name, strerror(errno));
  bool                           is_64_bits = io.iov_len == sizeof(regs.regs64);
  bool                           is_32_bits = io.iov_len == sizeof(regs.regs32);
  struct x86_64_user_regs_struct current_regs = {0};
  if (!is_64_bits && !is_32_bits)
    FATAL("%s: Bad architecture\n", prog_name);
  if (is_32_bits)
    set_regs32_to_current_regs(&current_regs, &regs.regs32);
  if (is_64_bits)
    current_regs = regs.regs64;
  uint64_t  syscall_number = current_regs.orig_rax;
  syscall_t syscall        = is_64_bits ? set_syscall_64(syscall_number)
                                        : set_syscall_32(syscall_number);
  if (!is_execve(&print, &in_kernel_space, syscall.name))
    return;
  if (in_kernel_space) {
    print_in_kernel_space(pid, current_regs, syscall);
    in_kernel_space = false;
  } else {
    print_out_kernel_space(current_regs);
    in_kernel_space = true;
  }
}

void handler(int signal) { printf("Signal %d is caughed !\n", signal); }

int trace_syscalls(int pid) {
  int       status;
  siginfo_t sig;
  ptrace(PTRACE_SEIZE, pid, 0, 0);
  ptrace(PTRACE_INTERRUPT, pid, 0, 0);
  signal(SIGINT, handler);
  disable_signals();
  for (; 42;) {
    status = 0;
    ptrace(PTRACE_SYSCALL, pid, 0, 0);
    if (waitpid(pid, &status, 0) == -1)
      FATAL("%s: waitpid(): %s\n", prog_name, strerror(errno));
    if (WIFSTOPPED(status)) {
      int signal = WSTOPSIG(status);
      ptrace(PTRACE_GETSIGINFO, pid, 0, &sig);
      printf("is user signal: %d, SIG%s\n", sig.si_code == SI_USER,
             signals_abbrev[signal]);
      // handle_syscall_io(pid);
    } else if (WTERMSIG(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFEXITED(status)) {
      int ret_value = WEXITSTATUS(status);
      fprintf(stderr, ") = ?\n+++ exited with %d +++\n", ret_value);
      exit(ret_value);
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    }
  }
}
