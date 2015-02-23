#ifndef C_H
#define C_H
SPPY::PyObject* Python_RTN_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Name(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Address(SPPY::PyObject* self, SPPY::PyObject* args);

/*AUTO GENERATED SKELETONS*/
SPPY::PyObject* Python_RTN_Valid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Id(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Range(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Size(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_IsDynamic(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_IsSafeForProbedInsertion(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_IsSafeForProbedReplacement(SPPY::PyObject* self, SPPY::PyObject* args);

SPPY::PyObject* Python_RTN_FindNameByAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_FindByName(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Open(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_Close(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_InsHead(SPPY::PyObject* self, SPPY::PyObject* args);

SPPY::PyObject* Python_RTN_InsTail(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_RTN_NumIns(SPPY::PyObject* self, SPPY::PyObject* args);
#endif
