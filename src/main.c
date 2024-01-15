#include <errno.h>
#include "ft_strace.h"
#include "syscalls_x86_64.h"
#include "errno_ent.h"

const char      *prog_name;
syscall_x86_64_t syscalls_x86_64[] = {SYSCALLS_ENT_X86_64};
// TODO: add i386 syscalls
syscall_x86_64_t syscalls_i386[] = {SYSCALLS_ENT_X86_64};
char* errno_ent[] = {ERRNO_ENT};

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
