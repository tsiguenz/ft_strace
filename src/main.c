#include "ft_strace.h"
#include "registers.h"
#include "syscalls_x86_64.h"

const char* prog_name;
syscall_x86_64_t syscalls_x86_64[] = {SYSCALLS_ENT_X86_64};

void
print_regs(union user_regs_t regs, struct iovec io) {
    if (io.iov_len == sizeof(regs.regs64)) {
        struct user_regs_struct current_regs = regs.regs64;
        syscall_x86_64_t syscall = syscalls_x86_64[current_regs.orig_rax];
        if (strcmp(syscall.name, "access") == 0) {
            printf("syscall = %llu, %s\n", current_regs.orig_rax, syscall.name);
            printf("rdi = %llx\n", current_regs.rdi);
            printf("rsi = 0x%llx\n", current_regs.rsi);
            printf("rdx = 0x%llx\n", current_regs.rdx);
            printf("rcx = 0x%llx\n", current_regs.rcx);
            printf("r8 = 0x%llx\n", current_regs.r8);
            printf("r9 = 0x%llx\n", current_regs.r9);
        } else {
            printf("syscall = %llu, %s\n", current_regs.orig_rax, syscall.name);
            printf("rdi = 0x%llx\n", current_regs.rdi);
            printf("rsi = 0x%llx\n", current_regs.rsi);
            printf("rdx = 0x%llx\n", current_regs.rdx);
            printf("rcx = 0x%llx\n", current_regs.rcx);
            printf("r8 = 0x%llx\n", current_regs.r8);
            printf("r9 = 0x%llx\n", current_regs.r9);
        }
    }
}

void
handle_syscall_io(int pid, int i) {
    union user_regs_t regs;
    struct iovec io = {
        .iov_base = &regs,
        .iov_len = sizeof(regs),
    };
    if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &io) == -1) {
        FATAL("%s: ptrace(GETREGSET): %s\n", prog_name, strerror(errno));
    }
    if (io.iov_len == sizeof(regs.regs64)) {
        if (!(i % 2)) {
            print_regs(regs, io);
            // struct user_regs_struct current_regs = regs.regs64;
            // syscall_x86_64_t        syscall = syscalls_x86_64[current_regs.orig_rax];
            // fprintf(stderr, syscall.format, syscall.name, current_regs.rdi,
            //         current_regs.rsi, current_regs.rdx, current_regs.rcx,
            //         current_regs.r8, current_regs.r9);
        } else {
            fprintf(stderr, ") = %llu\n", regs.regs64.rax);
        }
    } //else {
      //    if ((i % 2))
      //      fprintf(stderr,
      //              "%s(%u, %u, %u) = ", syscalls_x86_64[regs.regs32.orig_eax].name,
      //              regs.regs32.edi, regs.regs32.esi, regs.regs32.edx);
      //    else
      //      fprintf(stderr, "%u\n", regs.regs32.eax);
      //  }
}

int
trace_syscalls(int pid) {
    int status;
    for (int i = 0; 42; i++) {
        status = 0;
        ptrace(PTRACE_SYSCALL, pid, 0, 0);
        if (waitpid(pid, &status, 0) == -1) {
            FATAL("%s: waitpid(): %s\n", prog_name, strerror(errno));
        }
        if (WIFEXITED(status)) {
            // problem sometimes exit with no such process
            fprintf(stderr, ") = ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
            // is it normal it differ sometimes
            fprintf(stderr, "errno: %d = %s\n", errno, strerror(errno));
            exit(WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("killed by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            handle_syscall_io(pid, i);
        } else if (WIFCONTINUED(status)) {
            printf("continued\n");
        }
    }
}

int
strace(char** argv, char** envp) {
    pid_t pid = fork();
    if (pid < 0) {
        FATAL("%s: fork(): %s\n", prog_name, strerror(errno));
    }
    if (pid == 0) {
        kill(getpid(), SIGSTOP);
        write(1, "hello\n", 6);
        execve(argv[1], argv + 1, envp);
        FATAL("%s: execve(): %s\n", prog_name, strerror(errno));
    }
    ptrace(PTRACE_SEIZE, pid, 0, 0);
    ptrace(PTRACE_INTERRUPT, pid, 0, 0);
    // wait the tracee
    usleep(100);
    // do something with signals
    return trace_syscalls(pid);
}

int
main(int argc, char** argv, char** envp) {
    prog_name = argv[0];
    if (argc == 1) {
        FATAL("%s: must have PROG [ARGS]\n", prog_name);
    }
    return strace(argv, envp);
}
