#include "converter.h"

#include <stdlib.h>

static void init(char *buf)
{
    // Start of the source code  of output.S

    // %r12 -> pointer to stack %rsp
    // %r13 -> pointer
    // preparing the memset(array, 0, 30016)
    strcat(buf, ".global execute\n\n");
    strcat(buf, "execute:\n");
    strcat(buf, "    push %r12\n");
    strcat(buf, "    push %r13\n");
    strcat(buf, "    subq $30016, %rsp\n");
    strcat(buf, "    movq %rsp, %r12\n"); // 1st arg
    strcat(buf, "    movq %r12, %rdi\n"); // 1st arg
    strcat(buf, "    movl $0, %esi\n"); // 2nd arg
    strcat(buf, "    movl $30016, %edx\n"); // 3rd arg
    strcat(buf, "    call memset@PLT\n"); // call memset
    strcat(buf, "    movq $0, %r13\n"); // %r13 will be our pointer
}

static void finish(char *buf)
{
    // end of the source code of output.S
    strcat(buf, "    addq $30016, %rsp\n");
    strcat(buf, "    pop %r13\n");
    strcat(buf, "    pop %r12\n");
    strcat(buf, "    ret\n");
}

static void write_code(char last_char, int last_iter, char *buf,
                  struct loop_ids *loop)
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
        sprintf(buf + strlen(buf),
                       "    addb $%d, (%%r12, %%r13, 1) # +\n", last_iter);
        break;
    case '-':
        sprintf(buf + strlen(buf),
                       "    subb $%d, (%%r12, %%r13, 1) # -\n", last_iter);
        break;
    case '.':
        sprintf(buf + strlen(buf),
                       "    movzbq (%%r12, %%r13, 1), %%rdi # .\n");
        sprintf(buf + strlen(buf), "    call putchar@PLT\n");
        break;
    case '[':
        loop->loop_start[0] = '\0';
        loop->exec_start[0] = '\0';
        snprintf(loop->loop_start, sizeof(loop->loop_start),
                 "    jmp loop%d\n\nloop%d: # [\n", loop->loop_id,
                 loop->loop_id);
        snprintf(loop->exec_start, sizeof(loop->exec_start),
                 "    je execute%d # [\n", loop->loop_id);
        loop->loop_stack[loop->sp++] = loop->loop_id;
        loop->loop_id++;
        strcat(buf, loop->loop_start);
        strcat(buf, "    cmpb $0, (%r12, %r13, 1)\n");
        strcat(buf, loop->exec_start);
        break;
    case ']':
        loop->loop_end[0] = '\0';
        loop->exec_end[0] = '\0';
        int id = loop->loop_stack[--loop->sp];
        snprintf(loop->loop_end, sizeof(loop->loop_end), "    jmp loop%d # ]\n\n",
                 id);
        snprintf(loop->exec_end, sizeof(loop->exec_end), "execute%d:\n", id);
        strcat(buf, loop->loop_end);
        strcat(buf, loop->exec_end);
        break;
    default:
        fprintf(stderr, "char dismissed: %c\n", last_char);
    }
}

char *convert(char *bf_code, char *buf)
{
    // translate bf -> asm

    char last_char = '\0'; // determined by the can_repeat function
    int last_iter = 0; // how much times last_char is repeating

    struct loop_ids *loop = calloc(1, sizeof(struct loop_ids));

    init(buf);

    for (size_t i = 0; i < strlen(bf_code); i++)
    {
        char c = bf_code[i];
        if (c == '[' || c == ']')
        {
            if (last_iter > 0)
                write_code(last_char, last_iter, buf, loop);
            write_code(c, 1, buf, loop);

            last_char = '\0';
            last_iter = 0;
            continue;
        }
        if (c == last_char)
            last_iter++;
        else
        {
            if (last_iter > 0)
                write_code(last_char, last_iter, buf, loop);
            last_iter = 1;
            last_char = c;
        }
    }
    write_code(last_char, last_iter, buf, loop);
    free(loop);
    finish(buf);
    return buf;
}
