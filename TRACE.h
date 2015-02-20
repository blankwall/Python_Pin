#ifndef E_H
#define E_H

/* TRACE STUFF */
SPPY::PyObject* Python_TRACE_Address(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_BblHead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_Original(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_InsertIfCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_InsertThenCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_BblTail(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_Size(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_Rtn(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_NumBbl(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_NumIns(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_StubSize(SPPY::PyObject* self, SPPY::PyObject* args);

/* BBL STUFF */

SPPY::PyObject* Python_BBL_MoveAllAttributes(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_NumIns(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_InsHead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_InsTail(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Next(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Prev(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Valid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Original(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Address(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_Size(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_InsertIfCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_InsertThenCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_BBL_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args);

#endif