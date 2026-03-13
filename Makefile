SRCS=src/execution.c src/converter.c src/parser.c
OBJS=$(SRCS:.c=.o)
TEST_OBJS=src/converter.o src/parser.o tests/unit_tests.o
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

VENV=tests/env
PY=$(VENV)/bin/python3

all: $(OBJS) # linking
	gcc $(LDFLAGS) $(OBJS) -o bf

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: clean_objs all

%.o: %.c # compiling
	gcc $(CFLAGS) -o $@ -c $^

check: debug tests/unit_tests.o
	gcc $(TEST_OBJS) -lcriterion -fsanitize=address -o unit
	@-./unit # if returns non-zero status because of a failed test, continue anyway
	@python3 -m venv $(VENV)
	@$(PY) -m pip install -r tests/requirements.txt
	@$(PY) -m pytest --tb=no

clean_objs:
	rm -rf $(OBJS) tests/unit_tests.o

clean: clean_objs
	rm -rf $(VENV) unit bf output.S a.out tests/__pycache__/
