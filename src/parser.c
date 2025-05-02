#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARGS 20

char **parse_command(char *input, int *background) {
  char **tokens = malloc(MAX_ARGS * sizeof(char *));
  int token_count = 0;
  char *token = strtok(input, " ");

  while (token != NULL && token_count < MAX_ARGS) {
    tokens[token_count++] = token;
    token = strtok(NULL, " ");
  }

  return tokens;
}
