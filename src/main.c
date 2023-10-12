#include "ft_strace.h"
#include "registers.h"
#include "syscalls.h"

const char *prog_name;
syscalls_t  syscalls[] = {SYSCALLS_ENT_X86_64};

int trace_syscalls(int child) {
  int status;
  for (int i = 0; 42; i++) {
    status = 0;
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    if (waitpid(child, &status, 0) == -1)
      FATAL("%s: %s\n", prog_name, strerror(errno));
    if (WIFEXITED(status)) {
      // problem somethimes exit with no such process
      fprintf(stderr, "?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      fprintf(stderr, "errno: %d = %s\n", errno, strerror(errno));
      exit(WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      union user_regs_t regs;
      struct iovec      io = {
               .iov_base = &regs,
               .iov_len  = sizeof(regs),
      };
      if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, &io) == -1)
        FATAL("%s: %s\n", prog_name, strerror(errno));
      if ((i % 2))
        fprintf(stderr,
                "%s(%llu, %llu, %llu) = ", syscalls[regs.regs64.orig_rax].name,
                regs.regs64.rdi, regs.regs64.rsi, regs.regs64.rdx);
      else
        fprintf(stderr, "%llu\n", regs.regs64.rax);
    } else if (WIFCONTINUED(status)) {
      printf("continued\n");
    }
  }
}

int strace(char **argv) {
  pid_t child = fork();
  if (child < 0)
    FATAL("%s: %s\n", prog_name, strerror(errno));
  if (child == 0) {
    execve(argv[1], argv + 1, NULL);
    FATAL("%s: %s\n", prog_name, strerror(errno));
  }
  ptrace(PTRACE_SEIZE, child, 0, 0);
  ptrace(PTRACE_INTERRUPT, child, 0, 0);
  // do something with signals
  return trace_syscalls(child);
}

int main(int argc, char **argv) {
  prog_name = argv[0];
  if (argc == 1)
    FATAL("%s: must have PROG [ARGS]\n", prog_name);
  return strace(argv);
}
