import pytest
import brainfuck as bf
import subprocess as sp

def test_1():
    code = """>++++++++[<++++++++>-]<.>++++[<++++++>-]<+.+++++++..+++.>++++++[<++++>-] <.>++++++++[<++++++++>-]<+.------------.>++++++[<++++>-]<+.---.------.--------.>+."""
    interpreter = bf.Interpreter()
    interpreter.execute(code)
