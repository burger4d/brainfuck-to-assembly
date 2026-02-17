#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  char buf[50] = "\0";
  // TODO: bf (stdin) et bf -c (string)
  // bf file:
  FILE *fd = fopen(argv[1], "r");
  if (!fd) {
    err(EXIT_FAILURE, "Error: can not read or find %s", argv[1]);
  }
  parse_fd(fd, buf);
  printf("\n%s\n", buf);
  return 0;
}
