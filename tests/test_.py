import pytest
import brainfuck as bf
import subprocess as sp

timeout = 2

def run_code(code):
    sp.run(["rm", "-f", "a.out", "output.S"])
    sp.run(["./bf", "-c", code])
    sp.run(["gcc", "check.c", "output.S"])
    result = sp.run(["./a.out"], stdout=sp.PIPE, text=True)
    return result

def test_print_H_72_c_option():
    sp.run(["rm", "a.out", "output.S"])
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    assert run_code(code).stdout == bf.evaluate(code)


def test_print_H_72_stdin():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    sp.run(["rm", "a.out", "output.S"])
    sp.run(f"echo '{code}' | ./bf", shell=True)
    sp.run(["gcc", "check.c", "output.S"])
    result = sp.run(["./a.out"], stdout=sp.PIPE, text=True)
    assert result.stdout == bf.evaluate(code)

def test_print_H_72_file():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    sp.run(["rm", "a.out", "output.S"])
    sp.run(["./bf", "print_H.bf"])
    sp.run(["gcc", "check.c", "output.S"])
    result = sp.run(["./a.out"], stdout=sp.PIPE, text=True)
    assert result.stdout == bf.evaluate(code)

def test_print_H_and_I_same_pointer():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++.+."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_print_H_and_I_different_pointer():
    code = """+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++.>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +++++++."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_hello_world():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++
    .<<+++++++++++++++.>.+++.------.--------.>+.>."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_hello_world_print_end_only():
    code = """++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++>+++++++++++>++<<+++
    ++++++++++++>+++-------------->+>."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_simple_input():
    code = """,."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_back_to_zero():
    code = """,[-]."""
    assert run_code(code).stdout == bf.evaluate(code)

def test_empty():
    code = """"""
    assert run_code(code).stdout == bf.evaluate(code)

def test_sierpinski():
    code = """++++++++[>+>++++<<-]>++>>+<[-[>>+<<-]+>>]>+[-<<<[->[+[-]+>++>>>-<
    <]<[<]>>++++++[<<+++++>>-]+<<++.[-]<<]>.>+[>>]>+]"""
    assert run_code(code).stdout == bf.evaluate(code)

@pytest.mark.timeout(timeout)
def test_big_array():
    code = """++++[>++++++<-]>[>+++++>+++++++<<-]>>++++<[[>[[>>+<<-]<]>>>-]>-[>
    +>+<<-]>]+++++[>+++++++<<++>-]>.<<."""
    assert run_code(code).stdout == "#\n" # bf.evaluate(code) se fait timeout

@pytest.mark.timeout(timeout)
def test_unmatched_1():
    code = """+++++[>+++++++>++<<-]>.>.["""
    assert run_code(code).stdout == bf.evaluate(code)

@pytest.mark.timeout(timeout)
def test_unmatched_2():
    code = """+++++[>+++++++>++<<-]>.>.]["""
    assert run_code(code).stdout == bf.evaluate(code)
