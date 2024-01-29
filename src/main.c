#include "errno_ent.h"
#include "ft_strace.h"
#include "signals_abbrev.h"
#include "syscalls_32.h"
#include "syscalls_64.h"
#include <errno.h>
#include <sys/stat.h>

const char *prog_name;
syscall_t   syscalls_64[]    = {SYSCALLS_ENT_64};
syscall_t   syscalls_32[]    = {SYSCALLS_ENT_32};
char       *errno_ent[]      = {ERRNO_ENT};
char       *signals_abbrev[] = {SIGNALS_ABBREV};

void check_and_set_exec_name(char **exec_name) {
  if (strlen(*exec_name) == 0)
    FATAL("%s: access: error bad file name!\n", prog_name);
  int   is_relative = strchr(*exec_name, '/') != NULL;
  char *path_value  = getenv("PATH");
  while (!is_relative && path_value) {
    char *pos_colon = strchr(path_value, ':');
    if (pos_colon) {
      *pos_colon = '\0';
      pos_colon++;
    }
    char *full_name =
        calloc(strlen(path_value) + strlen(*exec_name) + 2, sizeof(char));
    if (!full_name)
      FATAL("%s: error allocation!\n", prog_name);
    strcpy(full_name, path_value);
    full_name[strlen(path_value)] = '/';
    strcat(full_name, *exec_name);
    if (access(full_name, X_OK) == 0) {
      *exec_name = full_name;
      return;
    }
    free(full_name);
    path_value = pos_colon;
  }
  if (access(*exec_name, X_OK) != 0)
    FATAL("%s: access: error bad file name!\n", prog_name);
  *exec_name = strdup(*exec_name);
  if (*exec_name == NULL)
    FATAL("%s: error allocation!\n", prog_name);
}

int strace(char **argv, char **envp) {
  pid_t pid = fork();
  if (pid < 0) {
    free(argv[1]);
    FATAL("%s: fork(): %s\n", prog_name, strerror(errno));
  }
  if (pid == 0)
    child_exec(argv, envp);
  free(argv[1]);
  if (pid > 0)
    return trace_syscalls(pid);
  return 1;
}

int main(int argc, char **argv, char **envp) {
  prog_name = argv[0];
  if (argc == 1)
    FATAL("%s: must have PROG [ARGS]\n", prog_name);
  check_and_set_exec_name(&argv[1]);
  return strace(argv, envp);
}
