#ifndef F_H
#define F_H

PyObject* Python_REG_is_reg(PyObject* self, PyObject* args);
PyObject* Python_REG_is_pseudo(PyObject* self, PyObject* args);
PyObject* Python_REG_is_gr(PyObject* self, PyObject* args);
PyObject* Python_REG_is_fr(PyObject* self, PyObject* args);
PyObject* Python_REG_is_br(PyObject* self, PyObject* args);
PyObject* Python_REG_is_gr64(PyObject* self, PyObject* args);
PyObject* Python_REG_is_gr32(PyObject* self, PyObject* args);
PyObject* Python_REG_is_gr16(PyObject* self, PyObject* args);
PyObject* Python_REG_is_gr8(PyObject* self, PyObject* args);
PyObject* Python_REG_is_seg(PyObject* self, PyObject* args);
PyObject* Python_REG_is_pin_gr(PyObject* self, PyObject* args);
PyObject* Python_REG_INVALID(PyObject* self, PyObject* args);
PyObject* Python_REG_valid(PyObject* self, PyObject* args);
PyObject* Python_REG_is_pin64(PyObject* self, PyObject* args);
PyObject* Python_REG_FullRegName(PyObject* self, PyObject* args);
PyObject* Python_REG_StringShort(PyObject* self, PyObject* args);

#endif
