#include "ft_strace.h"

void print_regs(int pid, union user_regs_t regs, struct iovec io) {
  if (io.iov_len == sizeof(regs.regs64)) {
    struct x86_64_user_regs_struct current_regs = regs.regs64;
    syscall_x86_64_t syscall = syscalls_x86_64[current_regs.orig_rax];
    if (!strcmp(syscall.name, "write")) {
      printf("pid = %d\n", pid);
      printf("syscall = %lu, %s\n", current_regs.orig_rax, syscall.name);
      printf("rdi = 0x%lx\n", current_regs.rdi);
      printf("rsi = 0x%lx\n", current_regs.rsi);
      printf("rdx = 0x%lx\n", current_regs.rdx);
      printf("rcx = 0x%lx\n", current_regs.rcx);
      printf("r8 = 0x%lx\n", current_regs.r8);
      printf("r9 = 0x%lx\n", current_regs.r9);
      char arg[MAX_LEN_STR_ARG + 1] = {0};
      if (!get_str_from_process(pid, current_regs.rsi, arg))
        printf("arg = %s\n", arg);
    }
  }
}

int get_index_of_str_param(char *syscall_format) {
  printf("format = %s", syscall_format);
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

void set_str_params(int pid, struct x86_64_user_regs_struct *registers,
                    char *syscall_format,
                    char  str_params[MAX_ARGS][MAX_LEN_STR_ARG]) {
  (void) syscall_format;
  while (1) {
    int return_value = 0;
    int i            = 1;  //get_index_of_str_param(syscall_format);
    printf("index = %d\n", get_index_of_str_param("%s(%d %s %d %s)"));
    printf("index = %d\n", get_index_of_str_param("%s(%d %s %d %s)"));
    printf("index = %d\n", get_index_of_str_param("%s(%d %s %d %s)"));
    printf("2index = %d\n", get_index_of_str_param("%s(%s %d %s %d)"));
    printf("2index = %d\n", get_index_of_str_param("%s(%s %d %s %d)"));
    printf("2index = %d\n", get_index_of_str_param("%s(%s %d %s %d)"));
    uint64_t *reg = NULL;
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
      FATAL("%s: process_vm_readv(): %s\n", prog_name, strerror(errno));
    *reg = (uint64_t) str_params[i];
    return;
  }
}

void print_in_kernel_space_x86_64(int                            pid,
                                  struct x86_64_user_regs_struct registers,
                                  syscall_x86_64_t               syscall) {
  char str_params[MAX_ARGS][MAX_LEN_STR_ARG] = {0};
  set_str_params(pid, &registers, syscall.format, str_params);
  fprintf(stderr, syscall.format, syscall.name, registers.rdi, registers.rsi,
          registers.rdx, registers.rcx, registers.r8, registers.r9);
}

void print_out_kernel_space_x86_64(struct x86_64_user_regs_struct registers) {
  fprintf(stderr, ") = %lu\n", registers.rax);
}

void print_in_kernel_space_i386(struct i386_user_regs_struct registers,
                                syscall_x86_64_t             syscall) {
  fprintf(stderr, syscall.format, syscall.name, registers.ebx, registers.ecx,
          registers.edx, registers.esi, registers.edi, registers.ebp);
}

void print_out_kernel_space_i386(struct i386_user_regs_struct registers) {
  fprintf(stderr, ") = %u\n", registers.eax);
}
