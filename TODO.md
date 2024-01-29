# TODO

- Signals:

|**Signal**|**Message**|
|--------|-------------|
|HUP     |--- SIGHUP {si_signo=SIGHUP, si_code=SI_USER, si_pid=11583, si_uid=1000} ---<br>+++ killed by SIGHUP +++|
|INT     |--- SIGINT {si_signo=SIGINT, si_code=SI_KERNEL} <br> --- strace: Process xxx detached|
|QUIT    |--- SIGQUIT {si_signo=SIGQUIT, si_code=SI_USER, si_pid=11629, si_uid=1000} ---<br>+++ killed by SIGQUIT +++|
|ILL     |--- SIGILL {si_signo=SIGILL, si_code=SI_USER, si_pid=11676, si_uid=1000} ---<br>+++ killed by SIGILL +++|
|TRAP    |--- SIGTRAP {si_signo=SIGTRAP, si_code=SI_USER, si_pid=11707, si_uid=1000} ---<br>+++ killed by SIGTRAP +++|
|ABRT    |--- SIGABRT {si_signo=SIGABRT, si_code=SI_USER, si_pid=11738, si_uid=1000} ---<br>+++ killed by SIGABRT +++|
|BUS     |--- SIGBUS {si_signo=SIGBUS, si_code=SI_USER, si_pid=11841, si_uid=1000} ---<br>+++ killed by SIGBUS +++|
|FPE     |--- SIGFPE {si_signo=SIGFPE, si_code=SI_USER, si_pid=11886, si_uid=1000} ---<br>+++ killed by SIGFPE +++|
|USR1    |--- SIGUSR1 {si_signo=SIGUSR1, si_code=SI_USER, si_pid=12693, si_uid=1000} ---<br>+++ killed by SIGUSR1 +++|
|SEGV    |--- SIGSEGV {si_signo=SIGSEGV, si_code=SI_USER, si_pid=11993, si_uid=1000} ---<br>+++ killed by SIGSEGV +++|
|USR2    |--- SIGUSR2 {si_signo=SIGUSR2, si_code=SI_USER, si_pid=12024, si_uid=1000} ---<br>+++ killed by SIGUSR2 +++|
|PIPE    |--- SIGPIPE {si_signo=SIGPIPE, si_code=SI_USER, si_pid=12055, si_uid=1000} ---<br>+++ killed by SIGPIPE +++|
|ALRM    |--- SIGALRM {si_signo=SIGALRM, si_code=SI_USER, si_pid=12086, si_uid=1000} ---<br>+++ killed by SIGALRM +++|
|TERM    |--- SIGTERM {si_signo=SIGTERM, si_code=SI_USER, si_pid=12117, si_uid=1000} ---<br>+++ killed by SIGTERM +++|
|STKFLT  |--- SIGSTKFLT {si_signo=SIGSTKFLT, si_code=SI_USER, si_pid=12148, si_uid=1000} ---<br>+++ killed by SIGSTKFLT +++|
|CHLD    |--- SIGCHLD {si_signo=SIGCHLD, si_code=SI_USER, si_pid=12222, si_uid=1000} ---|
|CONT    |--- SIGCONT {si_signo=SIGCONT, si_code=SI_USER, si_pid=12250, si_uid=1000} ---|
|STOP    |--- SIGSTOP {si_signo=SIGSTOP, si_code=SI_USER, si_pid=12264, si_uid=1000} ---<br>--- stopped by SIGSTOP ---|
|TSTP    |--- SIGTSTP {si_signo=SIGTSTP, si_code=SI_USER, si_pid=12320, si_uid=1000} ---<br>--- stopped by SIGTSTP ---|
|TTIN    |--- SIGTTIN {si_signo=SIGTTIN, si_code=SI_USER, si_pid=12351, si_uid=1000} ---<br>--- stopped by SIGTTIN ---|
|TTOU    |--- SIGTTOU {si_signo=SIGTTOU, si_code=SI_USER, si_pid=12393, si_uid=1000} ---<br>--- stopped by SIGTTOU ---|
|URG     |--- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=12421, si_uid=1000} ---|
|XCPU    |--- SIGXCPU {si_signo=SIGXCPU, si_code=SI_USER, si_pid=12449, si_uid=1000} ---<br>+++ killed by SIGXCPU +++|
|XFSZ    |--- SIGXFSZ {si_signo=SIGXFSZ, si_code=SI_USER, si_pid=12480, si_uid=1000} ---<br>+++ killed by SIGXFSZ +++|
|VTALRM  |--- SIGVTALRM {si_signo=SIGVTALRM, si_code=SI_USER, si_pid=12511, si_uid=1000} ---<br>+++ killed by SIGVTALRM +++|
|PROF    |--- SIGPROF {si_signo=SIGPROF, si_code=SI_USER, si_pid=12542, si_uid=1000} ---<br>+++ killed by SIGPROF +++|
|WINCH   |--- SIGWINCH {si_signo=SIGWINCH, si_code=SI_USER, si_pid=12573, si_uid=1000} ---<br>|<br>+++ killed by SIGIO +++|
|PWR     |--- SIGPWR {si_signo=SIGPWR, si_code=SI_USER, si_pid=12631, si_uid=1000} ---<br>+++ killed by SIGPWR +++|
|SYS     |--- SIGSYS {si_signo=SIGSYS, si_code=SI_USER, si_pid=12662, si_uid=1000} ---<br>+++ killed by SIGSYS +++|
