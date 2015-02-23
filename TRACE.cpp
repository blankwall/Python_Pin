#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}
#include "TRACE.h"

/********* TRACE STUFF ****************/

/* VERIFIED */
SPPY::PyObject* Python_TRACE_Address(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    //EACH LONG IS LIKE A DEREFERENCE SO FIRST IS AN ADDRESS TO THE ACTUAL VALUE SECOND IS THE VALUE
    return SPPY::Py_BuildValue("k", SPPY::Py_BuildValue("k", TRACE_Address((TRACE)PyInt_AsLong(trace))));
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_Original(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

    return SPPY::Py_BuildValue("k", TRACE_Original((TRACE)PyInt_AsLong(trace)));
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_BblHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    BBL *need  = (BBL*) malloc(sizeof(BBL));

    *need = TRACE_BblHead(*(TRACE*) PyInt_AsLong(trace));
    return SPPY::Py_BuildValue("k", need);
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_BblTail(SPPY::PyObject* self, SPPY::PyObject* args) {
   SPPY::PyObject* trace;
   PyArg_ParseTuple(args, "O",&trace);
   BBL *need  = (BBL*) malloc(sizeof(BBL));

   *need = TRACE_BblTail(*(TRACE*) PyInt_AsLong(trace));
   return SPPY::Py_BuildValue("k", need);
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_Size(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O", &trace);

    return SPPY::Py_BuildValue("k", TRACE_Size(*(TRACE*)PyInt_AsLong(trace)));
}

/* NEEDS TESTING IN RTN CLASS*/
SPPY::PyObject* Python_TRACE_Rtn(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    RTN *rtn  = (RTN*) malloc(sizeof(RTN));

    *rtn =  TRACE_Rtn(*(TRACE*)PyInt_AsLong(trace));
    return SPPY::Py_BuildValue("k", rtn);
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_NumBbl(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

     return SPPY::Py_BuildValue("k", TRACE_NumBbl(*(TRACE*)PyInt_AsLong(trace)));
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_NumIns(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

    return SPPY::Py_BuildValue("k", TRACE_NumIns(*(TRACE*)PyInt_AsLong(trace)));
}

/* VERIFIED */
SPPY::PyObject* Python_TRACE_StubSize(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
	return SPPY::Py_BuildValue("k", TRACE_StubSize(*(TRACE*)PyInt_AsLong(trace)));
}

/* NVERIFIED */
SPPY::PyObject* Python_TRACE_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

    return SPPY::Py_BuildValue("k", TRACE_HasFallThrough(*(TRACE*)PyInt_AsLong(trace)));
}


/* Need to figure these 3 out */
SPPY::PyObject* Python_TRACE_InsertIfCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); 
}

SPPY::PyObject* Python_TRACE_InsertThenCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); //SPPY::Py_BuildValue("k", TRACE_Address((TRACE)PyInt_AsLong(trace))));
}

SPPY::PyObject* Python_TRACE_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args){
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);

    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); //SPPY::Py_BuildValue("k", TRACE_Address((TRACE)PyInt_AsLong(trace))));
}

/************ BBL STUFF ******************/

/* VERIFIED */
SPPY::PyObject* Python_BBL_MoveAllAttributes(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* bbl_src, * bbl_dest;
    PyArg_ParseTuple(args, "k|k", &bbl_src, &bbl_dest);
    BBL src = *(BBL *) bbl_src;
    BBL dest = *(BBL *) bbl_dest;
  
    BBL_MoveAllAttributes(src, dest);
    return SPPY::Py_BuildValue("O", (&SPPY::_Py_NoneStruct)); 
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_NumIns(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_NumIns(*(BBL*)trace)); 
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_HasFallThrough(*(BBL*)trace)); 
}

/*NEED TO IMPLEMENT INS FIRST */
SPPY::PyObject* Python_BBL_InsHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O", &trace);
    INS *need  = (INS*) malloc(sizeof(INS));

    *need = BBL_InsHead(*(BBL*) PyInt_AsLong(trace));
    return SPPY::Py_BuildValue("k", need); 
}

/*NEED TO IMPLEMENT INS FIRST */
SPPY::PyObject* Python_BBL_InsTail(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); 
}

/* VERIFIED*/
SPPY::PyObject* Python_BBL_Next(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    BBL *need  = (BBL*) malloc(sizeof(BBL));

    *need = BBL_Next(*(BBL*) PyInt_AsLong(trace));
    return SPPY::Py_BuildValue("k", need);
}

/* VERFIED */
SPPY::PyObject* Python_BBL_Prev(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    BBL* prev  = (BBL*) malloc(sizeof(BBL));

    *prev = BBL_Prev(*(BBL*) PyInt_AsLong(trace));
    return SPPY::Py_BuildValue("k", prev);
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_Valid(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_Valid(*(BBL*)trace));
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_Original(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_Original(*(BBL*)trace));
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_Address(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_Address(*(BBL*)trace));
}

/* VERIFIED */
SPPY::PyObject* Python_BBL_Size(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
     PyArg_ParseTuple(args, "k",&trace);
    return SPPY::Py_BuildValue("k", BBL_Size(*(BBL*)trace));
}

/* NOT IMPLEMENTED  */
SPPY::PyObject* Python_BBL_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); 
}

SPPY::PyObject* Python_BBL_InsertIfCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); 
}

SPPY::PyObject* Python_BBL_InsertThenCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* trace;
    PyArg_ParseTuple(args, "O",&trace);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct)); 
}
