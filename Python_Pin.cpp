#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}
#include "IMG.h"
#include "INS.h"
#include "RTN.h"
#include "SYS.h"
#include "TRACE.h"
#include "./python_pin.h"
#include <string.h>
#include <stdlib.h>

void add_hook(SPPY::PyObject*** hooks, SPPY::PyObject* new_hook) {
    SPPY::PyObject** hooks_list = *hooks;
    if (hooks_list == NULL) {
        hooks_list = (SPPY::PyObject**) malloc(sizeof(SPPY::PyObject*)*2);
        hooks_list[0] = new_hook;
        hooks_list[1] = NULL;
    } else {
        int hook_count;
        for(hook_count=0; hooks_list[hook_count]; hook_count++);
        hooks_list = (SPPY::PyObject**) realloc(hooks_list, sizeof(SPPY::PyObject*)*(hook_count+2));
        hooks_list[hook_count] = new_hook;
        hooks_list[hook_count+1] = NULL;
    }

    *hooks = hooks_list;
}

void Fini(INT32, VOID*) {
    for (int i=0; fini_functions[i]; i++) {
        if (SPPY::PyObject_CallObject(fini_functions[i], NULL) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
    return;
}

SPPY::PyObject* Python_AddFiniFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&fini_functions, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
} 

SPPY::PyObject* Python_TRACE_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_trace_instrument, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
} 

SPPY::PyObject* Python_INS_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_instruction, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
} 

SPPY::PyObject* Python_IMG_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_img_load, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_IMG_AddUnloadFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback;
    SPPY::PyObject* v;
    PyArg_ParseTuple(args, "O|O", &callback, &v);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_img_unload, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_RTN_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    PyArg_ParseTuple(args, "O", &callback);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_instrument_function, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}



SPPY::PyObject* Python_PIN_AddSyscallExitFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    PyArg_ParseTuple(args, "O", &callback);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_syscall_exit, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_PIN_AddSyscallEntryFunction(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* callback = (SPPY::PyObject*) malloc(sizeof(SPPY::PyObject));
    PyArg_ParseTuple(args, "O", &callback);

    if (!PyCallable_Check(callback)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    add_hook(&hooks_syscall_entry, callback);
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

KNOB<string> KnobPythonModule(KNOB_MODE_WRITEONCE, "pintool", "m", "", "the python pintool to import");
int main(int argc, char** argv) {
    PIN_InitSymbols();
	 SPPY::Py_Initialize();
	 SPPY::PyRun_SimpleString("import sys; sys.path.append('.')\n");
    if (PIN_Init(argc, argv)) {
        printf("Failed to initialize pin.\n");
        exit(1);
    }

	 SPPY::PyObject* pin_module = 
		 Py_InitModule4("pin", methods, (char *)NULL, (SPPY::PyObject *)NULL, PYTHON_API_VERSION);
    //PyObject* pin_module = Py_InitModule("pin", methods);
    if (pin_module == NULL) {
        printf("Failed to initialize internal pin module\n");
        SPPY::PyErr_Print();
        exit(1);
    }

    PyModule_AddIntConstant(pin_module, "IPOINT_BEFORE", IPOINT_BEFORE);
    PyModule_AddIntConstant(pin_module, "IPOINT_AFTER", IPOINT_AFTER);
    PyModule_AddIntConstant(pin_module, "IMG_TYPE_STATIC", IMG_TYPE_STATIC);
    PyModule_AddIntConstant(pin_module, "IMG_TYPE_SHARED", IMG_TYPE_SHARED);
    PyModule_AddIntConstant(pin_module, "IMG_TYPE_SHAREDLIB", IMG_TYPE_SHAREDLIB);
    PyModule_AddIntConstant(pin_module, "IMG_TYPE_RELOCATABLE", IMG_TYPE_RELOCATABLE);
    PyModule_AddIntConstant(pin_module, "IARG_INVALID", IARG_INVALID);
    PyModule_AddIntConstant(pin_module, "IARG_ADDRINT", IARG_ADDRINT);
    PyModule_AddIntConstant(pin_module, "IARG_PTR", IARG_PTR);
    PyModule_AddIntConstant(pin_module, "IARG_BOOL", IARG_BOOL);
    PyModule_AddIntConstant(pin_module, "IARG_UINT32", IARG_UINT32);
    PyModule_AddIntConstant(pin_module, "IARG_INST_PTR", IARG_INST_PTR);
    PyModule_AddIntConstant(pin_module, "IARG_REG_VALUE", IARG_REG_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_REG_REFERENCE", IARG_REG_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_REG_CONST_REFERENCE", IARG_REG_CONST_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD_EA", IARG_MEMORYREAD_EA);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD2_EA", IARG_MEMORYREAD2_EA);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYWRITE_EA", IARG_MEMORYWRITE_EA);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYREAD_SIZE", IARG_MEMORYREAD_SIZE);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYWRITE_SIZE", IARG_MEMORYWRITE_SIZE);
    PyModule_AddIntConstant(pin_module, "IARG_BRANCH_TAKEN", IARG_BRANCH_TAKEN);
    PyModule_AddIntConstant(pin_module, "IARG_BRANCH_TARGET_ADDR", IARG_BRANCH_TARGET_ADDR);
    PyModule_AddIntConstant(pin_module, "IARG_FALLTHROUGH_ADDR", IARG_FALLTHROUGH_ADDR);
    PyModule_AddIntConstant(pin_module, "IARG_EXECUTING", IARG_EXECUTING);
    PyModule_AddIntConstant(pin_module, "IARG_FIRST_REP_ITERATION", IARG_FIRST_REP_ITERATION);
    PyModule_AddIntConstant(pin_module, "IARG_PREDICATE", IARG_PREDICATE);
    PyModule_AddIntConstant(pin_module, "IARG_STACK_VALUE", IARG_STACK_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_STACK_REFERENCE", IARG_STACK_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORY_VALUE", IARG_MEMORY_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORY_REFERENCE", IARG_MEMORY_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_NUMBER", IARG_SYSCALL_NUMBER);
    PyModule_AddIntConstant(pin_module, "IARG_SYSARG_REFERENCE", IARG_SYSARG_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_SYSARG_VALUE", IARG_SYSARG_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_SYSRET_VALUE", IARG_SYSRET_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_SYSRET_ERRNO", IARG_SYSRET_ERRNO);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_CALLSITE_REFERENCE", IARG_FUNCARG_CALLSITE_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_CALLSITE_VALUE", IARG_FUNCARG_CALLSITE_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_ENTRYPOINT_REFERENCE", IARG_FUNCARG_ENTRYPOINT_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCARG_ENTRYPOINT_VALUE", IARG_FUNCARG_ENTRYPOINT_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCRET_EXITPOINT_REFERENCE", IARG_FUNCRET_EXITPOINT_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_FUNCRET_EXITPOINT_VALUE", IARG_FUNCRET_EXITPOINT_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_RETURN_IP", IARG_RETURN_IP);
    PyModule_AddIntConstant(pin_module, "IARG_ORIG_FUNCPTR", IARG_ORIG_FUNCPTR);
    PyModule_AddIntConstant(pin_module, "IARG_PROTOTYPE", IARG_PROTOTYPE);
    PyModule_AddIntConstant(pin_module, "IARG_THREAD_ID", IARG_THREAD_ID);
    PyModule_AddIntConstant(pin_module, "IARG_CONTEXT", IARG_CONTEXT);
    PyModule_AddIntConstant(pin_module, "IARG_CONST_CONTEXT", IARG_CONST_CONTEXT);
    PyModule_AddIntConstant(pin_module, "IARG_PARTIAL_CONTEXT", IARG_PARTIAL_CONTEXT);
    PyModule_AddIntConstant(pin_module, "IARG_PRESERVE", IARG_PRESERVE);
    PyModule_AddIntConstant(pin_module, "IARG_RETURN_REGS", IARG_RETURN_REGS);
    PyModule_AddIntConstant(pin_module, "IARG_CALL_ORDER", IARG_CALL_ORDER);
    PyModule_AddIntConstant(pin_module, "IARG_REG_NAT_VALUE", IARG_REG_NAT_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_REG_OUTPUT_FRAME_VALUE", IARG_REG_OUTPUT_FRAME_VALUE);
    PyModule_AddIntConstant(pin_module, "IARG_REG_OUTPUT_FRAME_REFERENCE", IARG_REG_OUTPUT_FRAME_REFERENCE);
    PyModule_AddIntConstant(pin_module, "IARG_IARGLIST", IARG_IARGLIST);
    PyModule_AddIntConstant(pin_module, "IARG_FAST_ANALYSIS_CALL", IARG_FAST_ANALYSIS_CALL);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG0", IARG_SYSCALL_ARG0);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARGBASE", IARG_SYSCALL_ARGBASE);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG1", IARG_SYSCALL_ARG1);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG2", IARG_SYSCALL_ARG2);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG3", IARG_SYSCALL_ARG3);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG4", IARG_SYSCALL_ARG4);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARG5", IARG_SYSCALL_ARG5);
    PyModule_AddIntConstant(pin_module, "IARG_SYSCALL_ARGLAST", IARG_SYSCALL_ARGLAST);
    PyModule_AddIntConstant(pin_module, "IARG_G_RESULT0", IARG_G_RESULT0);
    PyModule_AddIntConstant(pin_module, "IARG_G_RETBASE", IARG_G_RETBASE);
    PyModule_AddIntConstant(pin_module, "IARG_G_RESULTLAST", IARG_G_RESULTLAST);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG0_CALLEE", IARG_G_ARG0_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARGBASE_CALLEE", IARG_G_ARGBASE_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG1_CALLEE", IARG_G_ARG1_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG2_CALLEE", IARG_G_ARG2_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG3_CALLEE", IARG_G_ARG3_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG4_CALLEE", IARG_G_ARG4_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG5_CALLEE", IARG_G_ARG5_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARGLAST_CALLEE", IARG_G_ARGLAST_CALLEE);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG0_CALLER", IARG_G_ARG0_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARGBASE_CALLER", IARG_G_ARGBASE_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG1_CALLER", IARG_G_ARG1_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG2_CALLER", IARG_G_ARG2_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG3_CALLER", IARG_G_ARG3_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG4_CALLER", IARG_G_ARG4_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARG5_CALLER", IARG_G_ARG5_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_G_ARGLAST_CALLER", IARG_G_ARGLAST_CALLER);
    PyModule_AddIntConstant(pin_module, "IARG_MEMORYOP_EA", IARG_MEMORYOP_EA);
    PyModule_AddIntConstant(pin_module, "IARG_FILE_NAME", IARG_FILE_NAME);
    PyModule_AddIntConstant(pin_module, "IARG_LINE_NO", IARG_LINE_NO);
    PyModule_AddIntConstant(pin_module, "IARG_LAST", IARG_LAST);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_FIRST", CALL_ORDER_FIRST);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_DEFAULT", CALL_ORDER_DEFAULT);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_LAST", CALL_ORDER_LAST);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_FIRST", CALL_ORDER_FIRST);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_DEFAULT", CALL_ORDER_DEFAULT);
    PyModule_AddIntConstant(pin_module, "CALL_ORDER_LAST", CALL_ORDER_LAST);

     const char* filename = KnobPythonModule.Value().c_str();
//     FILE* tool = fopen(filename, "r");
//     if (tool == NULL) {
//         perror("fopen");
//         exit(1);
//     }
// 
//     PyRun_SimpleFile(tool, filename);
//     fclose(tool);

	 SPPY::PyObject* PyFileObject = SPPY::PyFile_FromString((char *)filename, "r");
	 SPPY::PyRun_SimpleFile(SPPY::PyFile_AsFile(PyFileObject), filename);

    if (fini_functions) {
        PIN_AddFiniFunction(Fini, 0);
    }

    if (hooks_syscall_entry) {
        PIN_AddSyscallEntryFunction(SyscallEntry, 0);
    }

    if (hooks_syscall_exit) {
        PIN_AddSyscallEntryFunction(SyscallExit, 0);
    }

    if (hooks_instrument_function) {
        RTN_AddInstrumentFunction(InstrumentFunction, 0);
    }

    if (hooks_img_load) {
        IMG_AddInstrumentFunction(ImageLoad, 0);
    }

    if (hooks_img_unload) {
        IMG_AddUnloadFunction(ImageUnload, 0);
    }

    if (hooks_trace_instrument) {
        TRACE_AddInstrumentFunction(Trace, 0);
    }
    if (hooks_instruction) {
        INS_AddInstrumentFunction(Ins_Hook, 0);
    }

    PIN_StartProgram();

	 SPPY::Py_Finalize();
    return 0;
}

void Ins_Hook(INS ins, VOID *v){
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&ins));

    for (int i=0; hooks_instruction[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_instruction[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
    return;
}

void Trace(TRACE trace, VOID *v){
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&trace));

    for (int i=0; hooks_trace_instrument[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_trace_instrument[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
    return;
}

void InstrumentFunction(RTN rtn, VOID *v) {
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&rtn));

    for (int i=0; hooks_instrument_function[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_instrument_function[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
}

void SyscallExit(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v) {
    SPPY::PyObject* arguments = SPPY::PyTuple_New(2);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&ctxt));
    PyTuple_SetItem(arguments, 1, SPPY::PyInt_FromLong((long int)&std));

    for (int i=0; hooks_syscall_entry[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_syscall_exit[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
}

void SyscallEntry(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v) {
    SPPY::PyObject* arguments = SPPY::PyTuple_New(2);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&ctxt));
    PyTuple_SetItem(arguments, 1, SPPY::PyInt_FromLong((long int)&std));

    for (int i=0; hooks_syscall_entry[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_syscall_entry[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
}

void ImageLoad(IMG img, VOID *v) {
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&img));

    for (int i=0; hooks_img_load[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_img_load[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
}

void ImageUnload(IMG img, VOID* v) {
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);
    PyTuple_SetItem(arguments, 0, SPPY::PyInt_FromLong((long int)&img));

    for (int i=0; hooks_img_unload[i]; i++) {
        if (SPPY::PyObject_CallObject(hooks_img_unload[i], arguments) == NULL) {
            SPPY::PyErr_Print();
            exit(1);
        }
    }
}
