#include "ft_strace.h"

void child_exec(char **argv, char **envp) {
  execve(argv[1], argv + 1, envp);
  free(argv[1]);
  FATAL("%s: execve failed!\n", prog_name);
}
