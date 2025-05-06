#include "../include/builtins.h"
#include "../include/host_name.h"
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

char *current_directory;

char *get_prompt() {
  int prompt_size = 100;
  char *host_name = get_hostname();

  current_directory = custom_pwd();

  // only getting the last direcotry using strtok
  char *last = basename(current_directory);

  char *prompt = (char *)malloc(prompt_size);
  snprintf(prompt, prompt_size, "[mini-shell@%s %s ]$ ", host_name, last);
  return prompt;
}

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

void custom_cat(int argc, char **args) {

  int buff_size = 4096;
  char *buffer = (char *)malloc(4096);
  int i;
  if (argc > 1) {
    for (i = 1; args[i] != NULL; i++) {
      // reading from the file by opening
      int fd = syscall(SYS_open, args[i], O_RDONLY);
      if (fd == -1) {
        perror("\nCouldn't open  file\n");
        return;
      }

      int bytes;
      int total = 0;
      while ((bytes = syscall(SYS_read, fd, buffer + total,
                              buff_size - total)) > 0) {
        total += bytes;

        // if buffer full then reallocating the buffer
        if (total == buff_size) {
          buff_size *= 2;
          buffer = (char *)realloc(buffer, buff_size);
        }
      }
    }
  }
  printf("%s\n", buffer);
}

char *custom_pwd() {

  char *buff = (char *)malloc(100);
  char *current_directory = getcwd(buff, 100);

  return buff;
}

void custom_clear() {
  // writing the command to the ansi terminal

  char *clear_command = "\033[H\033[2J"; // code to move cursor to the top left
                                         // corner and clear the screen

  syscall(SYS_write, 1, clear_command, 7);
}

void custom_cd(int argc, char *args[]) {

  if (argc > 2) {
    perror("Invalid argument");
    return;
  }

  char *path_name = args[1];

  if (chdir(path_name) == -1) {
    perror("Cannot change the directory.");
    return;
  }
}
