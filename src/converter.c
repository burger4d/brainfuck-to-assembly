#include "converter.h"

void init(char *buf) {
  // %r8 -> pointer to stack %rsp
  // %r9 -> pointer
  // preparing the memset(array, 0, 30016)
  strcat(buf, ".global execute\n\n");
  strcat(buf, "execute:\n");
  strcat(buf, "    subq $30016, %rsp\n");
  strcat(buf, "    movq %rsp, %r8\n");    // 1st arg
  strcat(buf, "    movq %r8, %rdi\n");    // 1st arg
  strcat(buf, "    movl $0, %esi\n");     // 2nd arg
  strcat(buf, "    movl $30016, %edx\n"); // 3rd arg
  strcat(buf, "    call memset@PLT\n");   // call memset
  strcat(buf, "    movq $0, %r9\n");      // %r9 will be our pointer
}

void finish(char *buf) {
  strcat(buf, "    addq $30016, %rsp\n");
  strcat(buf, "    ret\n");
  strcat(buf, ".section	.note.GNU-stack,\"\",@progbits");
}

char *convert(char *bf_code, char *buf) {
  int loop_id = 0;
  int loop_stack[1024];
  int sp = 0;

  init(buf);

  for (size_t i = 0; i < strlen(bf_code); i++) {
    char c = bf_code[i];
    switch (c) {
    case '>':
      strcat(buf, "    addq $1, %r9 # >\n");
      break;
    case '<':
      strcat(buf, "    subq $1, %r9 # <\n");
      break;
    case '+':
      strcat(buf, "    addb $1, (%r8, %r9, 1) # +\n");
      break;
    case '-':
      strcat(buf, "    subb $1, (%r8, %r9, 1) # -\n");
      break;
    case '.':
      strcat(buf, "    movzbl (%r8, %r9, 1), %edi # .\n");
      strcat(buf, "    call putchar@PLT\n");
      break;
    case '[':
      char loop_start[32];
      char exec_start[32];
      snprintf(loop_start, sizeof(loop_start), "\nloop%d: # [\n", loop_id);
      snprintf(exec_start, sizeof(exec_start), "    je execute%d # [\n",
               loop_id);
      loop_stack[sp++] = loop_id;
      loop_id++;
      strcat(buf, loop_start);
      strcat(buf, "    cmpb $0, (%r8, %r9, 1)\n");
      strcat(buf, exec_start);
      break;
    case ']':
      char loop_end[32];
      char exec_end[32];
      int id = loop_stack[--sp];
      snprintf(loop_end, sizeof(loop_end), "    jmp loop%d # ]\n\n", id);
      snprintf(exec_end, sizeof(exec_end), "execute%d:\n", id);
      strcat(buf, loop_end);
      strcat(buf, exec_end);
      break;
    default:
      fprintf(stderr, "char dismissed: %c\n", c);
    }
  }
  finish(buf);
  return buf;
}
