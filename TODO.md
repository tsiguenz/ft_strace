# Init

- Startup child (src/strace.c:2835)

- Synchonize child:

```c
    alarm(3);
    /* we depend on SIGCHLD set to SIG_DFL by init code */
    /* if it happens to be SIG_IGN'ed, wait won't block */
    while (wait(NULL) < 0 && errno == EINTR)
      ;
    alarm(0);
    if (params->child_sa.sa_handler != SIG_DFL)
      sigaction(SIGCHLD, &params->child_sa, NULL);
  }

  if (!username)
    maybe_init_seccomp_filter();
  execve(params->pathname, params->argv, params->env);
- Disable signals (src/strace.c:2846)
```

- Disable signals parent:

```c
  set_sighandler(SIGTTOU, SIG_IGN, NULL);
  set_sighandler(SIGTTIN, SIG_IGN, NULL);
  if (opt_intr != INTR_ANYWHERE) {
    if (opt_intr == INTR_BLOCK_TSTP_TOO)
      set_sighandler(SIGTSTP, SIG_IGN, NULL);
    /*
     * In interactive mode (if no -o OUTFILE, or -p PID is used),
     * fatal signals are handled asynchronously and acted
     * when waiting for process state changes.
     * In non-interactive mode these signals are ignored.
     */
    set_sighandler(SIGHUP, interactive ? interrupt : SIG_IGN, NULL);
    set_sighandler(SIGINT, interactive ? interrupt : SIG_IGN, NULL);
    set_sighandler(SIGQUIT, interactive ? interrupt : SIG_IGN, NULL);
    set_sighandler(SIGPIPE, interactive ? interrupt : SIG_IGN, NULL);
    set_sighandler(SIGTERM, interactive ? interrupt : SIG_IGN, NULL);
  }

  sigemptyset(&timer_set);
  sigaddset(&timer_set, SIGALRM);
  sigprocmask(SIG_BLOCK, &timer_set, NULL);
  set_sighandler(SIGALRM, timer_sighandler, NULL);
```
