#include "ft_strace.h"

void child_exec(char **argv, char **envp) {
  // wait when the parent is ready
  raise(SIGSTOP);
  execve(argv[1], argv + 1, envp);
  FATAL("%s: execve(): %s\n", prog_name, strerror(errno));
}
