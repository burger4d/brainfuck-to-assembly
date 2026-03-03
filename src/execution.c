#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "parser.h"

#define BUFFER_SIZE 60000

int main(int argc, char *argv[]) {
  char buf[BUFFER_SIZE] = "\0";
  char result[BUFFER_SIZE] = "\0";
  // TODO: bf (stdin)
  // bf file:
  if (!strcmp("-c", argv[1])) {
    // ./bf -c "..."
    parse_c_string(argv[2], buf);
  } else {
    // ./bf file.bf
    FILE *fd = fopen(argv[1], "r");
    if (!fd) {
      err(EXIT_FAILURE, "Error: can not read or find %s", argv[1]);
    }
    parse_fd(fd, buf);
    fclose(fd);
    convert(buf, result);
    FILE *output = fopen("output.S", "w");
    if (!output) {
      err(EXIT_FAILURE, "Error: can not write");
    }
    fprintf(output, "%s", result);
    fclose(output);
  }
  return 0;
}
