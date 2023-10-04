#include <ft_strace.h>

int main(void) {
  pid_t child = fork();
  if (child < 0) {
    fprintf(stderr, "fork() error\n");
    return EXIT_FAILURE;
  }
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl("/bin/ls", "/bin/ls", NULL);
  } else {
    if (wait(NULL) == -1) {
      fprintf(stderr, "wait() error\n");
      return EXIT_FAILURE;
    }
    ptrace(PTRACE_SEIZE, child, 0, 0);
  }

  return EXIT_SUCCESS;
}
