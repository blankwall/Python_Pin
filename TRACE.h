#ifndef E_H
#define E_H

/* TRACE STUFF */
PyObject* Python_TRACE_Address(PyObject* self, PyObject* args);
PyObject* Python_TRACE_BblHead(PyObject* self, PyObject* args);
PyObject* Python_TRACE_Original(PyObject* self, PyObject* args);
PyObject* Python_TRACE_InsertCall(PyObject* self, PyObject* args);
PyObject* Python_TRACE_InsertIfCall(PyObject* self, PyObject* args);
PyObject* Python_TRACE_InsertThenCall(PyObject* self, PyObject* args);
PyObject* Python_TRACE_BblTail(PyObject* self, PyObject* args);
PyObject* Python_TRACE_Size(PyObject* self, PyObject* args);
PyObject* Python_TRACE_Rtn(PyObject* self, PyObject* args);
PyObject* Python_TRACE_HasFallThrough(PyObject* self, PyObject* args);
PyObject* Python_TRACE_NumBbl(PyObject* self, PyObject* args);
PyObject* Python_TRACE_NumIns(PyObject* self, PyObject* args);
PyObject* Python_TRACE_StubSize(PyObject* self, PyObject* args);

/* BBL STUFF */

PyObject* Python_BBL_MoveAllAttributes(PyObject* self, PyObject* args);
PyObject* Python_BBL_NumIns(PyObject* self, PyObject* args);
PyObject* Python_BBL_InsHead(PyObject* self, PyObject* args);
PyObject* Python_BBL_InsTail(PyObject* self, PyObject* args);
PyObject* Python_BBL_Next(PyObject* self, PyObject* args);
PyObject* Python_BBL_Prev(PyObject* self, PyObject* args);
PyObject* Python_BBL_Valid(PyObject* self, PyObject* args);
PyObject* Python_BBL_Original(PyObject* self, PyObject* args);
PyObject* Python_BBL_Address(PyObject* self, PyObject* args);
PyObject* Python_BBL_Size(PyObject* self, PyObject* args);
PyObject* Python_BBL_InsertCall(PyObject* self, PyObject* args);
PyObject* Python_BBL_InsertIfCall(PyObject* self, PyObject* args);
PyObject* Python_BBL_InsertThenCall(PyObject* self, PyObject* args);
PyObject* Python_BBL_HasFallThrough(PyObject* self, PyObject* args);

#endif