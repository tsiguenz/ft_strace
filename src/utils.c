#include "ft_strace.h"
#include "syscalls_64.h"
#include "syscalls_32.h"

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

bool execve_is_done(bool *in_kernel_space,
                   const char *syscall_name) {
  static bool execve_is_done = false;
  if (in_kernel_space == NULL || syscall_name == NULL)
    return execve_is_done;
  if (execve_is_done == false && strcmp("execve", syscall_name) == 0) {
    execve_is_done           = true;
    *in_kernel_space = true;
  }
  return execve_is_done;
}

syscall_t set_syscall_64(uint64_t syscall_number) {
      return (syscall_number < SYSCALLS_NBR_64)
               ? syscalls_64[syscall_number]
               : (syscall_t) UNRECONGNIZE_SYSCALL;
}

syscall_t set_syscall_32(uint64_t syscall_number) {
      return (syscall_number < SYSCALLS_NBR_32)
               ? syscalls_32[syscall_number]
               : (syscall_t) UNRECONGNIZE_SYSCALL;
}
