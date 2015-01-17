#include </usr/include/python2.7/Python.h>
#include "pin.H"

PyObject* Python_PIN_GetSyscallArgument(PyObject* self, PyObject* args) {
    PyObject* context;
    PyObject* std;
    PyObject* number;
    PyArg_ParseTuple(args, "O|O|O", &context, &std, &number);

    return Py_BuildValue("L", PIN_GetSyscallArgument((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (int) PyInt_AsLong(number)));
}

PyObject* Python_PIN_GetSyscallReturn(PyObject* self, PyObject* args) {
    PyObject* context;
    PyObject* std;
    PyArg_ParseTuple(args, "O|O", &context, &std);

    return Py_BuildValue("L", PIN_GetSyscallReturn((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std)));
}

PyObject* Python_PIN_GetSyscallNumber(PyObject* self, PyObject* args) {
    PyObject* context;
    PyObject* std;
    PyArg_ParseTuple(args, "O|O", &context, &std);

    return Py_BuildValue("L", PIN_GetSyscallNumber((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std)));
}

PyObject* Python_PIN_SetSyscallArgument(PyObject* self, PyObject* args) {
    PyObject* context;
    PyObject* std;
    PyObject* number;
    PyObject* value;
    PyArg_ParseTuple(args, "O|O|O|O", &context, &std, &number, &value);

    PIN_SetSyscallArgument((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (int) PyInt_AsLong(number), (ADDRINT) PyInt_AsLong(value));
    return Py_BuildValue("O", Py_None);
}

PyObject* Python_PIN_SetSyscallNumber(PyObject* self, PyObject* args) {
    PyObject* context;
    PyObject* std;
    PyObject* value;
    PyArg_ParseTuple(args, "O|O|O", &context, &std, &value);

    PIN_SetSyscallNumber((CONTEXT*) *(CONTEXT**)PyInt_AsLong(context), (SYSCALL_STANDARD) *(SYSCALL_STANDARD*)PyInt_AsLong(std), (ADDRINT) PyInt_AsLong(value));
    return Py_BuildValue("O", Py_None);
}

