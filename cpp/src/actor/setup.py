from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

from Cython.Build import cythonize

ext_modules = [Extension("ac",
                     ["ac.pyx"],
                     language='c++',
                     extra_objects=["libactor.a"],
                     )]

setup(
  name = 'ac',
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)
