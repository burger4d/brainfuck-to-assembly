import pytest
import brainfuck as bf
import subprocess as sp

timeout = 2

def run_code(code, stdin_input=""):
    sp.run(["rm", "-f", "a.out", "output.S"])
    bf_result = sp.run(["./bf", "-c", code], stdout=sp.PIPE, stderr=sp.PIPE, text=True)
    if bf_result.returncode != 0:
        return bf_result  # early exit, returncode != 0, test will pass
    gcc_result = sp.run(["gcc", "check.c", "output.S"], stdout=sp.PIPE, stderr=sp.PIPE)
    if gcc_result.returncode != 0:
        return gcc_result
    result = sp.run(["./a.out"], stdout=sp.PIPE, stderr=sp.PIPE, input=stdin_input, text=True)
    return result
