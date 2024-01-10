#ifndef SYSCALLS_X86_64_H
#define SYSCALLS_X86_64_H

// clang-format off
#define SYSCALLS_NBR 328
#define SYSCALLS_ENT_X86_64                                                    \
[0] = { "read", "%s(%u, \"%s\", %lu" },                                        \
[1] = { "write", "%s(%u, \"%s\", %lu" },                                       \
[2] = { "open", "%s(\"%s\", %d, %d" },                                         \
[3] = { "close", "%s(%u" },                                                    \
[4] = { "stat", "%s(\"%s\", %p" },                                             \
[5] = { "fstat", "%s(%u, %p" },                                                \
[6] = { "lstat", "%s(\"%s\", %p" },                                            \
[7] = { "poll", "%s(%p, %u, %ld" },                                            \
[8] = { "lseek", "%s(%u,%ld, %u" },                                            \
[9] = { "mmap", "%s(%lu, %lu, %lu, %lu, %lu, %lu" },                           \
[10] = { "mprotect", "%s(%lu, %lu, %lu" },                                     \
[11] = { "munmap", "%s(%lu, %lu" },                                            \
[12] = { "brk", "%s(%lu" },                                                    \
[13] = { "rt_sigaction", "%s(%d, %p, %p, %lu" },                               \
[14] = { "rt_sigprocmask", "%s(%d, %p, %p, %lu" },                             \
[15] = { "rt_sigreturn", "%s(%lu" },                                           \
[16] = { "ioctl", "%s(%u, %u, %lu" },                                          \
[17] = { "pread64", "%s(%lu, \"%s\", %lu,%ld" },                               \
[18] = { "pwrite64", "%s(%u, \"%s\", %lu,%ld" },                               \
[19] = { "readv", "%s(%lu, %p, %lu" },                                         \
[20] = { "writev", "%s(%lu, %p, %lu" },                                        \
[21] = { "access", "%s(\"%s\", %d" },                                          \
[22] = { "pipe", "%s(%p" },                                                    \
[23] = { "select", "%s(%d, %p, %p, %p, %p" },                                  \
[24] = { "sched_yield", "%s(" },                                               \
[25] = { "mremap", "%s(%lu, %lu, %lu, %lu, %lu" },                             \
[26] = { "msync", "%s(%lu, %lu, %d" },                                         \
[27] = { "mincore", "%s(%lu, %lu, %p" },                                       \
[28] = { "madvise", "%s(%lu, %lu, %d" },                                       \
[29] = { "shmget", "%s(%d, %lu, %d" },                                         \
[30] = { "shmat", "%s(%d, \"%s\", %d" },                                       \
[31] = { "shmctl", "%s(%d, %d, %p" },                                          \
[32] = { "dup", "%s(%u" },                                                     \
[33] = { "dup2", "%s(%u, %u" },                                                \
[34] = { "pause", "%s(" },                                                     \
[35] = { "nanosleep", "%s(%p, %p" },                                           \
[36] = { "getitimer", "%s(%d, %p" },                                           \
[37] = { "alarm", "%s(%u" },                                                   \
[38] = { "setitimer", "%s(%d, %p, %p" },                                       \
[39] = { "getpid", "%s(" },                                                    \
[40] = { "sendfile", "%s(%d, %d,%p, %lu" },                                    \
[41] = { "socket", "%s(%d, %d, %d" },                                          \
[42] = { "connect", "%s(%d, %p, %d" },                                         \
[43] = { "accept", "%s(%d, %p, %p" },                                          \
[44] = { "sendto", "%s(%d, %p, %lu, %d, %p, %d" },                             \
[45] = { "recvfrom", "%s(%d, %p, %lu, %d, %p, %p" },                           \
[46] = { "sendmsg", "%s(%d, %p, %d" },                                         \
[47] = { "recvmsg", "%s(%d, %p, %u" },                                         \
[48] = { "shutdown", "%s(%d, %d" },                                            \
[49] = { "bind", "%s(%d, %p, %d" },                                            \
[50] = { "listen", "%s(%d, %d" },                                              \
[51] = { "getsockname", "%s(%d, %p, %p" },                                     \
[52] = { "getpeername", "%s(%d, %p, %p" },                                     \
[53] = { "socketpair", "%s(%d, %d, %d, %p" },                                  \
[54] = { "setsockopt", "%s(%d, %d, %d, \"%s\", %d" },                          \
[55] = { "getsockopt", "%s(%d, %d, %d, \"%s\", %p" },                          \
[56] = { "clone", "%s(%lu, %lu, %p, %p, %u" },                                 \
[57] = { "fork", "%s(" },                                                      \
[58] = { "vfork", "%s(" },                                                     \
[59] = { "execve", "%s(\"%s\", %p, %p" },                                      \
[60] = { "exit", "%s(%d" },                                                    \
[61] = { "wait4", "%s(%d, %p, %d, %p" },                                       \
[62] = { "kill", "%s(%d, %d" },                                                \
[63] = { "uname", "%s(%p" },                                                   \
[64] = { "semget", "%s(%d, %d, %d" },                                          \
[65] = { "semop", "%s(%d, %p, %d" },                                           \
[66] = { "semctl", "%s(%d, %d, %d" },                                          \
[67] = { "shmdt", "%s(\"%s\"" },                                               \
[68] = { "msgget", "%s(%d, %d" },                                              \
[69] = { "msgsnd", "%s(%d, %p, %lu, %d" },                                     \
[70] = { "msgrcv", "%s(%d, %p, %lu, %ld, %d" },                                \
[71] = { "msgctl", "%s(%d, %d, %p" },                                          \
[72] = { "fcntl", "%s(%u, %u, %lu" },                                          \
[73] = { "flock", "%s(%u, %u" },                                               \
[74] = { "fsync", "%s(%u" },                                                   \
[75] = { "fdatasync", "%s(%u" },                                               \
[76] = { "truncate", "%s(\"%s\", %ld" },                                       \
[77] = { "ftruncate", "%s(%u, %lu" },                                          \
[78] = { "getdents", "%s(%u, %p, %u" },                                        \
[79] = { "getcwd", "%s(\"%s\", %lu" },                                         \
[80] = { "chdir", "%s(\"%s\"" },                                               \
[81] = { "fchdir", "%s(%u" },                                                  \
[82] = { "rename", "%s(\"%s\", \"%s\"" },                                      \
[83] = { "mkdir", "%s(\"%s\", %d" },                                           \
[84] = { "rmdir", "%s(\"%s\"" },                                               \
[85] = { "creat", "%s(\"%s\", %d" },                                           \
[86] = { "link", "%s(\"%s\", \"%s\"" },                                        \
[87] = { "unlink", "%s(\"%s\"" },                                              \
[88] = { "symlink", "%s(\"%s\", \"%s\"" },                                     \
[89] = { "readlink", "%s(\"%s\", \"%s\", %d" },                                \
[90] = { "chmod", "%s(\"%s\", %u" },                                           \
[91] = { "fchmod", "%s(%u, %u" },                                              \
[92] = { "chown", "%s(\"%s\", %d, %d" },                                       \
[93] = { "fchown", "%s(%u, %d, %d" },                                          \
[94] = { "lchown", "%s(\"%s\", %d, %d" },                                      \
[95] = { "umask", "%s(%d" },                                                   \
[96] = { "gettimeofday", "%s(%p, %p" },                                        \
[97] = { "getrlimit", "%s(%u, %p" },                                           \
[98] = { "getrusage", "%s(%d, %p" },                                           \
[99] = { "sysinfo", "%s(%p" },                                                 \
[100] = { "times", "%s(%p" },                                                  \
[101] = { "ptrace", "%s(%ld, %ld, %lu, %lu" },                                 \
[102] = { "getuid", "%s(" },                                                   \
[103] = { "syslog", "%s(%d, \"%s\", %d" },                                     \
[104] = { "getgid", "%s(" },                                                   \
[105] = { "setuid", "%s(%d" },                                                 \
[106] = { "setgid", "%s(%d" },                                                 \
[107] = { "geteuid", "%s(" },                                                  \
[108] = { "getegid", "%s(" },                                                  \
[109] = { "setpgid", "%s(%d, %d" },                                            \
[110] = { "getppid", "%s(" },                                                  \
[111] = { "getpgrp", "%s(" },                                                  \
[112] = { "setsid", "%s(" },                                                   \
[113] = { "setreuid", "%s(%d, %d" },                                           \
[114] = { "setregid", "%s(%d, %d" },                                           \
[115] = { "getgroups", "%s(%d, %p" },                                          \
[116] = { "setgroups", "%s(%d, %p" },                                          \
[117] = { "setresuid", "%s(%p, %p, %p" },                                      \
[118] = { "getresuid", "%s(%p, %p, %p" },                                      \
[119] = { "setresgid", "%s(%d, %d, %d" },                                      \
[120] = { "getresgid", "%s(%p, %p, %p" },                                      \
[121] = { "getpgid", "%s(%d" },                                                \
[122] = { "setfsuid", "%s(%d" },                                               \
[123] = { "setfsgid", "%s(%d" },                                               \
[124] = { "getsid", "%s(%d" },                                                 \
[125] = { "capget", "%s(%p, %p" },                                             \
[126] = { "capset", "%s(%p, %p" },                                             \
[127] = { "rt_sigpending", "%s(%p, %lu" },                                     \
[128] = { "rt_sigtimedwait", "%s( %p, %p, %p, %lu" },                          \
[129] = { "rt_sigqueueinfo", "%s(%d, %d, %p" },                                \
[130] = { "rt_sigsuspend", "%s(%p, %lu" },                                     \
[131] = { "sigaltstack", "%s( %p, %p" },                                       \
[132] = { "utime", "%s(\"%s\", %p" },                                          \
[133] = { "mknod", "%s(\"%s\", %u, %d" },                                      \
[134] = { "uselib", "%s(NOT IMPLEMENTED" },                                    \
[135] = { "personality", "%s(%u" },                                            \
[136] = { "ustat", "%s(%d, %p" },                                              \
[137] = { "statfs", "%s(\"%s\", %p" },                                         \
[138] = { "fstatfs", "%s(%u, %p" },                                            \
[139] = { "sysfs", "%s(%d, %lu, %lu" },                                        \
[140] = { "getpriority", "%s(%d, %d" },                                        \
[141] = { "setpriority", "%s(%d, %d, %d" },                                    \
[142] = { "sched_setparam", "%s(%d, %p" },                                     \
[143] = { "sched_getparam", "%s(%d, %p" },                                     \
[144] = { "sched_setscheduler", "%s(%d, %d, %p" },                             \
[145] = { "sched_getscheduler", "%s(%d" },                                     \
[146] = { "sched_get_priority_max", "%s(%d" },                                 \
[147] = { "sched_get_priority_min", "%s(%d" },                                 \
[148] = { "sched_rr_get_interval", "%s(%d, %p" },                              \
[149] = { "mlock", "%s(%lu, %lu" },                                            \
[150] = { "munlock", "%s(%lu, %lu" },                                          \
[151] = { "mlockall", "%s(%d" },                                               \
[152] = { "munlockall", "%s(" },                                               \
[153] = { "vhangup", "%s(" },                                                  \
[154] = { "modify_ldt", "%s(%d, %p, %lu" },                                    \
[155] = { "pivot_root", "%s(\"%s\", %s" },                                     \
[156] = { "_sysctl", "%s(%p" },                                                \
[157] = { "prctl", "%s(%d, %lu, %lu, %lu, %lu" },                              \
[158] = { "arch_prctl", "%s(%p, %d, %p" },                                     \
[159] = { "adjtimex", "%s(%p" },                                               \
[160] = { "setrlimit", "%s(%u, %p" },                                          \
[161] = { "chroot", "%s(%s" },                                                 \
[162] = { "sync", "%s(" },                                                     \
[163] = { "acct", "%s(%s" },                                                   \
[164] = { "settimeofday", "%s(%p, %p" },                                       \
[165] = { "mount", "%s(\"%s\", \"%s\", \"%s\", %lu, %p" },                     \
[166] = { "umount2", "%s(\"%s\", %d" },                                        \
[167] = { "swapon", "%s(\"%s\", %d" },                                         \
[168] = { "swapoff", "%s(%s" },                                                \
[169] = { "reboot", "%s(%d, %d, %u, %p" },                                     \
[170] = { "sethostname", "%s(\"%s\", %d" },                                    \
[171] = { "setdomainname", "%s(\"%s\", %d" },                                  \
[172] = { "iopl", "%s(%u, %p" },                                               \
[173] = { "ioperm", "%s(%lu, %lu, %d" },                                       \
[174] = { "create_module", "%s(REMOVED IN Linux 2.6" },                        \
[175] = { "init_module", "%s(%p, %lu, %s" },                                   \
[176] = { "delete_module", "%s( %p, %u" },                                     \
[177] = { "get_kernel_syms", "%s(REMOVED IN Linux 2.6" },                      \
[178] = { "query_module", "%s(REMOVED IN Linux 2.6" },                         \
[179] = { "quotactl", "%s(%u, \"%s\", %d, %p" },                               \
[180] = { "nfsservctl", "%s(NOT IMPLEMENTED" },                                \
[181] = { "getpmsg", "%s(NOT IMPLEMENTED" },                                   \
[182] = { "putpmsg", "%s(NOT IMPLEMENTED" },                                   \
[183] = { "afs_syscall", "%s(NOT IMPLEMENTED" },                               \
[184] = { "tuxcall", "%s(NOT IMPLEMENTED" },                                   \
[185] = { "security", "%s(NOT IMPLEMENTED" },                                  \
[186] = { "gettid", "%s(" },                                                   \
[187] = { "readahead", "%s(%d,%ld, %lu" },                                     \
[188] = { "setxattr", "%s(\"%s\", \"%s\", %p, %lu, %d" },                      \
[189] = { "lsetxattr", "%s(\"%s\", \"%s\", %p, %lu, %d" },                     \
[190] = { "fsetxattr", "%s(%d, \"%s\", %p, %lu, %d" },                         \
[191] = { "getxattr", "%s(\"%s\", \"%s\", %p, %lu" },                          \
[192] = { "lgetxattr", "%s(\"%s\", \"%s\", %p, %lu" },                         \
[193] = { "fgetxattr", "%s(%d, %p, %p, %lu" },                                 \
[194] = { "listxattr", "%s(\"%s\", \"%s\", %lu" },                             \
[195] = { "llistxattr", "%s(\"%s\", \"%s\", %lu" },                            \
[196] = { "flistxattr", "%s(%d, \"%s\", %lu" },                                \
[197] = { "removexattr", "%s(\"%s\", %s" },                                    \
[198] = { "lremovexattr", "%s(\"%s\", %s" },                                   \
[199] = { "fremovexattr", "%s(%d, %s" },                                       \
[200] = { "tkill", "%s(%d, %d" },                                              \
[201] = { "time", "%s(%p" },                                                   \
[202] = { "futex", "%s(%p, %d, %u, %p, %p, %u" },                              \
[203] = { "sched_setaffinity", "%s(%d, %u, %p" },                              \
[204] = { "sched_getaffinity", "%s(%d, %u, %p" },                              \
[205] = { "set_thread_area", "%s(NOT IMPLEMENTED. Use arch_prctl" },           \
[206] = { "io_setup", "%s(%d, %p" },                                           \
[207] = { "io_destroy", "%s(%lu" },                                            \
[208] = { "io_getevents", "%s(%lu, %ld, %ld, %p" },                            \
[209] = { "io_submit", "%s(%lu, %ld, %p" },                                    \
[210] = { "io_cancel", "%s(%lu, %p, %p" },                                     \
[211] = { "get_thread_area", "%s(NOT IMPLEMENTED. Use arch_prctl" },           \
[212] = { "lookup_dcookie", "%s(%lu %ld, %ld" },                               \
[213] = { "epoll_create", "%s(%d" },                                           \
[214] = { "epoll_ctl_old", "%s(NOT IMPLEMENTED" },                             \
[215] = { "epoll_wait_old", "%s(NOT IMPLEMENTED" },                            \
[216] = { "remap_file_pages", "%s(%lu, %lu, %lu, %lu, %lu" },                  \
[217] = { "getdents64", "%s(%u, %p, %u" },                                     \
[218] = { "set_tid_address", "%s(%p" },                                        \
[219] = { "restart_syscall", "%s(" },                                          \
[220] = { "semtimedop", "%s(%d, %p, %d, %p" },                                 \
[221] = { "fadvise64", "%s(%d,%ld, %lu, %d" },                                 \
[222] = { "timer_create", "%s( %d, %p, %p" },                                  \
[223] = { "timer_settime", "%s(%p, %d, %p, %p" },                              \
[224] = { "timer_gettime", "%s(%p, %p" },                                      \
[225] = { "timer_getoverrun", "%s(%p" },                                       \
[226] = { "timer_delete", "%s(%p" },                                           \
[227] = { "clock_settime", "%s( %d, %p" },                                     \
[228] = { "clock_gettime", "%s( %d, %p" },                                     \
[229] = { "clock_getres", "%s( %d, %p" },                                      \
[230] = { "clock_nanosleep", "%s( %d, %d, %p, %p" },                           \
[231] = { "exit_group", "%s(%d" },                                             \
[232] = { "epoll_wait", "%s(%d, %p, %d, %d" },                                 \
[233] = { "epoll_ctl", "%s(%d, %d, %d, %p" },                                  \
[234] = { "tgkill", "%s(%d, %d, %d" },                                         \
[235] = { "utimes", "%s(\"%s\", %p" },                                         \
[236] = { "vserver", "%s(NOT IMPLEMENTED" },                                   \
[237] = { "mbind", "%s(%lu, %lu, %lu, %p, %lu, %d" },                          \
[238] = { "set_mempolicy", "%s(%d, %p, %lu" },                                 \
[239] = { "get_mempolicy", "%s(%p, %p, %lu, %lu, %lu" },                       \
[240] = { "mq_open", "%s(\"%s\", %d, %u, %p" },                                \
[241] = { "mq_unlink", "%s(%s" },                                              \
[242] = { "mq_timedsend", "%s(%d, \"%s\", %lu, %u, %p" },                      \
[243] = { "mq_timedreceive", "%s(%d, \"%s\", %lu, %p, %p" },                   \
[244] = { "mq_notify", "%s(%d, %p" },                                          \
[245] = { "mq_getsetattr", "%s(%d, %p, %p" },                                  \
[246] = { "kexec_load", "%s(%lu, %lu, %p, %lu" },                              \
[247] = { "waitid", "%s(%d, %d, %p, %d, %p" },                                 \
[248] = { "add_key", "%s(\"%s\", \"%s\", %p, %lu" },                           \
[249] = { "request_key", "%s(\"%s\", \"%s\", \"%s\", %d" },                    \
[250] = { "keyctl", "%s(%d, %lu, %lu, %lu, %lu" },                             \
[251] = { "ioprio_set", "%s(%d, %d, %d" },                                     \
[252] = { "ioprio_get", "%s(%d, %d" },                                         \
[253] = { "inotify_init", "%s(" },                                             \
[254] = { "inotify_add_watch", "%s(%d, \"%s\", %u" },                          \
[255] = { "inotify_rm_watch", "%s(%d, %d" },                                   \
[256] = { "migrate_pages", "%s(%d, %lu, %p, %p" },                             \
[257] = { "openat", "%s(%d, \"%s\", %d, %d" },                                 \
[258] = { "mkdirat", "%s(%d, \"%s\", %d" },                                    \
[259] = { "mknodat", "%s(%d, \"%s\", %d, %d" },                                \
[260] = { "fchownat", "%s(%d, \"%s\", %d, %d, %d" },                           \
[261] = { "futimesat", "%s(%d, \"%s\", %p" },                                  \
[262] = { "newfstatat", "%s(%d, \"%s\", %p, %d" },                             \
[263] = { "unlinkat", "%s(%d, \"%s\", %d" },                                   \
[264] = { "renameat", "%s(%d, \"%s\", %d, %s" },                               \
[265] = { "linkat", "%s(%d, \"%s\", %d, \"%s\", %d" },                         \
[266] = { "symlinkat", "%s(\"%s\", %d, %s" },                                  \
[267] = { "readlinkat", "%s(%d, \"%s\", \"%s\", %d" },                         \
[268] = { "fchmodat", "%s(%d, \"%s\", %u" },                                   \
[269] = { "faccessat", "%s(%d, \"%s\", %d" },                                  \
[270] = { "pselect6", "%s(%d, %p, %p, %p, %p, %p" },                           \
[271] = { "ppoll", "%s(%p, %u, %p, %p, %lu" },                                 \
[272] = { "unshare", "%s(%lu" },                                               \
[273] = { "set_robust_list", "%s(%p, %lu" },                                   \
[274] = { "get_robust_list", "%s(%d, %p, %p" },                                \
[275] = { "splice", "%s(%d,%p, %d,%p, %lu, %u" },                              \
[276] = { "tee", "%s(%d, %d, %lu, %u" },                                       \
[277] = { "sync_file_range", "%s(%ld,%ld,%ld, %ld" },                          \
[278] = { "vmsplice", "%s(%d, %p, %lu, %u" },                                  \
[279] = { "move_pages", "%s(%d, %lu, %p, %p, %p, %d" },                        \
[280] = { "utimensat", "%s(%d, \"%s\", %p, %d" },                              \
[281] = { "epoll_pwait", "%s(%d, %p, %d, %d, %p, %lu" },                       \
[282] = { "signalfd", "%s(%d, %p, %lu" },                                      \
[283] = { "timerfd_create", "%s(%d, %d" },                                     \
[284] = { "eventfd", "%s(%u" },                                                \
[285] = { "fallocate", "%s(%ld, %ld,%ld,%ld" },                                \
[286] = { "timerfd_settime", "%s(%d, %d, %p, %p" },                            \
[287] = { "timerfd_gettime", "%s(%d, %p" },                                    \
[288] = { "accept4", "%s(%d, %p, %p, %d" },                                    \
[289] = { "signalfd4", "%s(%d, %p, %lu, %d" },                                 \
[290] = { "eventfd2", "%s(%u, %d" },                                           \
[291] = { "epoll_create1", "%s(%d" },                                          \
[292] = { "dup3", "%s(%u, %u, %d" },                                           \
[293] = { "pipe2", "%s(%p, %d" },                                              \
[294] = { "inotify_init1", "%s(%d" },                                          \
[295] = { "preadv", "%s(%lu, %p, %lu, %lu, %lu" },                             \
[296] = { "pwritev", "%s(%lu, %p, %lu, %lu, %lu" },                            \
[297] = { "rt_tgsigqueueinfo", "%s(%d, %d, %d, %p" },                          \
[298] = { "perf_event_open", "%s(%p, %d, %d, %d, %lu" },                       \
[299] = { "recvmmsg", "%s(%d, %p, %u, %u, %p" },                               \
[300] = { "fanotify_init", "%s(%u, %u" },                                      \
[301] = { "fanotify_mark", "%s(%ld, %ld, %lu, %ld, %ld" },                     \
[302] = { "prlimit64", "%s(%d, %u, %p, %p" },                                  \
[303] = { "name_to_handle_at", "%s(%d, \"%s\", %p, %p, %d" },                  \
[304] = { "open_by_handle_at", "%s(%d, \"%s\", %p, %p, %d" },                  \
[305] = { "clock_adjtime", "%s(%d, %p" },                                      \
[306] = { "syncfs", "%s(%d" },                                                 \
[307] = { "sendmmsg", "%s(%d, %p, %u, %u" },                                   \
[308] = { "setns", "%s(%d, %d" },                                              \
[309] = { "getcpu", "%s(%p, %p, %p" },                                         \
[310] = { "process_vm_readv", "%s(%d, %p, %lu, %p, %lu, %lu" },                \
[311] = { "process_vm_writev", "%s(%d, %p, %lu, %p, %lu, %lu" },               \
[312] = { "kcmp", "%s(%d, %d, %d, %lu, %lu" },                                 \
[313] = { "finit_module", "%s(%d, \"%s\", %d" },                               \
[314] = { "sched_setattr", "%s(%d, %p, %u" },                                  \
[315] = { "sched_getattr", "%s(%d, %p, %u, %u" },                              \
[316] = { "renameat2", "%s(%d, \"%s\", %d, \"%s\", %u" },                      \
[317] = { "seccomp", "%s(%u, %u, %s" },                                        \
[318] = { "getrandom", "%s(\"%s\", %lu, %u" },                                 \
[319] = { "memfd_create", "%s(\"%s\", %u" },                                   \
[320] = { "kexec_file_load", "%s(%d, %d, %lu, \"%s\", %lu" },                  \
[321] = { "bpf", "%s(%d, union %p, %u" },                                      \
[322] = { "stub_execveat", "%s(%d, \"%s\", %p, %p, %d" },                      \
[323] = { "userfaultfd", "%s(%d" },                                            \
[324] = { "membarrier", "%s(%d, %d" },                                         \
[325] = { "mlock2", "%s(%lu, %lu, %d" },                                       \
[326] = { "copy_file_range", "%s(%d,%ld, %d, %ld, %lu, %u" },                  \
[327] = { "preadv2", "%s(%lu, %p, %lu, %lu, %lu, %d" },                        \
[328] = { "pwritev2", "%s(%lu, %p, %lu, %lu, %lu, %d" }

#endif  // SYSCALLS_X86_64_H
