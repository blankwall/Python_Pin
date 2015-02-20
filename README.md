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

2. Need to work on compiling for Mac and Windows. Code should be portable but makefile may need to be updated.

====================================================
# REMARK on Windows
====================================================
I compiled the project Python_Pin on Windows under MS Visual Studio 2005 but I found errors at compile time.

Files pin.h and python.h should be different namespace.

I placed python.h in namespace SPPY:

`namespace SPPY` 

`{`

`#include <Python.h>`

`}`

This helped

This code don't work on Windows:

`//     FILE* tool = fopen(filename, "r");`

`//     if (tool == NULL) {`

`//         perror("fopen");`

`//         exit(1);`

`//     }`

`//`

`// 	 SPPY::PyRun_SimpleFile(tool, filename);`

`//     fclose(tool);`

And replace on this code:

	 SPPY::PyObject* PyFileObject = SPPY::PyFile_FromString((char *)filename, "r");

	 SPPY::PyRun_SimpleFile(SPPY::PyFile_AsFile(PyFileObject), filename);

