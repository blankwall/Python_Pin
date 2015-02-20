#ifndef F_H
#define F_H

SPPY::PyObject* Python_REG_is_reg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_pseudo(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_gr(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_fr(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_br(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_gr64(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_gr32(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_gr16(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_gr8(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_seg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_pin_gr(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_INVALID(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_valid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_is_pin64(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_FullRegName(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_REG_StringShort(SPPY::PyObject* self, SPPY::PyObject* args);

#endif
