#include </usr/include/python2.7/Python.h>
#include "pin.H"
#include "REG.h"

PyObject* Python_REG_is_reg(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_reg(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_pseudo(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pseudo(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_gr(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_fr(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_fr(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_br(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_br(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_gr64(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr64(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_gr32(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr32(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_gr16(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr16(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_gr8(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr8(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_seg(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_seg(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_pin_gr(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pin_gr(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_INVALID(PyObject* self, PyObject* args) {
    return Py_BuildValue("L", REG_INVALID());
}

PyObject* Python_REG_valid(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_valid(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_is_pin64(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pin64(reg_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_REG_FullRegName(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = REG_FullRegName(reg_object);
    return Py_BuildValue("L", reg_return);
}

PyObject* Python_REG_StringShort(PyObject* self, PyObject* args) {
    PyObject* reg;
    PyArg_ParseTuple(args, "L", &reg);

    REG reg_object = *(REG*) reg;
    return Py_BuildValue("s", REG_StringShort(reg_object).c_str());
}


