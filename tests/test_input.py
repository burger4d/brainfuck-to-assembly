from test import *

def test_simple_input():
    code = """,."""
    assert run_code(code, "A").stdout == "A"

def test_read_and_transform():
    code = """,+."""
    assert run_code(code, "A").stdout == "B"

def test_back_to_zero():
    code = """,[-]."""
    assert run_code(code).stdout == "\x00"

def test_read_multiple_chars():
    code = """,.,.,."""
    assert run_code(code, "ABC").stdout == "ABC"

def test_read_until_zero():
    code = """,[.,]"""
    assert run_code(code, "Hello\x00").stdout == "Hello"
