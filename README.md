Python_Pin
==========

Python bindings for pin.


# Build Instructions

Pre-requisite is python-dev `sudo apt-get install python-dev` on Ubuntu.

Copy the entire directory into ~/pin/source/tools

Type make and enjoy!


# Using the Extension
Most of pin's functionality is exposed via the `pin` module, internal to the pintool. Its implementation is very similar to the way gdb handles python extensions.

To run a specific python script, for example the strace script:
`../../../pin -t obj-intel64/Python_Pin.so -m examples/strace.py -- /bin/ls`


# Current Issues

1. Some Python modules are compiled as shared objects without symbols. These modules can't be loaded from within the python pin tool. (solution is to either not use those modules, or have a custom build of python alongside the pintool)

2. Need to merge the two branches to allow 32 and 64 bit support for both. 32 bit support is fully functional but is a few commits behind.
