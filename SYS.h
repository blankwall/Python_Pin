#ifndef D_H
#define D_H

SPPY::PyObject* Python_PIN_GetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_PIN_GetSyscallReturn(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_PIN_GetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_PIN_SetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_PIN_SetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args);

#endif