#include "ft_strace.h"
#include "syscalls_64.h"

void disable_signals(void) {
  // restore signals to default
  sigset_t empty;
  sigemptyset(&empty);
  sigprocmask(SIG_SETMASK, &empty, NULL);
  // block int signals
  sigset_t block;
  sigemptyset(&block);
  sigaddset(&block, SIGHUP);
  sigaddset(&block, SIGINT);
  sigaddset(&block, SIGQUIT);
  sigaddset(&block, SIGPIPE);
  sigaddset(&block, SIGTERM);
  sigprocmask(SIG_BLOCK, &block, NULL);
}

bool is_child_call(bool *print, bool *in_kernel_space,
                   const char *syscall_name) {
  if (*print == false && strcmp("execve", syscall_name) == 0) {
    *print           = true;
    *in_kernel_space = true;
  }
  return *print == true;
}

syscall_t set_syscall_64(uint64_t syscall_number) {
      return (syscall_number < SYSCALLS_NBR_64)
               ? syscalls_64[syscall_number]
               : (syscall_t) UNRECONGNIZE_SYSCALL;
}

syscall_t set_syscall_32(uint32_t syscall_number) {
      return (syscall_number < SYSCALLS_NBR_64)
               ? syscalls_32[syscall_number]
               : (syscall_t) UNRECONGNIZE_SYSCALL;
}
