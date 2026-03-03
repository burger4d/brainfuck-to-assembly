#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

char *parse_fd(FILE *fd, char *buf);

char *parse_c_string(char *string, char *buf);

#endif
