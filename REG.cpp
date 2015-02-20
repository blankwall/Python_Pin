#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}
#include "REG.h"

SPPY::PyObject* Python_REG_is_reg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_reg(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_pseudo(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pseudo(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_gr(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_fr(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_fr(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_br(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_br(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_gr64(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr64(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_gr32(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr32(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_gr16(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr16(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_gr8(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_gr8(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_seg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_seg(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_pin_gr(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pin_gr(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_INVALID(SPPY::PyObject* self, SPPY::PyObject* args) {
    return SPPY::Py_BuildValue("k", REG_INVALID());
}

SPPY::PyObject* Python_REG_valid(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_valid(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_is_pin64(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    if (REG_is_pin64(reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_REG_FullRegName(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = REG_FullRegName(reg_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_REG_StringShort(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k", &reg);

    REG reg_object = *(REG*) reg;
    return SPPY::Py_BuildValue("s", REG_StringShort(reg_object).c_str());
}


