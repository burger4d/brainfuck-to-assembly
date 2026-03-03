import pytest
import brainfuck as bf
import subprocess as sp

def test_print_H_72():
    code = """++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."""
    interpreter = bf.Interpreter()
    interpreter.execute(code)

def test_hello_wrold():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>."""
    interpreter = bf.Interpreter()
    interpreter.execute(code)
