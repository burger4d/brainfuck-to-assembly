#include <criterion/criterion.h>
#include <stdio.h>

#include "../src/parser.h"

#define BUFFER_SIZE 60000

TestSuite(parser);

Test(parser, test_same)
{
    char buf[BUFFER_SIZE] = "\0";
    parse_c_string("+++", buf);
    cr_expect(strcmp("+++", buf) == 0);
}

Test(parser, test_spaces)
{
    char buf[BUFFER_SIZE] = "\0";
    parse_c_string("+ +  + ", buf);
    cr_expect(strcmp("+++", buf) == 0);
}

Test(parser, test_h_file)
{
    char buf[BUFFER_SIZE] = "\0";
    char *h = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
              "++++++++.";
    FILE *fd = fopen("print_H.bf", "r");
    parse_fd(fd, buf);
    cr_expect(strcmp(h, buf) == 0);
}

Test(parser, test_hello_file)
{
    char buf[BUFFER_SIZE] = "\0";
    char *hello = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..++"
                  "+.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
    FILE *fd = fopen("hello.bf", "r");
    parse_fd(fd, buf);
    cr_expect(strcmp(hello, buf) == 0);
}