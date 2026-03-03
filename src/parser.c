#include "parser.h"
#include <stddef.h>

static int is_instruction(char c) {
  return (c == '+' || c == '-' || c == '<' || c == '>' || c == '.' ||
          c == ',' || c == '[' || c == ']');
}

char *parse_fd(FILE *fd, char *buf) {
  // get the bf code from the file
  char c = '\0';
  while (c != EOF) {
    if (is_instruction(c)) {
      int len = strlen(buf);
      buf[len] = c;
      buf[len + 1] = '\0';
    }
    c = fgetc(fd);
  }
  return buf;
}

char *parse_c_string(char *string, char *buf) {
  // get the bf code from the string
  char c = string[0];
  size_t i = 0;
  while (c != '\0') {
    if (is_instruction(c)) {
      int len = strlen(buf);
      buf[len] = c;
      buf[len + 1] = '\0';
    }
    i++;
    c = string[i];
  }
  return buf;
}
