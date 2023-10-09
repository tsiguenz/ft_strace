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
    execve(argv[1], argv + 1, NULL);
    FATAL("%s\n", strerror(errno));
  }
  int status;
  ptrace(PTRACE_SEIZE, child, 0, PTRACE_O_TRACESYSGOOD);
  ptrace(PTRACE_INTERRUPT, child, 0, 0);
  while (42) {
    status = 0;
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    if (waitpid(child, &status, 0) == -1)
      FATAL("waitpid() fail\n");
    if (WIFEXITED(status))
      printf("exited, status=%d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
      printf("killed by signal %d\n", WTERMSIG(status));
    else if (WIFSTOPPED(status))
      printf("stopped by signal %d\n", WSTOPSIG(status));
    else if (WIFCONTINUED(status))
      printf("continued\n");
  }
  return EXIT_SUCCESS;
}
