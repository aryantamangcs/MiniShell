#include "../include/execute_commands.h"
#include "../include/builtins.h"
#include <stdio.h>
#include <string.h>

int count_args(char **args) {
  int count = 0;
  while (args[count] != NULL) {
    count++;
  }
  return count;
}

void execute_command(char **args) {
  char *command = args[0];
  int argc = count_args(args);

  if (strcmp(command, "ls") == 0) {
    custom_ls(argc, args);
  } else if (strcmp(command, "cd") == 0) {
    printf("cd\n");
  } else {
    printf("%s : command not found\n", command);
  }
}
