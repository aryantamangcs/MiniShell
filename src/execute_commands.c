#include "../include/execute_commands.h"
#include "../include/builtins.h"
#include <stdio.h>
#include <string.h>

void execute_command(char **args) {
  char *command = args[0];

  if (strcmp(command, "ls") == 0) {
    custom_ls(args);
  } else if (strcmp(command, "cd") == 0) {
    printf("cd\n");
  } else {
    printf("%s : command not found\n", command);
  }
}
