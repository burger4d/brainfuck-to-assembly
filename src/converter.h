#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <string.h>

struct loop_ids
{
    int loop_id;
    int loop_stack[1024];
    int sp;

    char loop_start[32];
    char exec_start[32];
    char loop_end[32];
    char exec_end[32];
};

char *convert(char *bf_code, char *buf);

#endif
