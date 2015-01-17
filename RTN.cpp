#include </usr/include/python2.7/Python.h>
#include "pin.H"
#include "RTN.h"

PyObject* get_pointer(PyObject* self, PyObject* args) {
    PyObject* target;
    PyArg_ParseTuple(args, "L", &target);
    return PyInt_FromLong(*(ADDRINT*)target);
}

PyObject* set_pointer(PyObject* self, PyObject* args) {
    PyObject* target;
    PyObject* value;
    PyArg_ParseTuple(args, "O|O", &target, &value);
    ADDRINT* p_target = (ADDRINT*) PyInt_AsLong(target);
    ADDRINT p_value = (ADDRINT) PyInt_AsLong(value);
    //printf("*%p = %lx\n", p_target, p_value);
    *p_target = p_value;
    return Py_True;
}


void RTN_IPOINT_AFTER(
        char* name, PyObject* callback, long int return_value,
        ADDRINT* reg_gax, ADDRINT* reg_gbx, ADDRINT* reg_gcx, ADDRINT* reg_gdx,
        ADDRINT* reg_gbp, ADDRINT* reg_gsp, ADDRINT* reg_gdi, ADDRINT* reg_gsi
    ) {
    PyObject* arguments = PyTuple_New(1);

    PyObject* everything = PyDict_New();
    PyDict_SetItemString(everything, "function", PyString_FromString(name));
    PyDict_SetItemString(everything, "return", PyInt_FromLong(return_value));
    PyDict_SetItemString(everything, "reg_gax", Py_BuildValue("L", reg_gax));
    PyDict_SetItemString(everything, "reg_gbx", Py_BuildValue("L", reg_gbx));
    PyDict_SetItemString(everything, "reg_gcx", Py_BuildValue("L", reg_gcx));
    PyDict_SetItemString(everything, "reg_gdx", Py_BuildValue("L", reg_gdx));
    PyDict_SetItemString(everything, "reg_gbp", Py_BuildValue("L", reg_gbp));
    PyDict_SetItemString(everything, "reg_gsp", Py_BuildValue("L", reg_gsp));
    PyDict_SetItemString(everything, "reg_gdi", Py_BuildValue("L", reg_gdi));
    PyDict_SetItemString(everything, "reg_gsi", Py_BuildValue("L", reg_gsi));

    PyTuple_SetItem(arguments, 0, everything);
    PyObject_CallObject(callback, arguments);
}

void RTN_IPOINT_BEFORE(
        char* name, int num_args, PyObject* callback,
        long int arg0, long int arg1, long int arg2, long int arg3, long int arg4,
        long int arg5, long int arg6, long int arg7, long int arg8, long int arg9, long int arg10,
        ADDRINT* ref_arg0, ADDRINT* ref_arg1, ADDRINT* ref_arg2, ADDRINT* ref_arg3, ADDRINT* ref_arg4,
        ADDRINT* ref_arg5, ADDRINT* ref_arg6, ADDRINT* ref_arg7, ADDRINT* ref_arg8, ADDRINT* ref_arg9, ADDRINT* ref_arg10,
        ADDRINT* reg_gax, ADDRINT* reg_gbx, ADDRINT* reg_gcx, ADDRINT* reg_gdx,
        ADDRINT* reg_gbp, ADDRINT* reg_gsp, ADDRINT* reg_gdi, ADDRINT* reg_gsi
    ) {
    PyObject* arguments = PyTuple_New(1);

    PyObject* everything = PyDict_New();
    PyDict_SetItemString(everything, "function", PyString_FromString(name));
    PyDict_SetItemString(everything, "arg_0", PyInt_FromLong(arg0));
    PyDict_SetItemString(everything, "arg_1", PyInt_FromLong(arg1));
    PyDict_SetItemString(everything, "arg_2", PyInt_FromLong(arg2));
    PyDict_SetItemString(everything, "arg_3", PyInt_FromLong(arg3));
    PyDict_SetItemString(everything, "arg_4", PyInt_FromLong(arg4));
    PyDict_SetItemString(everything, "arg_5", PyInt_FromLong(arg5));
    PyDict_SetItemString(everything, "arg_6", PyInt_FromLong(arg6));
    PyDict_SetItemString(everything, "arg_7", PyInt_FromLong(arg7));
    PyDict_SetItemString(everything, "arg_8", PyInt_FromLong(arg8));
    PyDict_SetItemString(everything, "arg_9", PyInt_FromLong(arg9));
    PyDict_SetItemString(everything, "arg_10", PyInt_FromLong(arg10));
    PyDict_SetItemString(everything, "ref_arg_0", PyInt_FromLong((long int) ref_arg0));
    PyDict_SetItemString(everything, "ref_arg_1", PyInt_FromLong((long int) ref_arg1));
    PyDict_SetItemString(everything, "ref_arg_2", PyInt_FromLong((long int) ref_arg2));
    PyDict_SetItemString(everything, "ref_arg_3", PyInt_FromLong((long int) ref_arg3));
    PyDict_SetItemString(everything, "ref_arg_4", PyInt_FromLong((long int) ref_arg4));
    PyDict_SetItemString(everything, "ref_arg_5", PyInt_FromLong((long int) ref_arg5));
    PyDict_SetItemString(everything, "ref_arg_6", PyInt_FromLong((long int) ref_arg6));
    PyDict_SetItemString(everything, "ref_arg_7", PyInt_FromLong((long int) ref_arg7));
    PyDict_SetItemString(everything, "ref_arg_8", PyInt_FromLong((long int) ref_arg8));
    PyDict_SetItemString(everything, "ref_arg_9", PyInt_FromLong((long int) ref_arg9));
    PyDict_SetItemString(everything, "ref_arg_10", PyInt_FromLong((long int) ref_arg10));
    PyDict_SetItemString(everything, "reg_gax", Py_BuildValue("L", reg_gax));
    PyDict_SetItemString(everything, "reg_gbx", Py_BuildValue("L", reg_gbx));
    PyDict_SetItemString(everything, "reg_gcx", Py_BuildValue("L", reg_gcx));
    PyDict_SetItemString(everything, "reg_gdx", Py_BuildValue("L", reg_gdx));
    PyDict_SetItemString(everything, "reg_gbp", Py_BuildValue("L", reg_gbp));
    PyDict_SetItemString(everything, "reg_gsp", Py_BuildValue("L", reg_gsp));
    PyDict_SetItemString(everything, "reg_gdi", Py_BuildValue("L", reg_gdi));
    PyDict_SetItemString(everything, "reg_gsi", Py_BuildValue("L", reg_gsi));

    PyTuple_SetItem(arguments, 0, everything);

    if (PyObject_CallObject(callback, arguments)) {
    } else {
        printf("no\n");
        PyErr_Print();
    }
}

PyObject* Python_RTN_InsertCall(PyObject* self, PyObject* args) {
    PyObject* num_args;
    PyObject* function_name;
    PyObject* rtn;
    PyObject* callable;
    PyObject* ipoint;

    PyArg_ParseTuple(args, "L|O|L|L|O", &ipoint, &function_name, &rtn, &num_args, &callable);
    if (!PyCallable_Check(callable) || (long int) num_args > 10 || (long int) num_args < 0) {
        return Py_BuildValue("O", Py_False);
    }

    //cout << "function_name: " << PyString_AsString(function_name) << endl;
    RTN rtn_object = *(RTN*) rtn;
    if ((long int) ipoint == IPOINT_AFTER) {
        RTN_InsertCall(rtn_object, IPOINT_AFTER, (AFUNPTR) RTN_IPOINT_AFTER,
            IARG_ADDRINT, PyString_AsString(function_name),
            IARG_PTR, callable,
            IARG_FUNCRET_EXITPOINT_VALUE,
            IARG_REG_REFERENCE, REG_GAX,
            IARG_REG_REFERENCE, REG_GBX,
            IARG_REG_REFERENCE, REG_GCX,
            IARG_REG_REFERENCE, REG_GDX,
            IARG_REG_REFERENCE, REG_GBP,
            IARG_REG_REFERENCE, REG_STACK_PTR,
            IARG_REG_REFERENCE, REG_GDI,
            IARG_REG_REFERENCE, REG_GSI,
            IARG_END);
    } else if ((long int) ipoint == IPOINT_BEFORE) {
        RTN_InsertCall(rtn_object, IPOINT_BEFORE, (AFUNPTR) RTN_IPOINT_BEFORE,
            IARG_ADDRINT, PyString_AsString(function_name),
            IARG_ADDRINT, num_args,
            IARG_PTR, callable,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 8,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 9,
            IARG_FUNCARG_ENTRYPOINT_VALUE, 10,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 1,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 2,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 3,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 4,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 5,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 6,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 7,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 8,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 9,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 10,
            IARG_REG_REFERENCE, REG_GAX,
            IARG_REG_REFERENCE, REG_GBX,
            IARG_REG_REFERENCE, REG_GCX,
            IARG_REG_REFERENCE, REG_GDX,
            IARG_REG_REFERENCE, REG_GBP,
            IARG_REG_REFERENCE, REG_STACK_PTR,
            IARG_REG_REFERENCE, REG_GDI,
            IARG_REG_REFERENCE, REG_GSI,
            IARG_END);
    } else {
        return Py_BuildValue("O", Py_False);
    }

    return Py_BuildValue("O", Py_True);
/*
    for (int i=0; i < PyTuple_Size(args); i++) {
        cur = PyTuple_GetItem(args, i);
        if (PyString_Check(cur)) {
            printf("[str] %s\n", PyString_AsString(cur));
        } else if (PyInt_Check(cur)) {
            printf("[int] %ld\n", PyInt_AsLong(cur));
        }
    }

    return Py_BuildValue("O", Py_False);*/
}

PyObject* Python_RTN_Next(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Next(x_object);
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_Prev(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Prev(x_object);
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_Invalid(PyObject* self, PyObject* args) {
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_Invalid();
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_Valid(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    if (RTN_Valid(x_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_RTN_Name(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    return Py_BuildValue("s", RTN_Name(x_object).c_str());
}

PyObject* Python_RTN_Sym(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    SYM* sym_return = (SYM*) malloc(sizeof(SYM));
    *sym_return = RTN_Sym(x_object);
    return Py_BuildValue("L", sym_return);
}

PyObject* Python_RTN_Id(PyObject* self, PyObject* args) {
    PyObject* x;
    PyArg_ParseTuple(args, "L", &x);
    RTN x_object = *(RTN*) x;
    return Py_BuildValue("L", RTN_Id(x_object));
}

PyObject* Python_RTN_Range(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Py_BuildValue("L", RTN_Range(rtn_object));
}

PyObject* Python_RTN_Size(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Py_BuildValue("L", RTN_Size(rtn_object));
}

PyObject* Python_RTN_FindNameByAddress(PyObject* self, PyObject* args) {
    PyObject* address;
    PyArg_ParseTuple(args, "L", &address);
    ADDRINT address_object = (ADDRINT) address;
    return Py_BuildValue("s", RTN_FindNameByAddress(address_object).c_str());
}

PyObject* Python_RTN_FindByAddress(PyObject* self, PyObject* args) {
    PyObject* address;
    PyArg_ParseTuple(args, "L", &address);
    ADDRINT address_object = (ADDRINT) address;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_FindByAddress(address_object);
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_FindByName(PyObject* self, PyObject* args) {
    PyObject* img;
    PyObject* name;
    PyArg_ParseTuple(args, "L|O", &img, &name);
    IMG img_object = *(IMG*) img;
    char* name_object = PyString_AsString(name);
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_FindByName(img_object, name_object);
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_Open(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    RTN_Open(rtn_object);
    return Py_BuildValue("O", Py_True);
}

PyObject* Python_RTN_Close(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    RTN_Close(rtn_object);
    return Py_BuildValue("O", Py_True);
}

PyObject* Python_RTN_InsHead(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsHead(rtn_object);
    return Py_BuildValue("L", ins_return);
}

PyObject* Python_RTN_InsHeadOnly(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsHeadOnly(rtn_object);
    return Py_BuildValue("L", ins_return);
}

PyObject* Python_RTN_InsTail(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = RTN_InsTail(rtn_object);
    return Py_BuildValue("L", ins_return);
}

PyObject* Python_RTN_NumIns(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Py_BuildValue("L", RTN_NumIns(rtn_object));
}

PyObject* Python_RTN_Address(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    return Py_BuildValue("L", RTN_Address(rtn_object));
}

PyObject* Python_RTN_CreateAt(PyObject* self, PyObject* args) {
    PyObject* address;
    PyObject* name;
    PyArg_ParseTuple(args, "L|s", &address, &name);
    ADDRINT address_object = (ADDRINT) address;
    char* name_object = PyString_AsString(name);
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = RTN_CreateAt(address_object, name_object);
    return Py_BuildValue("L", rtn_return);
}

PyObject* Python_RTN_IsDynamic(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsDynamic(rtn_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_RTN_IsSafeForProbedInsertion(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsSafeForProbedInsertion(rtn_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_RTN_IsSafeForProbedInsertionEx(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyObject* mode;
    PyArg_ParseTuple(args, "L|L", &rtn, &mode);
    RTN rtn_object = *(RTN*) rtn;
    PROBE_MODE mode_object = *(PROBE_MODE*) mode;
    if (RTN_IsSafeForProbedInsertionEx(rtn_object, mode_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_RTN_IsSafeForProbedReplacement(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyArg_ParseTuple(args, "L", &rtn);
    RTN rtn_object = *(RTN*) rtn;
    if (RTN_IsSafeForProbedReplacement(rtn_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}

PyObject* Python_RTN_IsSafeForProbedReplacementEx(PyObject* self, PyObject* args) {
    PyObject* rtn;
    PyObject* mode;
    PyArg_ParseTuple(args, "L|L", &rtn, &mode);
    RTN rtn_object = *(RTN*) rtn;
    PROBE_MODE mode_object = *(PROBE_MODE*) mode;
    if (RTN_IsSafeForProbedReplacementEx(rtn_object, mode_object)) {
        return Py_BuildValue("O", Py_True);
    } else {
        return Py_BuildValue("O", Py_False);
    }
}