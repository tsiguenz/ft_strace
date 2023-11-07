#include "ft_strace.h"
#include "registers.h"
#include "syscalls_x86_64.h"

const char      *prog_name;
syscall_x86_64_t syscalls_x86_64[] = {SYSCALLS_ENT_X86_64};

void print_regs(union user_regs_t regs, struct iovec io) {
  if (io.iov_len == sizeof(regs.regs64)) {
    struct x86_user_regs_struct current_regs = regs.regs64;
    syscall_x86_64_t syscall = syscalls_x86_64[current_regs.orig_rax];
    printf("syscall = %lu, %s\n", current_regs.orig_rax, syscall.name);
    printf("rdi = 0x%lx\n", current_regs.rdi);
    printf("rsi = 0x%lx\n", current_regs.rsi);
    printf("rdx = 0x%lx\n", current_regs.rdx);
    printf("rcx = 0x%lx\n", current_regs.rcx);
    printf("r8 = 0x%lx\n", current_regs.r8);
    printf("r9 = 0x%lx\n", current_regs.r9);
  }
}

void handle_syscall_io(int pid) {
  static bool print           = false;
  static bool in_kernel_space = false;
  (void) print;
  (void) in_kernel_space;
  union user_regs_t regs;
  struct iovec      io = {
           .iov_base = &regs,
           .iov_len  = sizeof(regs),
  };
  if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &io) == -1) {
    FATAL("%s: ptrace(GETREGSET): %s\n", prog_name, strerror(errno));
  }
  if (io.iov_len == sizeof(regs.regs64)) {
    // INFO: ptrace use process_vm_readv
    // print_regs(regs, io);
    struct x86_user_regs_struct current_regs = regs.regs64;
    syscall_x86_64_t syscall = syscalls_x86_64[current_regs.orig_rax];
    if (print == false && strcmp("execve", syscall.name) == 0) {
      print           = true;
      in_kernel_space = true;
    }
    if (print == false)
      return;
    if (in_kernel_space) {
      fprintf(stderr, syscall.format, syscall.name, current_regs.rdi,
              current_regs.rsi, current_regs.rdx, current_regs.rcx,
              current_regs.r8, current_regs.r9);
      in_kernel_space = false;
    } else {
      fprintf(stderr, ") = %lu\n", current_regs.rax);
      in_kernel_space = true;
    }
  }
  //       fprintf(stderr,
  //               "%s(%u, %u, %u) = ",
  //               syscalls_x86_64[regs.regs32.orig_eax].name,
  //               regs.regs32.edi, regs.regs32.esi, regs.regs32.edx);
  //       fprintf(stderr, "%u\n", regs.regs32.eax);
}

void disable_signals(void) {
  // restore signals to default
  sigset_t empty;
  sigemptyset(&empty);
  sigprocmask(SIG_SETMASK, &empty, NULL);
  // block int signals
  sigset_t block;
  sigemptyset(&block);
  sigaddset(&block, SIGHUP);
  sigaddset(&block, SIGINT);
  sigaddset(&block, SIGQUIT);
  sigaddset(&block, SIGPIPE);
  sigaddset(&block, SIGTERM);
  sigprocmask(SIG_BLOCK, &block, NULL);
}

int trace_syscalls(int pid) {
  int status;
  ptrace(PTRACE_SEIZE, pid, 0, 0);
  ptrace(PTRACE_INTERRUPT, pid, 0, 0);
  disable_signals();
  waitpid(pid, 0, 0);  // child wait when parent is ready
  for (; 42;) {
    status = 0;
    ptrace(PTRACE_SYSCALL, pid, 0, 0);
    if (waitpid(pid, &status, 0) == -1) {
      FATAL("%s: waitpid(): %s\n", prog_name, strerror(errno));
    }
    if (WIFEXITED(status)) {
      fprintf(stderr, ") = ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
      fprintf(stderr, "errno: %d = %s\n", errno, strerror(errno));
      exit(WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("killed by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
      handle_syscall_io(pid);
    } else if (WIFCONTINUED(status)) {
      printf("continued\n");
    }
  }
}

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
