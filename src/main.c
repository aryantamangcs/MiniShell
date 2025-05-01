#include <stdio.h>
#include <string.h>
#define MAX_INPUT_SIZE 4096
#define True 1
#define False 0

int main() {
  char input[MAX_INPUT_SIZE];

  while (True) {
    printf("mini-shell> ");

    if (!fgets(input, sizeof(input), stdin)) {
      perror("fgets failed");
      continue;
    }

    if (strncmp(input, "exit", 4) == 0) {
      printf("Exiting mini-shell......\n");
      break;
    }
  }
  return 0;
}
