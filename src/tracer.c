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
  if (!execve_is_done(&in_kernel_space, syscall.name))
    return;
  if (in_kernel_space) {
    print_in_kernel_space(pid, current_regs, syscall);
    in_kernel_space = false;
  } else {
    print_out_kernel_space(current_regs);
    in_kernel_space = true;
  }
}

void handle_signal(siginfo_t signal) {
  if (signal.si_code != SI_USER && signal.si_code != SI_KERNEL)
    return;
  char *signo  = signals_abbrev[signal.si_signo];
  char *sicode = signal.si_code == SI_USER ? "SI_USER" : "SI_KERNEL";

  fprintf(stderr,
          "--- SIG%s {si_signo=SIG%s, si_code=%s, si_pid=%d, si_uid=%d} ---\n",
          signo, signo, sicode, signal.si_pid, signal.si_uid);
}

int trace_syscalls(int pid) {
  int       signal = 0;
  siginfo_t sig    = {0};
  disable_signals();
  usleep(100);
  if (ptrace(PTRACE_SEIZE, pid, 0, 0) == -1)
    FATAL("%s: ptrace(SEIZE): %s\n", prog_name, strerror(errno));
  if (ptrace(PTRACE_INTERRUPT, pid, 0, 0) == -1)
    FATAL("%s: ptrace(INTERRUPT): %s\n", prog_name, strerror(errno));
  if (ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1)
    FATAL("%s: ptrace(SYSCALL): %s\n", prog_name, strerror(errno));
  for (; 42;) {
    int status = 0;
    if (waitpid(pid, &status, 0) == -1)
      FATAL("%s: waitpid(): %s\n", prog_name, strerror(errno));
    if (WIFSTOPPED(status)) {
      if (ptrace(PTRACE_GETSIGINFO, pid, 0, &sig) == -1)
        FATAL("%s: ptrace(GETSIGINFO): %s\n", prog_name, strerror(errno));
      signal = WSTOPSIG(status);
      if (sig.si_code == SIGTRAP || sig.si_code == (SIGTRAP | 0x80)) {
        handle_syscall_io(pid);
        signal = 0;
      } else if (execve_is_done(NULL, NULL)) {
        handle_signal(sig);
      }
      if (ptrace(PTRACE_SYSCALL, pid, 0, signal) == -1)
        FATAL("%s: ptrace(SYSCALL): %s\n", prog_name, strerror(errno));
    }
    if (WIFEXITED(status)) {
      int ret_value = WEXITSTATUS(status);
      fprintf(stderr, ") = ?\n+++ exited with %d +++\n", ret_value);
      exit(ret_value);
    }
    if (WIFSIGNALED(status)) {
      char *signal_name = signals_abbrev[WTERMSIG(status)];
      fprintf(stderr, "+++ killed by SIG%s +++\n", signal_name);
      raise(WTERMSIG(status));
      exit(128 + WTERMSIG(status));
    }
  }
}
