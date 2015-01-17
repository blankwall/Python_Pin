/*
    Only Python_IMG_RegsymHead left
    Need SYM first.

    New in 2.14 (not implemented yet):
        LEVEL_PINCLIENT::IMG_NumRegions (IMG img)
        LEVEL_PINCLIENT::IMG_RegionHighAddress (IMG img, UINT32 n)
        LEVEL_PINCLIENT::IMG_RegionLowAddress (IMG img, UINT32 n)

*/

#include </usr/include/python2.7/Python.h>
#include "pin.H"
#include <strings.h>
#include <stdlib.h>
#include "IMG.h"

PyObject* Python_IMG_Next(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);

    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Next(*(IMG*)PyInt_AsLong(img));
    return Py_BuildValue("L", img_object);
}

PyObject* Python_IMG_Prev(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);

    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Prev(*(IMG*)PyInt_AsLong(img));
    return Py_BuildValue("L", img_object);
}

PyObject* Python_IMG_Invalid(PyObject* self, PyObject* args) {
    IMG* img_object = (IMG*) malloc(sizeof(IMG));
    *img_object = IMG_Invalid();
    return Py_BuildValue("L", img_object);
}

PyObject* Python_IMG_Valid(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_Valid(img_object)) {
        return Py_BuildValue("O", Py_True);
    }

    return Py_BuildValue("O", Py_False);
}

PyObject* Python_IMG_SecHead(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    SEC* sec = (SEC*) malloc(sizeof(SEC));
    *sec = IMG_SecHead(img_object);
    return Py_BuildValue("L", sec);
}

PyObject* Python_IMG_SecTail(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    SEC* sec = (SEC*) malloc(sizeof(SEC));
    *sec = IMG_SecTail(img_object);
    return Py_BuildValue("L", sec);
}

PyObject* Python_IMG_RegsymHead(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    // IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("O", Py_True);
}

PyObject* Python_IMG_Entry(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_Entry(img_object));
}

PyObject* Python_IMG_Name(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("s", IMG_Name(img_object).c_str());
}

PyObject* Python_IMG_Gp(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_Gp(img_object));
}

PyObject* Python_IMG_LoadOffset(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_LoadOffset(img_object));
}

PyObject* Python_IMG_LowAddress(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_LowAddress(img_object));
}

PyObject* Python_IMG_HighAddress(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_HighAddress(img_object));
}

PyObject* Python_IMG_StartAddress(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_StartAddress(img_object));
}

PyObject* Python_IMG_SizeMapped(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_SizeMapped(img_object));
}

PyObject* Python_IMG_Type(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_Type(img_object));
}

PyObject* Python_IMG_IsMainExecutable(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_IsMainExecutable(img_object)) {
        return Py_BuildValue("O", Py_True);
    }

    return Py_BuildValue("O", Py_False);
}

PyObject* Python_IMG_IsStaticExecutable(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    if (IMG_IsStaticExecutable(img_object)) {
        return Py_BuildValue("O", Py_True);
    }

    return Py_BuildValue("O", Py_False);
}

PyObject* Python_IMG_Id(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    return Py_BuildValue("L", IMG_Id(img_object));
}

PyObject* Python_IMG_FindImgById(PyObject* self, PyObject* args) {
    PyObject* id;
    PyArg_ParseTuple(args, "O", &id);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_FindImgById((UINT32) PyInt_AsLong(id));
    return Py_BuildValue("L", img);
}

PyObject* Python_IMG_FindByAddress(PyObject* self, PyObject* args) {
    PyObject* address;
    PyArg_ParseTuple(args, "O", &address);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_FindByAddress((ADDRINT) PyInt_AsLong(address));
    return Py_BuildValue("L", img);
}

PyObject* Python_IMG_Open(PyObject* self, PyObject* args) {
    PyObject* filename;
    PyArg_ParseTuple(args, "O", &filename);
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = IMG_Open(PyString_AsString(filename));
    return Py_BuildValue("L", img);
}

PyObject* Python_IMG_Close(PyObject* self, PyObject* args) {
    PyObject* img;
    PyArg_ParseTuple(args, "O", &img);
    IMG img_object = *(IMG*)PyInt_AsLong(img);
    IMG_Close(img_object);
    return Py_BuildValue("O", Py_True);
}

PyObject* Python_APP_ImgHead(PyObject* self, PyObject* args) {
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = APP_ImgHead();
    return Py_BuildValue("L", img);
}

PyObject* Python_APP_ImgTail(PyObject* self, PyObject* args) {
    IMG* img = (IMG*) malloc(sizeof(IMG));
    *img = APP_ImgTail();
    return Py_BuildValue("L", img);
}

