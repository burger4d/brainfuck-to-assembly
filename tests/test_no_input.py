from test import *

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
    code = """+++++[>+++++++>++<<-]>.>.[""" # une [ de trop
    assert run_code(code).returncode != 0

@pytest.mark.timeout(timeout)
def test_unmatched_2():
    code = """+++++[>+++++++>++<<-]>.>.][""" # une ] de trop
    assert run_code(code).returncode != 0
