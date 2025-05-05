#include "../include/builtins.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void custom_ls(int argc, char *args[]) {

  // by default if only ls command is provided then the path should be current
  // directory
  char *path = ".";
  int showDetail = False;
  int showHidden = False;

  int i;
  if (argc > 1) {
    for (i = 1; args[i] != NULL; i++) {
      if (strncmp(args[i], "-", 1) != 0) {
        path = args[i];
      }
      if (strncmp(args[i], "-l", 2) == 0) {
        showDetail = True;
      }
      if (strncmp(args[i], "-a", 2) == 0) {
        showHidden = True;
      }
    }
  }

  DIR *dir = opendir(path);

  if (dir == NULL) {
    perror("\nError while opening the current directory\n");
    return;
  }

  struct dirent *entry;
  // now reading the files from the directory
  printf("\n");
  while ((entry = readdir(dir)) != NULL) {
    if (!showHidden && entry->d_name[0] == '.') {
      continue;
    } else if (showDetail) {
      printf("%u\t%ld\t%u\t%s\n", entry->d_reclen, entry->d_ino, entry->d_type,
             entry->d_name);
    } else {
      printf("%s\n", entry->d_name);
    }
  }
  printf("\n");
}
