#include <ft_strace.h>

const char *prog_name;

int main(int argc, char **argv) {
  prog_name = argv[0];
  if (argc != 2)
    FATAL("Bad number of arguments\n");
  pid_t child = fork();
  if (child < 0)
    FATAL("%s\n", strerror(errno));
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execve(argv[1], argv + 1, NULL);
    FATAL("%s\n", strerror(errno));
  }
  struct user_regs_struct regs;
  int64_t                 syscall;
  ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_EXITKILL);
  while (42) {
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    if (waitpid(child, 0, 0) == -1)
      FATAL("waitpid()1 fail\n");
    ptrace(PTRACE_GETREGS, child, 0, &regs);
    syscall = regs.orig_rax;
    fprintf(stderr, "%ld(%lld, %lld, %lld, %lld, %lld, %lld)", syscall,
            regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9);

    // syscall out
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    if (waitpid(child, 0, 0) == -1)
      FATAL("waitpid()2 fail\n");
    if (ptrace(PTRACE_GETREGS, child, 0, &regs) == -1)
      fprintf(stderr, " = %lld\n", regs.rax);
  }
  return EXIT_SUCCESS;
}
