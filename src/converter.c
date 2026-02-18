#include "converter.h"

char *convert(char *bf_code, char *buf)
{
    // %r8 -> pointer
    // %r9 -> buffer for array values to modify
    // allocating 30008 instead of 30000 to be aligned

    // preparing the memset(array, 0, 30008)
    strcat(buf, ".global execute\n\n");
    strcat(buf, "execute:\n");
    strcat(buf, "    subq $30008, %rsp\n");
	strcat(buf, "    movq %rsp, %rdi\n"); // 1st arg
	strcat(buf, "    movl $0, %esi\n"); // 2nd arg
    strcat(buf, "    movl $30000, %edx\n"); // 3rd arg 
	strcat(buf, "    call memset@PLT\n"); // call memset
    strcat(buf, "    movq $0, %r8\n"); // %r8 will be our pointer

    for (size_t i = 0; i < strlen(bf_code); i++)
    {
        char c = bf_code[i];
        switch (c)
        {
            case '>':
                strcat(buf, "    addq $1, %r8\n");
                break;
            case '<':
                strcat(buf, "    subq $1, %r8\n");
                break;
            case '+':
                strcat(buf, "    movq (%rsp, %r8), %r9\n");
                strcat(buf, "    addq $1, %r9\n");
                strcat(buf, "    movq %r9, (%rsp, %r8)\n");
                break;
            case '-':
                strcat(buf, "    movq (%rsp, %r8), %r9\n");
                strcat(buf, "    subq $1, %r9\n");
                strcat(buf, "    movq %r9, (%rsp, %r8)\n");
                break;
            case '.':
                strcat(buf, "    movl $97, %edi\n");
                strcat(buf, "    call putchar@PLT\n");
                break;
            default:
                fprintf(stderr, "char dismissed: %c\n", c);
        }
    }
    strcat(buf, "    addq $30008, %rsp\n");
    strcat(buf, "    ret\n");
    strcat(buf, ".section	.note.GNU-stack,\"\",@progbits");

    return buf;
}
