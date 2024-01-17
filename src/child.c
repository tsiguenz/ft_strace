#include "ft_strace.h"

void child_exec(char **argv, char **envp) {
  // wait when the parent is ready
  raise(SIGSTOP);
  // parent need to stat the filename of executable before fork
  execvpe(argv[1], argv + 1, envp);
}

// char *get_path_value(char **envp) {
//   if (!envp)
//     return NULL;
//   while (*envp) {
//     char *value = strchr(*envp, '=');
//     *value      = '\0';
//     value++;
//     if (strcmp("PATH", *envp) == 0) {
//       return value;
//     }
//     envp++;
//   }
//   return NULL;
// }
// 
// char *get_full_name_of_command(char *prog_name, char **envp) { // if (strlen(prog_name) == 0)
//   char *path_value = get_path_value(envp);
//   while (path_value) {
//     char *p = strchr(path_value, ':');
//     if (p) {
//       *p = '\0';
//       p++;
//     }
//     char *full_name = calloc(strlen(path_value) + strlen(prog_name) + 2, sizeof(char));
//     if (!full_name)
//       return NULL;
//     strcpy(full_name, path_value);
//     full_name[strlen(path_value)] = '/';
//     strcat(full_name, prog_name);
//     if (access(full_name, X_OK) == 0)
//       return full_name;
//     path_value = p;
//     free(full_name);
//   }
//   return NULL;
// }
// 
// void child_exec(char **argv, char **envp) {
//   // wait when the parent is ready
//   raise(SIGSTOP);
//   execvpe(argv[1], argv + 1, envp);
// }
