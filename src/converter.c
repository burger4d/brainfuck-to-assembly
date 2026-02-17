#include "converter.h"

char *convert(char *bf_code, char *buf)
{
    // preparing the memset(array, 0, 30000 * sizeof(int))
    strcat(buf, ".global execute\n\n");
    strcat(buf, "execute:\n");
	strcat(buf, "    movq %rax, %rdi\n"); // 1st arg
	strcat(buf, "    movl $0, %esi\n"); // 2nd arg
    strcat(buf, "    movl $120000, %edx\n"); // 3rd arg 
	strcat(buf, "    call memset@PLT\n"); // call memset

    for (size_t i = 0; i < strlen(bf_code); i++)
    {
        char c = bf_code[i];
        switch (c)
        {
            case '+':
                strcat(buf, "    addl $1 %\n");
                break;
            case '-':
                strcat(buf, "    subl $1 %\n");
                break;
            default:
                fprintf(stderr, "char dismissed: %c\n", c);
        }
    }
    return buf;
}
