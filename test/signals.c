#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signal) { printf("Signal %d is caughed !\n", signal); }

int main(void) {
  signal(SIGINT, handler);
  signal(SIGTERM, handler);
  signal(SIGILL, handler);
  while (1) {
    sleep(1);
  }
  return 0;
}
