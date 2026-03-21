#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <string.h>

#define LOOP_STACK_SIZE 1024
#define LOOP_SIZE 32

struct loop_ids
{
    int loop_id;
    int loop_stack[LOOP_STACK_SIZE];
    int sp;

    char loop_start[LOOP_SIZE];
    char exec_start[LOOP_SIZE];
    char loop_end[LOOP_SIZE];
    char exec_end[LOOP_SIZE];
};

char *convert(char *bf_code, char *buf);

#endif
