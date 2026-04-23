from test import *

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

