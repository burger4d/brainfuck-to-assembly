import pytest
import brainfuck as bf
import subprocess as sp

def run_code(code):
    sp.run(["./bf", "-c", code])
    sp.run(["gcc", "check.c", "output.S"])
    result = sp.run(["./a.out"], stdout=sp.PIPE)
    return result.stdout.decode("utf-8")

def run_ref(code, capsys):
    interpreter = bf.Interpreter()
    interpreter.execute(code)
    return capsys.readouterr().out
    

def test_print_H_72(capsys):
    code = """++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++."""
    assert run_code(code) == run_ref(code, capsys)
    # interpreter = bf.Interpreter()
    # interpreter.execute(code)

def test_hello_wrold():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>."""
    interpreter = bf.Interpreter()
    interpreter.execute(code)
