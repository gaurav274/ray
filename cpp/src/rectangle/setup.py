from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

from Cython.Build import cythonize

ext_modules = [Extension("test",
                     ["rect.pyx"],
                     language='c++',
                     extra_objects=["libR.a"],
                     )]

setup(
  name = 'test',
  cmdclass = {'build_ext': build_ext},
  ext_modules = ext_modules
)
