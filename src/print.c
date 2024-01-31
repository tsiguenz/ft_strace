#include "ft_strace.h"

void print_regs(int pid, union user_regs_t regs, struct iovec io) {
  if (io.iov_len == sizeof(regs.regs64)) {
    struct x86_64_user_regs_struct current_regs = regs.regs64;
    syscall_t                      syscall = syscalls_64[current_regs.orig_rax];
    printf("pid = %d\n", pid);
    printf("syscall = %lu, %s\n", current_regs.orig_rax, syscall.name);
    printf("rdi = 0x%lx\n", current_regs.rdi);
    printf("rsi = 0x%lx\n", current_regs.rsi);
    printf("rdx = 0x%lx\n", current_regs.rdx);
    printf("rcx = 0x%lx\n", current_regs.rcx);
    printf("r8 = 0x%lx\n", current_regs.r8);
    printf("r9 = 0x%lx\n", current_regs.r9);
  }
}

void print_in_kernel_space(int pid, struct x86_64_user_regs_struct registers,
                           syscall_t syscall) {
  char str_params[MAX_ARGS][MAX_LEN_STR_ARG] = {0};
  set_str_params_to_regs(pid, &registers, syscall.format, str_params);
  fprintf(stderr, syscall.format, syscall.name, registers.rdi, registers.rsi,
          registers.rdx, registers.rcx, registers.r8, registers.r9);
}

void print_out_kernel_space(struct x86_64_user_regs_struct registers,
                            bool is_32_bits, int32_t ret_32) {
  int64_t ret_val = is_32_bits ? ret_32 : (int64_t) registers.rax;
  if (ret_val > -1 || ret_val < -4095) {
    if (ret_val > 10000 || ret_val < -10000) {
      if (is_32_bits)
        fprintf(stderr, ") = 0x%x\n", (int32_t) ret_val);
      else
        fprintf(stderr, ") = 0x%lx\n", ret_val);
    } else {
      fprintf(stderr, ") = %ld\n", ret_val);
    }
  } else {
    // case when syscall-exit-stop because signal was caught
    // 512 to 530 are linux errnos and don't have description in strerror
    if ((-ret_val > MAX_LEN_ERRNO && -ret_val < 512) || -ret_val > 530)
      fprintf(stderr, ") = ? Unknow errno %ld\n", -ret_val);
    if (-ret_val >= 512 && -ret_val <= 530) {
      fprintf(stderr, ") = ? %s\n", errno_ent[-ret_val]);
    } else {
      fprintf(stderr, ") = -1 %s (%s)\n", errno_ent[-ret_val],
              strerror(-ret_val));
    }
  }
}
