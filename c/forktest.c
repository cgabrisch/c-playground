#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char** args) {
  pid_t pid = fork();

  if (pid != 0) {
    printf("Parent %d, child %d\n", getpid(), pid);
    int status;
    waitpid(pid, &status, WUNTRACED);
    printf("%d exited.\n", pid);
  } else {
    printf("Child %d\n", getpid());
    if (execl("/bin/ls", "/bin/ls", "-la", ".", NULL) < 0) {
      perror("Could not execute ls");
    }
  }
}
