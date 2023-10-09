# ft_strace

## Allowed ptrace options

|Option|Description|
|------|-----------|
|PTRACE\_SYSCALL|Restart the stopped tracee and stop it at the next entry or exit from a system call. data argument is set with the signal to be delivered to the tracee.|
|PTRACE\_GETREGSET|Read the tracee's registers. ... |
|PTRACE\_SETOPTIONS|Set ptrace options from data.|
|PTRACE\_GETSIGINFO|Get informations about the signal that caused the stop. data contain siginfo\_t structure.|
|PTRACE\_SEIZE|Attach to the process specified in pid. Doesn't stop the process and return the stop signal in WSTOPSIG(status).|
|PTRACE\_INTERRUPT|Stop a tracee if it's running or sleeping in kernel space and PTRACE\_SYSCALL is in effect.|
|PTRACE\_LISTEN|Restart the stopped tracee.|
