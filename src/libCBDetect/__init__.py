"""
libCBDetect – Python bindings for the cbdetect C++ checkerboard detector.
"""
from .Checkerboard import Checkerboard  # noqa: F401


import os, sys
from pathlib import Path

# shipped DLLs are put in …/libCBDetect.libs by delvewheel
_this_dir = Path(__file__).with_suffix('').parent
libs = _this_dir.parent / (f"{_this_dir.name}.libs")
if libs.exists() and hasattr(os, "add_dll_directory"):
    os.add_dll_directory(libs)