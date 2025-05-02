#include "../include/execute_commands.h"
#include "../include/parser.h"
#include <stdio.h>
#include <string.h>
#define MAX_INPUT_SIZE 4096
#define True 1
#define False 0

int main() {
  char input[MAX_INPUT_SIZE];
  char *args;
  int background = 0;

  while (True) {
    printf("mini-shell> ");

    if (!fgets(input, sizeof(input), stdin)) {
      perror("fgets failed");
      continue;
    }
    // replacing the \n with \0
    input[strcspn(input, "\n")] = '\0';

    if (strncmp(input, "exit", 4) == 0) {
      printf("Exiting mini-shell......\n");
      break;
    }

    char **tokens = parse_command(input, &background);

    execute_command(tokens);
  }
  return 0;
}
