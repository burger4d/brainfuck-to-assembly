import pytest
import brainfuck as bf
import subprocess as sp

def run_code(code):
    sp.run(["./bf", "-c", code])
    sp.run(["gcc", "check.c", "output.S"])
    result = sp.run(["./a.out"], stdout=sp.PIPE)
    return result.stdout.decode("utf-8")

def test_print_H_72():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    assert run_code(code) == bf.evaluate(code) 

def test_print_H_and_I_same_pointer():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++.+."""
    assert run_code(code) == bf.evaluate(code) 

def test_print_H_and_I_different_pointer():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++.>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    assert run_code(code) == bf.evaluate(code) 

def test_hello_world():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++
    .<<+++++++++++++++.>.+++.------.--------.>+.>."""
    assert run_code(code) == bf.evaluate(code) 

def test_hello_world_print_end_only():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++>+++++++++++>++<<+++
    ++++++++++++>+++-------------->+>."""
    assert run_code(code) == bf.evaluate(code) 
