# A basic converter ("transpiler") from brainfuck to assembly
(x86-64, System V AMD64 ABI compliant).

## Makefile rules
- all: produces the binary
- debug: prudes the binary with the debug files
- check: starts the test suite with criterion for unit tests, and pytest for functional ones with brainfuck-interpreter as a reference (from here: https://pypi.org/project/brainfuck-interpreter/).
- clean_objs: removes all *.o files
- clean: removes all of the produced files

## Usage of the binary
- Convert from a file: `./bf file`
- Convert from a string: `./bf -c "[code]"`
- Convert from stdin (TODO): `echo "[code]" | ./bf`

Once the output.S is generated, you can compile it with `gcc check.c output.S`.

## TODO:
- ~~Add the reading on stdin~~.
- Add tests using ','.
- ~~Optimize multiple identical operations into a single one (72 * '+1' becomes
'+72'...)~~.
