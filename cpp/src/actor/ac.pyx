# cython: profile=False
# distutils: language = c++
# cython: embedsignature = True
# cython: language_level = 3
# cython: c_string_encoding = default


from actor cimport exec_add as c_exec_add
from actor cimport dummy as c_dummy


def exec_add():
    return c_exec_add()


def dummy():
    return c_dummy()