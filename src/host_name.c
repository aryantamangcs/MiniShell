#include "../include/host_name.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

char *get_hostname() {
  // opening the /etc/hostname file
  int fd = syscall(SYS_open, "/etc/hostname", O_RDONLY);
  if (fd == -1) {
    perror("Error while getting the hostname");
    exit(1);
  }

  int buff_size = 4096;
  char *host_name = (char *)malloc(4096);
  int bytes;
  int total;

  while ((bytes = syscall(SYS_read, fd, host_name, buff_size)) > 0) {
    total += bytes;
    if (total == buff_size) {
      // reallocating the memory
      buff_size *= 2;
      char *new_buffer = realloc(host_name, buff_size);
      host_name = new_buffer;
    }
  }

  host_name[strcspn(host_name, "\n")] = '\0';

  return host_name;
}
