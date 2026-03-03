# A basic converter from brainfuck to assembly
(x86-64, System V AMD64 ABI compliant).

## Makefile rules
- all: produces the binary
- check: starts the test suite using pytest and brainfuck-interpreter as a
reference (from here: https://pypi.org/project/brainfuck-interpreter/).
- clean: removes the produced files

## Usage of the binary
- Convert from a file: `./bf file`
- Convert from a string: `./bf -c "[code in brainfuck]"
- Convert from stdin (TODO): `echo "[code]" | ./bf`

Once the output.S is generated, you can compile it with `gcc check.c output.S`.

## TODO:
- Add the reading on stdin.
- Add tests using ','
- Optimize multiple identical operations into a single one (72 * '+1' becomes
'+72'...)
