#include "parser.h"

static int is_instruction(char c) {
  return (c == '+' || c == '-' || c == '<' || c == '>' || c == '.' ||
          c == ',' || c == '[' || c == ']');
}

char *parse_fd(FILE *fd, char *buf) {
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
