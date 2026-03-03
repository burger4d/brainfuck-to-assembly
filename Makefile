SRCS=src/execution.c src/converter.c src/parser.c
OBJS=$(SRCS:.c=.o)

VENV=tests/env
PY=$(VENV)/bin/python3

all: $(OBJS) # linking
	gcc $(OBJS) -o bf

%.o: %.c # compiling
	gcc -o $@ -c $^

check: all
	@python3 -m venv $(VENV)
	@$(PY) -m pip install -r tests/requirements.txt
	@$(PY) -m pytest --tb=no

clean:
	rm -rf $(OBJS) $(VENV) bf output.S a.out tests/__pycache__/
