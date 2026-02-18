SRCS=src/execution.c src/converter.c src/parser.c
OBJS=$(SRCS:.c=.o)

all: $(OBJS) # linking
	gcc $(OBJS) -o bf

%.o: %.c # compiling
	gcc -o $@ -c $^

clean:
	rm -rf $(OBJS) bf output.S
