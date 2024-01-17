#include "errno_ent.h"
#include "ft_strace.h"
#include "syscalls_32.h"
#include "syscalls_64.h"
#include <errno.h>

const char *prog_name;
syscall_t   syscalls_64[] = {SYSCALLS_ENT_64};
syscall_t   syscalls_32[] = {SYSCALLS_ENT_32};
char       *errno_ent[]   = {ERRNO_ENT};

char *check_exec_name(char **exec_name) {
  (void) exec_name;
  char *value = getenv("PATH");
  return value;
}

int strace(char **argv, char **envp) {
  pid_t pid = fork();
  if (pid < 0)
    FATAL("%s: fork(): %s\n", prog_name, strerror(errno));
  if (pid == 0)
    child_exec(argv, envp);
  if (pid > 0)
    return trace_syscalls(pid);
  return 1;
}

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  prog_name = argv[0];
  if (argc == 1)
    FATAL("%s: must have PROG [ARGS]\n", prog_name);
  printf("%s\n", check_exec_name(&argv[1]));
  //   // TODO: get the fullname of prog_name and check it's executable
  //   return strace(argv, envp);
}
