#include "ft_strace.h"
#include <errno.h>

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
  bool is_64_bits = io.iov_len == sizeof(regs.regs64);
  bool is_32_bits = io.iov_len == sizeof(regs.regs32);
  if (is_64_bits) {
    // print_regs(pid, regs, io);
    struct x86_64_user_regs_struct current_regs   = regs.regs64;
    uint64_t                       syscall_number = current_regs.orig_rax;
    syscall_t                      syscall = set_syscall_64(syscall_number);
    if (!is_child_call(&print, &in_kernel_space, syscall.name))
      return;
    if (in_kernel_space) {
      print_in_kernel_space_64(pid, current_regs, syscall);
      in_kernel_space = false;
    } else {
      print_out_kernel_space_64(current_regs);
      in_kernel_space = true;
    }
  } else if (is_32_bits) {
    struct i386_user_regs_struct current_regs   = regs.regs32;
    uint32_t                     syscall_number = current_regs.orig_eax;
    syscall_t                    syscall = set_syscall_64(syscall_number);
    if (!is_child_call(&print, &in_kernel_space, syscall.name))
      return;
    if (in_kernel_space) {
      print_in_kernel_space_32(current_regs, syscall);
      in_kernel_space = false;
    } else {
      print_out_kernel_space_32(current_regs);
      in_kernel_space = true;
    }
  } else {
    FATAL("%s: Bad architecture\n", prog_name);
  }
}

int trace_syscalls(int pid) {
  int status;
  ptrace(PTRACE_SEIZE, pid, 0, 0);
  ptrace(PTRACE_INTERRUPT, pid, 0, 0);
  disable_signals();
  waitpid(pid, 0, 0);  // child wait when parent is ready
  for (; 42;) {
    status = 0;
    ptrace(PTRACE_SYSCALL, pid, 0, 0);
    if (waitpid(pid, &status, 0) == -1)
      FATAL("%s: waitpid(): %s\n", prog_name, strerror(errno));
    if (WIFEXITED(status)) {
      fprintf(stderr, ") = ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      exit(WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      handle_syscall_io(pid);
    } else if (WIFCONTINUED(status)) {
      printf("continued\n");
    }
  }
}
