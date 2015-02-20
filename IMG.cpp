/*
    Only Python_IMG_RegsymHead left
    Need SYM first.

    New in 2.14 (not implemented yet):
        LEVEL_PINCLIENT::IMG_NumRegions (IMG img)
        LEVEL_PINCLIENT::IMG_RegionHighAddress (IMG img, UINT32 n)
        LEVEL_PINCLIENT::IMG_RegionLowAddress (IMG img, UINT32 n)

*/

#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}
#include <string.h>
#include <stdlib.h>
#include "IMG.h"

SPPY::PyObject* Python_IMG_Next(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);

    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Next(*(IMG*)PyInt_AsLong(img));
    return SPPY::Py_BuildValue("k", img_object);
}

SPPY::PyObject* Python_IMG_Prev(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);

    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Prev(*(IMG*)PyInt_AsLong(img));
    return SPPY::Py_BuildValue("k", img_object);
}

SPPY::PyObject* Python_IMG_Invalid(SPPY::PyObject* self, SPPY::PyObject* args) {
    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Invalid();
    return SPPY::Py_BuildValue("k", img_object);
}

SPPY::PyObject* Python_IMG_Valid(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_Valid(img_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    }

    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
}

SPPY::PyObject* Python_IMG_SecHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    SEC* sec = (SEC*) malloc(sizeof(SEC));
    *sec = IMG_SecHead(img_object);
    return SPPY::Py_BuildValue("k", sec);
}

SPPY::PyObject* Python_IMG_SecTail(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    SEC* sec = (SEC*) malloc(sizeof(SEC));
    *sec = IMG_SecTail(img_object);
    return SPPY::Py_BuildValue("k", sec);
}

SPPY::PyObject* Python_IMG_RegsymHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    // IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_IMG_Entry(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_Entry(img_object));
}

SPPY::PyObject* Python_IMG_Name(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("s", IMG_Name(img_object).c_str());
}

SPPY::PyObject* Python_IMG_Gp(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_Gp(img_object));
}

SPPY::PyObject* Python_IMG_LoadOffset(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_LoadOffset(img_object));
}

SPPY::PyObject* Python_IMG_LowAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_LowAddress(img_object));
}

SPPY::PyObject* Python_IMG_HighAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_HighAddress(img_object));
}

SPPY::PyObject* Python_IMG_StartAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_StartAddress(img_object));
}

SPPY::PyObject* Python_IMG_SizeMapped(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_SizeMapped(img_object));
}

SPPY::PyObject* Python_IMG_Type(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_Type(img_object));
}

SPPY::PyObject* Python_IMG_IsMainExecutable(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_IsMainExecutable(img_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    }

    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
}

SPPY::PyObject* Python_IMG_IsStaticExecutable(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_IsStaticExecutable(img_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    }

    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
}

SPPY::PyObject* Python_IMG_Id(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return SPPY::Py_BuildValue("k", IMG_Id(img_object));
}

SPPY::PyObject* Python_IMG_FindImgById(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* id;
    PyArg_ParseTuple(args, "O", &id);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_FindImgById((UINT32) PyInt_AsLong(id));
    return SPPY::Py_BuildValue("k", img);
}

SPPY::PyObject* Python_IMG_FindByAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* address;
    PyArg_ParseTuple(args, "O", &address);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_FindByAddress((ADDRINT) PyInt_AsLong(address));
    return SPPY::Py_BuildValue("k", img);
}

SPPY::PyObject* Python_IMG_Open(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* filename;
    PyArg_ParseTuple(args, "O", &filename);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_Open(PyString_AsString(filename));
    return SPPY::Py_BuildValue("k", img);
}

SPPY::PyObject* Python_IMG_Close(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    IMG_Close(img_object);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_APP_ImgHead(SPPY::PyObject* self, SPPY::PyObject* args) {
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = APP_ImgHead();
    return SPPY::Py_BuildValue("k", img);
}

SPPY::PyObject* Python_APP_ImgTail(SPPY::PyObject* self, SPPY::PyObject* args) {
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = APP_ImgTail();
    return SPPY::Py_BuildValue("k", img);
}

