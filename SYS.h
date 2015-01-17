#ifndef D_H
#define D_H

PyObject* Python_PIN_GetSyscallArgument(PyObject* self, PyObject* args);
PyObject* Python_PIN_GetSyscallReturn(PyObject* self, PyObject* args);
PyObject* Python_PIN_GetSyscallNumber(PyObject* self, PyObject* args);
PyObject* Python_PIN_SetSyscallArgument(PyObject* self, PyObject* args);
PyObject* Python_PIN_SetSyscallNumber(PyObject* self, PyObject* args);

#endif