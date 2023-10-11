#include <ft_strace.h>

const char *prog_name;

int main(int argc, char **argv) {
  (void) argc;
  prog_name   = argv[0];
  pid_t child = fork();
  if (child < 0)
    FATAL("%s\n", strerror(errno));
  if (child == 0) {
    execve(argv[1], argv + 1, NULL);
    FATAL("%s\n", strerror(errno));
  }
  int status;
  ptrace(PTRACE_SEIZE, child, 0, 0);
  ptrace(PTRACE_INTERRUPT, child, 0, 0);
  printf("errno = %d\n", errno);
  for (int i = 0; 42; i++) {
    status = 0;
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    if (waitpid(child, &status, 0) == -1)
      FATAL("%s\n", strerror(errno));
    if (WIFEXITED(status)) {
      printf("?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      exit(WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      /* Gather system call arguments */
      struct iovec io;
      printf("errno = %d\n", errno);
      if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, &io) == -1)
        FATAL("%s\n", strerror(errno));
      struct user_regs_struct *regs = (struct user_regs_struct *) io.iov_base;
      (void) regs;
      (void) i;
      printf("io.iov_len = %zu\n", io.iov_len);
      printf("io.iov_base = %p\n", io.iov_base);
      printf("errno = %d\n", errno);
      //uint64_t                 syscall = regs->rax;
      // (void) syscall;
      //       if (!(i % 2))
      //         fprintf(stderr, "%lld\n", regs->rax);
      //       else
      //         fprintf(stderr, "%ld(%lld, %lld, %lld) = ", syscall, regs->rdi,
      //                 regs->rsi, regs->rdx);
    } else if (WIFCONTINUED(status)) {
      printf("continued\n");
    }
  }
  return EXIT_SUCCESS;
}
