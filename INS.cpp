#include "pin.H"
namespace SPPY 
{
#include <Python.h>
}
#include "INS.h"

void INS_IPOINT_BEFORE(SPPY::PyObject* callback, INS ins_object, UINT32 num_operands, unsigned int rax, unsigned int rbx, unsigned int rcx, unsigned int rdx, unsigned int rdi, unsigned int rsi, unsigned int rbp, unsigned int rsp, UINT64 memop0, unsigned int memop1, unsigned int memop2) {
    SPPY::PyObject* dict = SPPY::PyDict_New();
    SPPY::PyObject* arguments = SPPY::PyTuple_New(1);

    #ifdef __i386__
    SPPY::PyDict_SetItemString(dict, "REG_EAX", SPPY::PyInt_FromLong(rax));
    SPPY::PyDict_SetItemString(dict, "REG_EBX", SPPY::PyInt_FromLong(rbx));
    SPPY::PyDict_SetItemString(dict, "REG_ECX", SPPY::PyInt_FromLong(rcx));
    SPPY::PyDict_SetItemString(dict, "REG_EDX", SPPY::PyInt_FromLong(rdx));
    SPPY::PyDict_SetItemString(dict, "REG_EDI", SPPY::PyInt_FromLong(rdi));
    SPPY::PyDict_SetItemString(dict, "REG_ESI", SPPY::PyInt_FromLong(rsi));
    SPPY::PyDict_SetItemString(dict, "REG_EBP", SPPY::PyInt_FromLong(rbp));
    SPPY::PyDict_SetItemString(dict, "REG_ESP", SPPY::PyInt_FromLong(rsp));
    switch (num_operands) {
        case 0:
        break;
        case 1:
        SPPY::PyDict_SetItemString(dict, "MEM_OP0", SPPY::PyInt_FromLong(memop0));
        case 2:
        SPPY::PyDict_SetItemString(dict, "MEM_OP1", SPPY::PyInt_FromLong(memop1));
        case 3:
        SPPY::PyDict_SetItemString(dict, "MEM_OP2", SPPY::PyInt_FromLong(memop2));
        break;
    }

    #endif
    #ifdef __x86_64__

    ADDRINT k = 0;

    PIN_LockClient();
    IMG img = IMG_FindByAddress(INS_Address(ins_object));
    PIN_UnlockClient();

    if (IMG_Valid(img) && IMG_IsMainExecutable(img)){
        if (INS_OperandCount(ins_object) > 1 && INS_MemoryOperandIsWritten(ins_object, 0)){
           k = *(ADDRINT*)memop0;
        }
    }
    

    SPPY::PyDict_SetItemString(dict, "VAL", SPPY::PyInt_FromLong(k));
    SPPY::PyDict_SetItemString(dict, "REG_RAX", SPPY::PyInt_FromLong(rax));
    SPPY::PyDict_SetItemString(dict, "REG_RBX", SPPY::PyInt_FromLong(rbx));
    SPPY::PyDict_SetItemString(dict, "REG_RCX", SPPY::PyInt_FromLong(rcx));
    SPPY::PyDict_SetItemString(dict, "REG_RDX", SPPY::PyInt_FromLong(rdx));
    SPPY::PyDict_SetItemString(dict, "REG_RDI", SPPY::PyInt_FromLong(rdi));
    SPPY::PyDict_SetItemString(dict, "REG_RSI", SPPY::PyInt_FromLong(rsi));
    SPPY::PyDict_SetItemString(dict, "REG_RBP", SPPY::PyInt_FromLong(rbp));
    SPPY::PyDict_SetItemString(dict, "REG_RSP", SPPY::PyInt_FromLong(rsp));
    SPPY::PyDict_SetItemString(dict, "IP", SPPY::PyInt_FromLong(INS_Address(ins_object)));
   // SPPY::PyDict_SetItemString(dict, "EA", SPPY::PyInt_FromLong(ea));
    SPPY::PyDict_SetItemString(dict, "mnemonic", SPPY::PyString_FromString(INS_Disassemble(ins_object).c_str()));
    switch (num_operands) {
        case 0:
        break;
        case 1:
        SPPY::PyDict_SetItemString(dict, "MEM_OP0", SPPY::PyInt_FromLong(memop0));
        break;
        case 2:
        SPPY::PyDict_SetItemString(dict, "MEM_OP0", SPPY::PyInt_FromLong(memop0));
        SPPY::PyDict_SetItemString(dict, "MEM_OP1", SPPY::PyInt_FromLong(memop1));
        break;
        case 3:
        SPPY::PyDict_SetItemString(dict, "MEM_OP0", SPPY::PyInt_FromLong(memop0));
        SPPY::PyDict_SetItemString(dict, "MEM_OP1", SPPY::PyInt_FromLong(memop1));
        SPPY::PyDict_SetItemString(dict, "MEM_OP2", SPPY::PyInt_FromLong(memop2));
        break;
    }
    #endif
    PyTuple_SetItem(arguments, 0, dict);
    SPPY::PyObject_CallObject(callback, arguments);
}

void INS_IPOINT_AFTER(SPPY::PyObject* callback, INS ins_object, UINT32 num_operands, UINT64 rax) {
}


SPPY::PyObject* Python_INS_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* callable;
    SPPY::PyObject* ipoint;

    PyArg_ParseTuple(args, "k|k|O", &ipoint, &ins, &callable);
    if (!PyCallable_Check(callable)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }

    INS ins_object = *(INS*) ins;
    UINT32 num_operands = INS_MemoryOperandCount(ins_object);
    num_operands = num_operands;
    if ((long int) ipoint == IPOINT_BEFORE) {
        INS_InsertCall(
            ins_object,
            IPOINT_BEFORE,
            (AFUNPTR) INS_IPOINT_BEFORE,
            IARG_PTR, callable,
            IARG_PTR, ins_object,
            IARG_UINT32, num_operands,
            #ifdef __i386__
            IARG_REG_VALUE, REG_GAX,
            IARG_REG_VALUE, REG_GBX,
            IARG_REG_VALUE, REG_GCX,
            IARG_REG_VALUE, REG_GDX,
            IARG_REG_VALUE, REG_GDI,
            IARG_REG_VALUE, REG_GSI,
            IARG_REG_VALUE, REG_GBP,
            IARG_REG_VALUE, REG_STACK_PTR,
            (num_operands >= 1 ? IARG_MEMORYOP_EA : IARG_UINT32), 0,
            (num_operands >= 2 ? IARG_MEMORYOP_EA : IARG_UINT32), 1,
            (num_operands >= 3 ? IARG_MEMORYOP_EA : IARG_UINT32), 2,
            #endif
            #ifdef __x86_64__
            IARG_REG_VALUE, REG_GAX,
            IARG_REG_VALUE, REG_GBX,
            IARG_REG_VALUE, REG_GCX,
            IARG_REG_VALUE, REG_GDX,
            IARG_REG_VALUE, REG_GDI,
            IARG_REG_VALUE, REG_GSI,
            IARG_REG_VALUE, REG_GBP,
            IARG_REG_VALUE, REG_STACK_PTR,
            (num_operands >= 1 ? IARG_MEMORYOP_EA : IARG_UINT32), 0,
            (num_operands >= 2 ? IARG_MEMORYOP_EA : IARG_UINT32), 1,
            (num_operands >= 3 ? IARG_MEMORYOP_EA : IARG_UINT32), 2,
            #endif
            IARG_END
        );
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else if ((long int) ipoint == IPOINT_AFTER) {
    }
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
}

SPPY::PyObject* Python_INS_Category(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_Category(ins_object));
}

SPPY::PyObject* Python_INS_Extension(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_Extension(ins_object));
}

SPPY::PyObject* Python_INS_MemoryOperandSize(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* memoryop;
    PyArg_ParseTuple(args, "k|O", &ins, &memoryop);
    INS ins_object = *(INS*) ins;
    UINT32 memoryop_object = (UINT32) PyInt_AsLong(memoryop);
    return SPPY::Py_BuildValue("k", INS_MemoryOperandSize(ins_object, memoryop_object));
}

SPPY::PyObject* Python_INS_MemoryWriteSize(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_MemoryWriteSize(ins_object));
}

SPPY::PyObject* Python_INS_GetPredicate(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_GetPredicate(ins_object));
}

SPPY::PyObject* Python_INS_MemoryReadSize(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_MemoryReadSize(ins_object));
}

SPPY::PyObject* Python_INS_IsMemoryRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMemoryRead(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsMemoryWrite(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMemoryWrite(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_HasMemoryRead2(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_HasMemoryRead2(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_HasFallThrough(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsLea(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsLea(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsNop(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsNop(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_OPCODE_StringShort(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* opcode;
    PyArg_ParseTuple(args, "O", &opcode);
    UINT32 opcode_object = (UINT32) PyInt_AsLong(opcode);
    return SPPY::Py_BuildValue("s", OPCODE_StringShort(opcode_object).c_str());
}

SPPY::PyObject* Python_INS_Mnemonic(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("s", INS_Mnemonic(ins_object).c_str());
}

SPPY::PyObject* Python_INS_IsBranch(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsBranch(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsDirectBranch(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsDirectBranch(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsDirectCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsDirectCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsDirectBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsDirectBranchOrCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsBranchOrCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_Stutters(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_Stutters(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsProcedureCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsProcedureCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsRet(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsRet(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsSysret(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsSysret(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsPrefetch(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsPrefetch(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsAtomicUpdate(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsAtomicUpdate(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsIndirectBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsIndirectBranchOrCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_RegR(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    SPPY::PyObject* k;
    PyArg_ParseTuple(args, "k|O", &x, &k);
    INS x_object = *(INS*) x;
    UINT32 k_object = (UINT32) PyInt_AsLong(k);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_RegR(x_object, k_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_RegW(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    SPPY::PyObject* k;
    PyArg_ParseTuple(args, "k|O", &x, &k);
    INS x_object = *(INS*) x;
    UINT32 k_object = (UINT32) PyInt_AsLong(k);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_RegW(x_object, k_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_Opcode(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    OPCODE* opcode_return = (OPCODE*) malloc(sizeof(OPCODE));
    *opcode_return = INS_Opcode(ins_object);
    return SPPY::Py_BuildValue("k", opcode_return);
}

SPPY::PyObject* Python_CATEGORY_StringShort(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* num;
    PyArg_ParseTuple(args, "O", &num);
    UINT32 num_object = (UINT32) PyInt_AsLong(num);
    return SPPY::Py_BuildValue("s", CATEGORY_StringShort(num_object).c_str());
}

SPPY::PyObject* Python_EXTENSION_StringShort(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* num;
    PyArg_ParseTuple(args, "O", &num);
    UINT32 num_object = (UINT32) PyInt_AsLong(num);
    return SPPY::Py_BuildValue("s", EXTENSION_StringShort(num_object).c_str());
}

SPPY::PyObject* Python_INS_MaxNumRRegs(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    return SPPY::Py_BuildValue("k", INS_MaxNumRRegs(x_object));
}

SPPY::PyObject* Python_INS_MaxNumWRegs(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    return SPPY::Py_BuildValue("k", INS_MaxNumWRegs(x_object));
}

SPPY::PyObject* Python_INS_RegRContain(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k|k", &ins, &reg);
    INS ins_object = *(INS*) ins;
    REG reg_object = *(REG*) reg;
    if (INS_RegRContain(ins_object, reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_RegWContain(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k|k", &ins, &reg);
    INS ins_object = *(INS*) ins;
    REG reg_object = *(REG*) reg;
    if (INS_RegWContain(ins_object, reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsStackRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsStackRead(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsStackWrite(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsStackWrite(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsIpRelRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsIpRelRead(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsIpRelWrite(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsIpRelWrite(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsPredicated(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsPredicated(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsOriginal(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsOriginal(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_Disassemble(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("s", INS_Disassemble(ins_object).c_str());
}

SPPY::PyObject* Python_INS_MemoryOperandCount(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_MemoryOperandCount(ins_object));
}

SPPY::PyObject* Python_INS_OperandIsAddressGenerator(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsAddressGenerator(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_MemoryOperandIsRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* memopidx;
    PyArg_ParseTuple(args, "k|O", &ins, &memopidx);
    INS ins_object = *(INS*) ins;
    UINT32 memopidx_object = (UINT32) PyInt_AsLong(memopidx);
    if (INS_MemoryOperandIsRead(ins_object, memopidx_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_MemoryOperandIsWritten(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* memopidx;
    PyArg_ParseTuple(args, "k|O", &ins, &memopidx);
    INS ins_object = *(INS*) ins;
    UINT32 memopidx_object = (UINT32) PyInt_AsLong(memopidx);
    if (INS_MemoryOperandIsWritten(ins_object, memopidx_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsSyscall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsSyscall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_SyscallStd(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_SyscallStd(ins_object));
}

SPPY::PyObject* Python_INS_Rtn(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    RTN* rtn_return = (RTN*) malloc(sizeof(RTN));
    *rtn_return = INS_Rtn(x_object);
    return SPPY::Py_BuildValue("k", rtn_return);
}

SPPY::PyObject* Python_INS_Next(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = INS_Next(x_object);
    return SPPY::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_INS_Prev(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = INS_Prev(x_object);
    return SPPY::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_INS_Invalid(SPPY::PyObject* self, SPPY::PyObject* args) {

    INS* ins_return = (INS*) malloc(sizeof(INS));
    *ins_return = INS_Invalid();
    return SPPY::Py_BuildValue("k", ins_return);
}

SPPY::PyObject* Python_INS_Valid(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* x;
    PyArg_ParseTuple(args, "k", &x);
    INS x_object = *(INS*) x;
    if (INS_Valid(x_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_Address(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_Address(ins_object));
}

SPPY::PyObject* Python_INS_Size(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_Size(ins_object));
}

SPPY::PyObject* Python_INS_DirectBranchOrCallTargetAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_DirectBranchOrCallTargetAddress(ins_object));
}

SPPY::PyObject* Python_INS_NextAddress(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_NextAddress(ins_object));
}

SPPY::PyObject* Python_INS_EffectiveAddressWidth(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_EffectiveAddressWidth(ins_object));
}

SPPY::PyObject* Python_INS_IsSysenter(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsSysenter(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsXbegin(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsXbegin(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsXend(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsXend(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsHalt(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsHalt(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsPcMaterialization(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsPcMaterialization(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsFarCall(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsFarCall(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsFarJump(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsFarJump(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsDirectFarJump(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsDirectFarJump(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsVgather(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsVgather(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsVscatter(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsVscatter(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_HasMemoryVector(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_HasMemoryVector(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsInterrupt(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsInterrupt(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsFarRet(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsFarRet(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsSub(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsSub(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsMov(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMov(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsMovFullRegRegSame(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMovFullRegRegSame(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsRDTSC(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsRDTSC(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsMaskMov(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMaskMov(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsMaskedJump(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsMaskedJump(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_RepCountRegister(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_RepCountRegister(ins_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_SegmentRegPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_SegmentRegPrefix(ins_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_SegPrefixIsMemoryRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_SegPrefixIsMemoryRead(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_SegPrefixIsMemoryWrite(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_SegPrefixIsMemoryWrite(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_AddressSizePrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_AddressSizePrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_BranchNotTakenPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_BranchNotTakenPrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_BranchTakenPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_BranchTakenPrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_LockPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_LockPrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandSizePrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_OperandSizePrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_RepPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_RepPrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_RepnePrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_RepnePrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_SegmentPrefix(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_SegmentPrefix(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsXchg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsXchg(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsStringop(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsStringop(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_IsIRet(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_IsIRet(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_FullRegRContain(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k|k", &ins, &reg);
    INS ins_object = *(INS*) ins;
    REG reg_object = *(REG*) reg;
    if (INS_FullRegRContain(ins_object, reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_FullRegWContain(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* reg;
    PyArg_ParseTuple(args, "k|k", &ins, &reg);
    INS ins_object = *(INS*) ins;
    REG reg_object = *(REG*) reg;
    if (INS_FullRegWContain(ins_object, reg_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_HasRealRep(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    if (INS_HasRealRep(ins_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_MemoryDisplacement(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_MemoryDisplacement(ins_object));
}

SPPY::PyObject* Python_INS_MemoryBaseReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_MemoryBaseReg(ins_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_MemoryIndexReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_MemoryIndexReg(ins_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_MemoryScale(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_MemoryScale(ins_object));
}

SPPY::PyObject* Python_INS_ChangeReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
}

SPPY::PyObject* Python_INS_OperandCount(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    PyArg_ParseTuple(args, "k", &ins);
    INS ins_object = *(INS*) ins;
    return SPPY::Py_BuildValue("k", INS_OperandCount(ins_object));
}

SPPY::PyObject* Python_INS_OperandNameId(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    return SPPY::Py_BuildValue("k", INS_OperandNameId(ins_object, n_object));
}

SPPY::PyObject* Python_INS_OperandIsMemory(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsMemory(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandMemoryBaseReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_OperandMemoryBaseReg(ins_object, n_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_OperandMemoryIndexReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_OperandMemoryIndexReg(ins_object, n_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_OperandMemorySegmentReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_OperandMemorySegmentReg(ins_object, n_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_OperandMemoryScale(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    return SPPY::Py_BuildValue("k", INS_OperandMemoryScale(ins_object, n_object));
}

SPPY::PyObject* Python_INS_OperandMemoryDisplacement(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    return SPPY::Py_BuildValue("k", INS_OperandMemoryDisplacement(ins_object, n_object));
}

SPPY::PyObject* Python_INS_OperandIsFixedMemop(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsFixedMemop(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandIsBranchDisplacement(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsBranchDisplacement(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandIsReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsReg(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandReg(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    REG* reg_return = (REG*) malloc(sizeof(REG));
    *reg_return = INS_OperandReg(ins_object, n_object);
    return SPPY::Py_BuildValue("k", reg_return);
}

SPPY::PyObject* Python_INS_OperandIsImmediate(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsImmediate(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandImmediate(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    return SPPY::Py_BuildValue("k", INS_OperandImmediate(ins_object, n_object));
}

SPPY::PyObject* Python_INS_OperandIsImplicit(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandIsImplicit(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandWidth(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    return SPPY::Py_BuildValue("k", INS_OperandWidth(ins_object, n_object));
}

SPPY::PyObject* Python_INS_OperandRead(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandRead(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandWritten(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandWritten(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandReadOnly(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandReadOnly(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandWrittenOnly(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandWrittenOnly(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_OperandReadAndWritten(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* n;
    PyArg_ParseTuple(args, "k|O", &ins, &n);
    INS ins_object = *(INS*) ins;
    UINT32 n_object = (UINT32) PyInt_AsLong(n);
    if (INS_OperandReadAndWritten(ins_object, n_object)) {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_TrueStruct));
    } else {
        return SPPY::Py_BuildValue("O", ((SPPY::PyObject *) &SPPY::_Py_ZeroStruct));
    }
}

SPPY::PyObject* Python_INS_MemoryOperandIndexToOperandIndex(SPPY::PyObject* self, SPPY::PyObject* args) {
    SPPY::PyObject* ins;
    SPPY::PyObject* memopidx;
    PyArg_ParseTuple(args, "k|O", &ins, &memopidx);
    INS ins_object = *(INS*) ins;
    UINT32 memopidx_object = (UINT32) PyInt_AsLong(memopidx);
    return SPPY::Py_BuildValue("k", INS_MemoryOperandIndexToOperandIndex(ins_object, memopidx_object));
}