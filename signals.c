#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

static void sighandler(int signo) {
  int fd;
  char * err = "Exited due to SIGINT\n";
  if (SIGINT == signo) {
    fd = open("stuff", O_CREAT | O_WRONLY | O_APPEND, 0644);
    write(fd, &err, sizeof(err));
    close(fd);
    exit(1);
  }
  if (SIGUSR1 == signo) {
    printf("Parent PID:%d\n", getppid());
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);

  while(1) {
    printf("PID:%d\n", getpid());
    sleep(1);
  }

  return 0;
}
