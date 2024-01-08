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
      char arg[43] = {0};
      if (!get_string_from_process(pid, current_regs.rsi, arg))
        printf("arg = %s\n", arg);
    }
  }
}

void print_in_kernel_space_x86_64(int                            pid,
                                  struct x86_64_user_regs_struct registers,
                                  syscall_x86_64_t               syscall) {
  (void) pid;
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
