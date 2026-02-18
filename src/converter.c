#include "converter.h"

char *convert(char *bf_code, char *buf)
{
    // %r8 -> pointer to stack %rsp
    // %r9 -> pointer
    // preparing the memset(array, 0, 30016)
    strcat(buf, ".global execute\n\n");
    strcat(buf, "execute:\n");
    strcat(buf, "    subq $30016, %rsp\n");
	strcat(buf, "    movq %rsp, %r8\n"); // 1st arg
	strcat(buf, "    movq %r8, %rdi\n"); // 1st arg
	strcat(buf, "    movl $0, %esi\n"); // 2nd arg
    strcat(buf, "    movl $30000, %edx\n"); // 3rd arg 
	strcat(buf, "    call memset@PLT\n"); // call memset
    strcat(buf, "    movq $0, %r9\n"); // %r9 will be our pointer

    for (size_t i = 0; i < strlen(bf_code); i++)
    {
        char c = bf_code[i];
        switch (c)
        {
            case '>':
                strcat(buf, "    addq $1, %r9\n");
                break;
            case '<':
                strcat(buf, "    subq $1, %r9\n");
                break;
            case '+':
                strcat(buf, "    addb $1, (%r8, %r9, 1)\n");
                break;
            case '-':
                strcat(buf, "    subb $1, (%r8, %r9, 1)\n");
                break;
            case '.':
                strcat(buf, "    movzbl (%r8, %r9), %edi\n");
                strcat(buf, "    call putchar@PLT\n");
                break;
            case '[':
                strcat(buf, "    jmp loop1\n\n");
                strcat(buf, "loop1:\n");
                strcat(buf, "    cmpb $0, (%r8, %r9, 1)\n");
                strcat(buf, "    je execute2\n");
                break;
            case ']':
                strcat(buf, "    jmp loop1\n\n");
                strcat(buf, "execute2:\n");
                break;
            default:
                fprintf(stderr, "char dismissed: %c\n", c);
        }
    }
    strcat(buf, "    addq $30016, %rsp\n");
    strcat(buf, "    ret\n");
    strcat(buf, ".section	.note.GNU-stack,\"\",@progbits");

    return buf;
}
