Python_Pin
==========

Python bindings for pin.


# Build Instructions

Pre-requisite is python-dev `sudo apt-get install python-dev` on Ubuntu.

Download and extract Pin from https://software.intel.com/en-us/articles/pintool-downloads

Copy the entire directory into ~/pin/source/tools

Type make and enjoy!


# Using the Extension
Most of pin's functionality is exposed via the `pin` module, internal to the pintool. Its implementation is very similar to the way gdb handles python extensions.

To run a specific python script, for example the strace script:
`../../../pin -t obj-intel64/Python_Pin.so -m examples/strace.py -- /bin/ls`


# Current Issues

1. Some Python modules are compiled as shared objects without symbols. These modules can't be loaded from within the python pin tool. (solution is to either not use those modules, or have a custom build of python alongside the pintool)

2. Need to work on compiling for Mac and ~~Windows~~ (check the branch Windows is supported). Code should be portable but makefile may need to be updated.
