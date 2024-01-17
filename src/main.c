#include "errno_ent.h"
#include "ft_strace.h"
#include "syscalls_32.h"
#include "syscalls_64.h"
#include <errno.h>

const char *prog_name;
syscall_t   syscalls_64[] = {SYSCALLS_ENT_64};
syscall_t   syscalls_32[] = {SYSCALLS_ENT_32};
char       *errno_ent[]   = {ERRNO_ENT};

int strace(char **argv, char **envp) {
  pid_t pid = fork();
  if (pid < 0) {
    FATAL("%s: fork(): %s\n", prog_name, strerror(errno));
  }
  if (pid == 0) {
    child_exec(argv, envp);
  }
  return trace_syscalls(pid);
}

int main(int argc, char **argv, char **envp) {
  prog_name = argv[0];
  if (argc == 1) {
    FATAL("%s: must have PROG [ARGS]\n", prog_name);
  }
  return strace(argv, envp);
}
