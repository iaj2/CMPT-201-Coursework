#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *buff = NULL;
  size_t len = 0;

  while (true) {
    printf("Enter programs to run: \n");

    ssize_t num_char = getline(&buff, &len, stdin);

    if (num_char > 0 && buff[num_char - 1] == '\n') {
      buff[num_char - 1] = '\0';
    } else {
      printf("done or error\n");
      exit(EXIT_FAILURE);
    }

    int pid = fork();

    if (pid == 0) {
      execl(buff, buff, NULL);
    } else {
      // Parent
      int status;
      waitpid(pid, &status, 0);

      if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
      }
    }
  }

  free(buff);
  return 0;
}
