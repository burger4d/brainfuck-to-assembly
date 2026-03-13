#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <criterion/redirect.h>

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
    parse_c_string("+ + +", buf);
    cr_expect(strcmp("+++", buf) == 0);
}