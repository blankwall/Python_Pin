#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}

SPPY::PyObject* Python_PIN_GetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* number;
    PyArg_ParseTuple(args, "O|O|O", &context, &std, &number);

    return SPPY::Py_BuildValue("k", PIN_GetSyscallArgument((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (int) PyInt_AsLong(number)));
}

SPPY::PyObject* Python_PIN_GetSyscallReturn(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    PyArg_ParseTuple(args, "O|O", &context, &std);

    return SPPY::Py_BuildValue("k", PIN_GetSyscallReturn((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std)));
}

SPPY::PyObject* Python_PIN_GetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    PyArg_ParseTuple(args, "O|O", &context, &std);

    return SPPY::Py_BuildValue("k", PIN_GetSyscallNumber((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std)));
}

SPPY::PyObject* Python_PIN_SetSyscallArgument(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* number;
    SPPY::PyObject* value;
    PyArg_ParseTuple(args, "O|O|O|O", &context, &std, &number, &value);

    PIN_SetSyscallArgument((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (int) PyInt_AsLong(number), (ADDRINT) PyInt_AsLong(value));
    return SPPY::Py_BuildValue("O", (&SPPY::_Py_NoneStruct));
}

SPPY::PyObject* Python_PIN_SetSyscallNumber(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* context;
    SPPY::PyObject* std;
    SPPY::PyObject* value;
    PyArg_ParseTuple(args, "O|O|O", &context, &std, &value);

    PIN_SetSyscallNumber((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (ADDRINT) PyInt_AsLong(value));
    return SPPY::Py_BuildValue("O", (&SPPY::_Py_NoneStruct));
}

