#ifndef C_H
#define C_H
PyObject* Python_RTN_InsertCall(PyObject* self, PyObject* args);
PyObject* Python_RTN_Name(PyObject* self, PyObject* args);
PyObject* Python_RTN_Address(PyObject* self, PyObject* args);

/*AUTO GENERATED SKELETONS*/
PyObject* Python_RTN_Valid(PyObject* self, PyObject* args);
PyObject* Python_RTN_Id(PyObject* self, PyObject* args);
PyObject* Python_RTN_Range(PyObject* self, PyObject* args);
PyObject* Python_RTN_Size(PyObject* self, PyObject* args);
PyObject* Python_RTN_IsDynamic(PyObject* self, PyObject* args);
PyObject* Python_RTN_IsSafeForProbedInsertion(PyObject* self, PyObject* args);
PyObject* Python_RTN_IsSafeForProbedReplacement(PyObject* self, PyObject* args);

PyObject* Python_RTN_FindNameByAddress(PyObject* self, PyObject* args);
PyObject* Python_RTN_FindByName(PyObject* self, PyObject* args);
PyObject* Python_RTN_Open(PyObject* self, PyObject* args);
PyObject* Python_RTN_Close(PyObject* self, PyObject* args);
PyObject* Python_RTN_InsHead(PyObject* self, PyObject* args);

PyObject* Python_RTN_InsTail(PyObject* self, PyObject* args);
PyObject* Python_RTN_NumIns(PyObject* self, PyObject* args);
#endif
