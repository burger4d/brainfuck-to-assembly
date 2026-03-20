#include "converter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void init(char *buf)
{
    strcat(buf, ".global execute\n\n");
    strcat(buf, "execute:\n");
    strcat(buf, "    push %r12\n");
    strcat(buf, "    push %r13\n");
    strcat(buf, "    subq $30016, %rsp\n");
    strcat(buf, "    movq %rsp, %r12\n");
    strcat(buf, "    movq %r12, %rdi\n");
    strcat(buf, "    movl $0, %esi\n");
    strcat(buf, "    movl $30016, %edx\n");
    strcat(buf, "    call memset@PLT\n");
    strcat(buf, "    movq $0, %r13\n");
}

static void finish(char *buf)
{
    strcat(buf, "    addq $30016, %rsp\n");
    strcat(buf, "    pop %r13\n");
    strcat(buf, "    pop %r12\n");
    strcat(buf, "    ret\n");
}

static void write_code(char last_char, int last_iter, char *buf, struct loop_ids *loop)
{
    switch (last_char)
    {
        case '>':
            sprintf(buf + strlen(buf), "    addq $%d, %%r13 # >\n", last_iter);
            break;
        case '<':
            sprintf(buf + strlen(buf), "    subq $%d, %%r13 # <\n", last_iter);
            break;
        case '+':
            sprintf(buf + strlen(buf), "    addb $%d, (%%r12, %%r13, 1) # +\n", last_iter);
            break;
        case '-':
            sprintf(buf + strlen(buf), "    subb $%d, (%%r12, %%r13, 1) # -\n", last_iter);
            break;
        case '.':
            sprintf(buf + strlen(buf), "    movzbq (%%r12, %%r13, 1), %%rdi # .\n");
            sprintf(buf + strlen(buf), "    call putchar@PLT\n");
            break;
        case '[':
        {
            int id = loop->loop_id++;
            loop->loop_stack[loop->sp++] = id;

            sprintf(buf + strlen(buf), "loop%d:\n", id);
            strcat(buf, "    cmpb $0, (%r12, %r13, 1)\n");
            sprintf(buf + strlen(buf), "    je execute%d\n", id);
            break;
        }
        case ']':
        {
            int id = loop->loop_stack[--loop->sp];
            sprintf(buf + strlen(buf), "    jmp loop%d\n", id);
            sprintf(buf + strlen(buf), "execute%d:\n", id);
            break;
        }
        default:
            fprintf(stderr, "char dismissed: %c\n", last_char);
    }
}

char *convert(char *bf_code, char *buf)
{
    char last_char = '\0';
    int last_iter = 0;
    int inside_loop = 0; // on veut track les loop nesting

    struct loop_ids *loop = calloc(1, sizeof(struct loop_ids));
    init(buf);

    for (size_t i = 0; i < strlen(bf_code); i++)
    {
        char c = bf_code[i];

        // Si on arrive à char non repetable on flush
        if (c == '[' || c == ']' || c == '.')
        {
            if (last_iter > 0)
                write_code(last_char, last_iter, buf, loop);

            write_code(c, 1, buf, loop);

            if (c == '[')
                inside_loop++;
            else if (c == ']')
                inside_loop--;

            last_char = '\0';
            last_iter = 0;
            continue;
        }

        if (c == last_char)
        {
            if (inside_loop && (c == '+' || c == '-'))
                write_code(c, 1, buf, loop);
            else
                last_iter++;
        }
        else
        {
            if (last_iter > 0)
                write_code(last_char, last_iter, buf, loop);

            last_char = c;
            last_iter = 1;

            if (inside_loop && (c == '+' || c == '-'))
            {
                write_code(c, 1, buf, loop);
                last_iter = 0;
                last_char = '\0';
            }
        }
    }

    if (last_iter > 0)
        write_code(last_char, last_iter, buf, loop);

    free(loop);
    finish(buf);
    return buf;
}
