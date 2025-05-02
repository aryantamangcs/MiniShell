#include "../include/builtins.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void custom_ls(char *args[]) {
  char *path = ".";

  DIR *dir = opendir(path);

  if (dir == NULL) {
    perror("Error while opening the current directory\n");
    exit(1);
  }

  struct dirent *entry;
  // now reading the files from the directory
  printf("\n");
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] == '.') {
      continue;
    } else {
      printf("%s\n", entry->d_name);
    }
  }
  printf("\n");
}
