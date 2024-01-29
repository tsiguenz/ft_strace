#include "ft_strace.h"
#include <errno.h>

static bool get_str_from_process(int pid, uint64_t address, char *arg) {
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

static int get_index_of_str_param(char *syscall_format) {
  static char *ptr         = NULL;
  static int   index_param = -1;
  // skip format of the syscall name
  if (index_param == -1) {
    ptr = syscall_format;
    ptr++;
    index_param++;
  }
  while ((ptr = strchr(ptr, '%'))) {
    index_param++;
    if (*++ptr == 's')
      return index_param;
  }
  index_param = -1;
  ptr         = NULL;
  return -1;
}

void set_str_params_to_regs(int pid, struct x86_64_user_regs_struct *registers,
                    char *syscall_format,
                    char  str_params[MAX_ARGS][MAX_LEN_STR_ARG]) {
  while (1) {
    int       return_value = 0;
    int       i            = get_index_of_str_param(syscall_format) - 1;
    uint64_t *reg          = NULL;
    switch (i) {
    case 0:
      reg = &(registers->rdi);
      break;
    case 1:
      reg = &(registers->rsi);
      break;
    case 2:
      reg = &(registers->rdx);
      break;
    case 3:
      reg = &(registers->rcx);
      break;
    case 4:
      reg = &(registers->r8);
      break;
    case 5:
      reg = &(registers->r9);
      break;
    default:
      return;
    }
    return_value = get_str_from_process(pid, *reg, str_params[i]);
    if (return_value)
      reg = NULL;
    *reg = (uint64_t) str_params[i];
  }
}
