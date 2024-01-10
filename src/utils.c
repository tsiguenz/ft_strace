#include "ft_strace.h"
#include <sys/uio.h>  // process_vm_readv

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

bool get_str_from_process(int pid, uint64_t address, char *arg) {
  ssize_t      nread;
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base  = arg;
  local[0].iov_len   = MAX_LEN_STR_ARG;
  remote[0].iov_base = (void *) address;
  remote[0].iov_len  = MAX_LEN_STR_ARG;

  nread = process_vm_readv(pid, local, 1, remote, 1, 0);
  return (nread < 0);
}
