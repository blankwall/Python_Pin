#ifndef B_H
#define B_H

SPPY::PyObject* module;
SPPY::PyObject** hooks_syscall_entry = NULL;
SPPY::PyObject** hooks_syscall_exit = NULL;
SPPY::PyObject** hooks_instrument_function = NULL;
SPPY::PyObject** hooks_img_load = NULL;
SPPY::PyObject** hooks_img_unload = NULL;
SPPY::PyObject** hooks_trace_instrument = NULL;
SPPY::PyObject** hooks_instruction = NULL;
SPPY::PyObject** fini_functions = NULL;

void initialize_pin_module();

void add_hook(SPPY::PyObject*** hooks, SPPY::PyObject* new_hook);

void SyscallEntry(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID *v);
void SyscallExit(THREADID threadIndex, CONTEXT *ctxt, SYSCALL_STANDARD std, VOID* v);
SPPY::PyObject* Python_PIN_AddSyscallExitFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_PIN_AddSyscallEntryFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_TRACE_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args);
void Fini(INT32, VOID*);
SPPY::PyObject* Python_AddFiniFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args);

void InstrumentFunction(RTN rtn, VOID *v);
SPPY::PyObject* Python_RTN_AddInstrumentFunction(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* get_pointer(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* set_pointer(SPPY::PyObject* self, SPPY::PyObject* args);

typedef struct rtn_hook {
    SPPY::PyObject* function;
    int arguments;
} rtn_hook;

void ImageLoad(IMG img, VOID *v);
void ImageUnload(IMG img, VOID *v);
void Trace(TRACE trace, VOID *v);
void Ins_Hook(INS ins, VOID *v);

///static (_Py_NoneStruct) methods2[];

static SPPY::PyMethodDef methods[] = {
//static (SPPY::_Py_NoneStruct) methods[] = {
    {"AddFiniFunction",
        Python_AddFiniFunction,
        METH_VARARGS,
      "Register a notification function that is called immediately before execution of a system call."},
    {"AddSyscallEntryFunction",
        Python_PIN_AddSyscallEntryFunction,
        METH_VARARGS,
      "Register a notification function that is called immediately before execution of a system call."},
    {"AddSyscallExitFunction",
        Python_PIN_AddSyscallExitFunction,
        METH_VARARGS,
      "Register a notification function that is called immediately after execution of a system call."},
    {"GetSyscallNumber",
        Python_PIN_GetSyscallNumber,
        METH_VARARGS,
      "Get the number (ID) of the system call to be executed in the specified context."},
    {"GetSyscallArgument",
        Python_PIN_GetSyscallArgument,
        METH_VARARGS,
      "Get the value of the argument of the system call to be executed in the specified context."},
    {"GetSyscallReturn",
        Python_PIN_GetSyscallReturn,
        METH_VARARGS,
      "Get the return value of the system call which has just returned with the specified context."},
    {"SetSyscallArgument",
        Python_PIN_SetSyscallArgument,
        METH_VARARGS,
      "Set the given value for the argument of the system call to be executed in the specified context."},
    {"SetSyscallNumber",
        Python_PIN_SetSyscallNumber,
        METH_VARARGS,
      "Set the number (ID) of the system call to be executed in the specified context."},
    {"RTN_AddInstrumentFunction",
        Python_RTN_AddInstrumentFunction,
        METH_VARARGS,
      "Set the number (ID) of the system call to be executed in the specified context."},
    {"RTN_Name",
        Python_RTN_Name, 
        METH_VARARGS,
      "Name of routine"},
    {"RTN_Address",
        Python_RTN_Address, 
        METH_VARARGS,
      "Address in memory of rtn"},
    {"RTN_InsertCall",
        Python_RTN_InsertCall,
        METH_VARARGS,
      "Insert call relative to a rtn."},
    {"RTN_Valid",
          Python_RTN_Valid , 
          METH_VARARGS,
       "True if x is not RTN_Invalid(). RTN_Valid() returns FALSE in certain cases when there is no static image of the code available, including dynamically generated code."},
   {"RTN_Id",
          Python_RTN_Id , 
          METH_VARARGS,
       "Pin assigns each routine a unique ID. The ID is globally unique, i.e. an ID will not appear in two images. If the same routine name exists in two different images (i.e. they are in different addresses), each will have a different ID. If an image is unloaded and then reloaded, the routines within it will most likely have different IDs than before."},
    {"RTN_Range",
          Python_RTN_Range , 
          METH_VARARGS,
       "range of routine in bytes (until the next known symbol or end of current code region)."},
    {"RTN_Size",
          Python_RTN_Size, 
          METH_VARARGS,
       "size of routine in bytes"},
    {"RTN_IsDynamic",
          Python_RTN_IsDynamic , 
          METH_VARARGS,
       "TRUE if the routine is dynamically created"},
    {"RTN_IsSafeForProbedInsertion",
          Python_RTN_IsSafeForProbedInsertion , 
          METH_VARARGS,
       "Return TRUE if the given RTN is a candidate for function insertion using probes, and FALSE otherwise. This API should be called before attempting to insert a call to an analysis function using RTN_InsertCallProbed(). If you want to replace the given RTN with RTN_ReplaceSignatureProbed() or RTN_ReplaceProbed() you should use RTN_IsSafeForProbedReplacement()"},
    {"RTN_IsSafeForProbedReplacement",
          Python_RTN_IsSafeForProbedReplacement , 
          METH_VARARGS,
       "Return TRUE if the given RTN is a candidate for probed function replacement, and FALSE otherwise. This API should be called before attempting to replace a function using RTN_ReplaceSignatureProbed() or RTN_ReplaceProbed(). Note that this routine does not guarantee it is safe to place a probe, it merely indicates that certain conditions are not present."},
    {"RTN_FindNameByAddress",
        Python_RTN_FindNameByAddress , 
        METH_VARARGS,
     "Return the name of a function. If more than one name is associated with this address, the first name found is returned."},
    {"RTN_FindByName",
        Python_RTN_FindByName,
        METH_VARARGS,
     "Handle to the RTN found. If not found returns RTN_Invalid()"},
     {"RTN_Open",
        Python_RTN_Open , 
        METH_VARARGS,
     "Open the given rtn. This must be called before RTN_InsHead() or RTN_InsertCall() or RTN_InsHeadOnly()"},
     {"RTN_Close",
        Python_RTN_Close, 
        METH_VARARGS,
     "Close the given rtn. This must be called before opening a new rtn."},
     {"RTN_InsHead",
        Python_RTN_InsHead , 
        METH_VARARGS,
     "You must call RTN_Open() before the first time this is called for an rtn"},
     {"RTN_InsTail",
        Python_RTN_InsTail , 
        METH_VARARGS,
     "You must call RTN_Open() before the first time this is called for an rtn"},
     {"RTN_NumIns",
        Python_RTN_NumIns , 
        METH_VARARGS,
     "Compute number of static INSs inside RTN."},
    {"IMG_Next",
        Python_IMG_Next,
        METH_VARARGS,
      "Of the list of currently loaded images in memory it returns the image loaded after image x, or IMG_Invalid() if x is the last image"},
    {"IMG_Prev",
        Python_IMG_Prev,
        METH_VARARGS,
      "Of the list of currently loaded images in memory it returns the image loaded prior to image x, or IMG_Invalid() if x is the first image"},
    {"IMG_Invalid",
        Python_IMG_Invalid,
        METH_VARARGS,
      "Used to indicate no image"},
    {"IMG_Valid",
        Python_IMG_Valid,
        METH_VARARGS,
      "True if x is not IMG_Invalid()"},
    {"IMG_SecHead",
        Python_IMG_SecHead,
        METH_VARARGS,
      "First section in image"},
    {"IMG_SecTail",
        Python_IMG_SecTail,
        METH_VARARGS,
      "Last section in image"},
    {"IMG_RegsymHead",
        Python_IMG_RegsymHead,
        METH_VARARGS,
      "First regular symbol in image"},
    {"IMG_Entry",
        Python_IMG_Entry,
        METH_VARARGS,
      "Address of first instruction executed when image is loaded"},
    {"IMG_Name",
        Python_IMG_Name,
        METH_VARARGS,
      "Name of image, Image names are encoded in UTF8 (a superset of ASCII), this is supported for Linux (only for locales encoded in UTF8) and Windows"},
    {"IMG_Gp",
        Python_IMG_Gp,
        METH_VARARGS,
      "Global pointer (GP) of image, if a GP is used to address global data"},
    {"IMG_LoadOffset",
        Python_IMG_LoadOffset,
        METH_VARARGS,
      "Offset from the image's link-time address to its load-time address."},
    {"IMG_LowAddress",
        Python_IMG_LowAddress,
        METH_VARARGS,
      "The lowest virtual address of the image in the memory"},
    {"IMG_HighAddress",
        Python_IMG_HighAddress,
        METH_VARARGS,
      "The highest virtual address of the image in the memory"},
    {"IMG_StartAddress",
        Python_IMG_StartAddress,
        METH_VARARGS,
      "The starting virtual address that the image is mapped to"},
    {"IMG_SizeMapped",
        Python_IMG_SizeMapped,
        METH_VARARGS,
      "The size of the image mapped"},
    {"IMG_Type",
        Python_IMG_Type,
        METH_VARARGS,
      "Image type"},
    {"IMG_IsMainExecutable",
        Python_IMG_IsMainExecutable,
        METH_VARARGS,
      "TRUE if this is the main executable of an application"},
    {"IMG_IsStaticExecutable",
        Python_IMG_IsMainExecutable,
        METH_VARARGS,
      "TRUE if this is the static executable"},
    {"IMG_Id",
        Python_IMG_Id,
        METH_VARARGS,
      "Returns a unique ID for the image. If an image is unloaded, the ID is not reused for a different image. If an image is unloaded and the same one is loaded back, the ID is different."},
    {"IMG_FindImgById",
        Python_IMG_FindImgById,
        METH_VARARGS,
      "Find image by Id"},
    {"IMG_FindByAddress",
        Python_IMG_FindByAddress,
        METH_VARARGS,
      "Find image by address"},
    {"IMG_AddInstrumentFunction",
        Python_IMG_AddInstrumentFunction,
        METH_VARARGS,
      "Use this to register a call back to catch the loading of an image"},
    {"IMG_AddUnloadFunction",
        Python_IMG_AddUnloadFunction,
        METH_VARARGS,
      "Register fun as a call back to be used when an image is unloaded. This is not an instrumentation function--it doesn't make sense to instrument a function when it removed from memory."},
    {"IMG_Open",
        Python_IMG_Open,
        METH_VARARGS,
      "Allows one to open and image and browse it statically. There can only be one image opened at a time. File names are encoded in UTF8 (a superset of ASCII), this is supported for Linux (only for locales encoded in UTF8) and Windows Returns IMG_INVALID() if the image can not be opened"},
    {"IMG_Close",
        Python_IMG_Close,
        METH_VARARGS,
      "Close the image that was opened"},
    {"APP_ImgHead",
        Python_APP_ImgHead,
        METH_VARARGS,
      "The first image loaded into memory"},
    {"APP_ImgTail",
        Python_APP_ImgTail,
        METH_VARARGS,
      "The last image loaded into memory"},

    /* TRACE */
    {"TRACE_Address",
        Python_TRACE_Address,
        METH_VARARGS,
      "Returns Address of trace"
    },
    {"TRACE_Original",
        Python_TRACE_Original,
        METH_VARARGS,
      "Whether the TRACE data structure has been instrumented or optimized since it was created"
    },
    {"TRACE_BblHead",
        Python_TRACE_BblHead,
        METH_VARARGS,
      "Returns reference to first basic block in trace"
    },
    {"TRACE_AddInstrumentFunction",
        Python_TRACE_AddInstrumentFunction,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_InsertIfCall",
        Python_TRACE_InsertIfCall,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_InsertThenCall",
        Python_TRACE_InsertThenCall,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_BblTail",
        Python_TRACE_BblTail,
        METH_VARARGS,
      "last bbl of trace"
    },
    {"TRACE_Size",
        Python_TRACE_Size,
        METH_VARARGS,
      "returns the original source footprint of the given trace"
    },
    {"TRACE_Rtn",
        Python_TRACE_Rtn,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_HasFallThrough",
        Python_TRACE_HasFallThrough,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_NumBbl",
        Python_TRACE_NumBbl,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_NumIns",
        Python_TRACE_NumIns,
        METH_VARARGS,
      "Add trace to program"
    },
    {"TRACE_StubSize",
        Python_TRACE_StubSize,
        METH_VARARGS,
      "Add trace to program"
    },
     {"TRACE_InsertCall",
        Python_TRACE_InsertCall,
        METH_VARARGS,
      "Add trace to program"
    },

    /* BBL */
    {"BBL_MoveAllAttributes",
        Python_BBL_MoveAllAttributes,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_NumIns",
        Python_BBL_NumIns,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_InsHead",
        Python_BBL_InsHead,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_InsTail",
        Python_BBL_InsTail,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_Next",
        Python_BBL_Next,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_Prev",
        Python_BBL_Prev,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_Original",
        Python_BBL_Original,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_Address",
        Python_BBL_Address,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_Size",
        Python_BBL_Size,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_InsertCall",
        Python_BBL_InsertCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_InsertIfCall",
        Python_BBL_InsertIfCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_InsertThenCall",
        Python_BBL_InsertThenCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"BBL_HasFallThrough",
        Python_BBL_HasFallThrough,
        METH_VARARGS,
      "checking if an instruction could have a fall-through path based on the opcode"
    },
    {"BBL_Valid",
     Python_BBL_Valid,
     METH_VARARGS,
   "True if bbl is not BBL_INVALID()"
    },
        /*AUTO GENERATED SKELETONS*/
     {"INS_AddInstrumentFunction",
        Python_INS_AddInstrumentFunction,
        METH_VARARGS,
      "Add trace to program"
    },
    {"INS_InsertCall",
        Python_INS_InsertCall,
        METH_VARARGS,
      "Insert a call to funptr relative to instruction ins."
    },
    {"INS_Category",
        Python_INS_Category,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Extension",
        Python_INS_Extension,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryOperandSize",
        Python_INS_MemoryOperandSize,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryWriteSize",
        Python_INS_MemoryWriteSize,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_GetPredicate",
        Python_INS_GetPredicate,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryReadSize",
        Python_INS_MemoryReadSize,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMemoryRead",
        Python_INS_IsMemoryRead,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMemoryWrite",
        Python_INS_IsMemoryWrite,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_HasMemoryRead2",
        Python_INS_HasMemoryRead2,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_HasFallThrough",
        Python_INS_HasFallThrough,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsLea",
        Python_INS_IsLea,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsNop",
        Python_INS_IsNop,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"OPCODE_StringShort",
        Python_OPCODE_StringShort,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Mnemonic",
        Python_INS_Mnemonic,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsBranch",
        Python_INS_IsBranch,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsDirectBranch",
        Python_INS_IsDirectBranch,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsDirectCall",
        Python_INS_IsDirectCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsDirectBranchOrCall",
        Python_INS_IsDirectBranchOrCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsBranchOrCall",
        Python_INS_IsBranchOrCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Stutters",
        Python_INS_Stutters,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsCall",
        Python_INS_IsCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsProcedureCall",
        Python_INS_IsProcedureCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsRet",
        Python_INS_IsRet,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsSysret",
        Python_INS_IsSysret,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsPrefetch",
        Python_INS_IsPrefetch,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsAtomicUpdate",
        Python_INS_IsAtomicUpdate,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsIndirectBranchOrCall",
        Python_INS_IsIndirectBranchOrCall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RegR",
        Python_INS_RegR,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RegW",
        Python_INS_RegW,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Opcode",
        Python_INS_Opcode,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MaxNumRRegs",
        Python_INS_MaxNumRRegs,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MaxNumWRegs",
        Python_INS_MaxNumWRegs,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RegRContain",
        Python_INS_RegRContain,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RegWContain",
        Python_INS_RegWContain,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsStackRead",
        Python_INS_IsStackRead,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsStackWrite",
        Python_INS_IsStackWrite,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsIpRelRead",
        Python_INS_IsIpRelRead,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsIpRelWrite",
        Python_INS_IsIpRelWrite,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsPredicated",
        Python_INS_IsPredicated,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsOriginal",
        Python_INS_IsOriginal,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Disassemble",
        Python_INS_Disassemble,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryOperandCount",
        Python_INS_MemoryOperandCount,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsAddressGenerator",
        Python_INS_OperandIsAddressGenerator,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryOperandIsRead",
        Python_INS_MemoryOperandIsRead,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryOperandIsWritten",
        Python_INS_MemoryOperandIsWritten,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsSyscall",
        Python_INS_IsSyscall,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_SyscallStd",
        Python_INS_SyscallStd,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Rtn",
        Python_INS_Rtn,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Next",
        Python_INS_Next,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Prev",
        Python_INS_Prev,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Valid",
        Python_INS_Valid,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Address",
        Python_INS_Address,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_Size",
        Python_INS_Size,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_DirectBranchOrCallTargetAddress",
        Python_INS_DirectBranchOrCallTargetAddress,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_NextAddress",
        Python_INS_NextAddress,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    /*AUTO GENERATED SKELETONS*/
    {"INS_EffectiveAddressWidth",
        Python_INS_EffectiveAddressWidth ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsSysenter",
        Python_INS_IsSysenter ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsXbegin",
        Python_INS_IsXbegin ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsXend",
        Python_INS_IsXend ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsHalt",
        Python_INS_IsHalt ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsPcMaterialization",
        Python_INS_IsPcMaterialization ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsFarCall",
        Python_INS_IsFarCall ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsFarJump",
        Python_INS_IsFarJump ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsDirectFarJump",
        Python_INS_IsDirectFarJump ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsVgather",
        Python_INS_IsVgather ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsVscatter",
        Python_INS_IsVscatter ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_HasMemoryVector",
        Python_INS_HasMemoryVector ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsInterrupt",
        Python_INS_IsInterrupt ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsFarRet",
        Python_INS_IsFarRet ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsSub",
        Python_INS_IsSub ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMov",
        Python_INS_IsMov ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMovFullRegRegSame",
        Python_INS_IsMovFullRegRegSame ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsRDTSC",
        Python_INS_IsRDTSC ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMaskMov",
        Python_INS_IsMaskMov ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsMaskedJump",
        Python_INS_IsMaskedJump ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RepCountRegister",
        Python_INS_RepCountRegister ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_SegmentRegPrefix",
        Python_INS_SegmentRegPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_SegPrefixIsMemoryRead",
        Python_INS_SegPrefixIsMemoryRead ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_SegPrefixIsMemoryWrite",
        Python_INS_SegPrefixIsMemoryWrite ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_AddressSizePrefix",
        Python_INS_AddressSizePrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_BranchNotTakenPrefix",
        Python_INS_BranchNotTakenPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_BranchTakenPrefix",
        Python_INS_BranchTakenPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_LockPrefix",
        Python_INS_LockPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandSizePrefix",
        Python_INS_OperandSizePrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RepPrefix",
        Python_INS_RepPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_RepnePrefix",
        Python_INS_RepnePrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_SegmentPrefix",
        Python_INS_SegmentPrefix ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsXchg",
        Python_INS_IsXchg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsStringop",
        Python_INS_IsStringop ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_IsIRet",
        Python_INS_IsIRet ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_HasRealRep",
        Python_INS_HasRealRep ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryDisplacement",
        Python_INS_MemoryDisplacement ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryBaseReg",
        Python_INS_MemoryBaseReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryIndexReg",
        Python_INS_MemoryIndexReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryScale",
        Python_INS_MemoryScale ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandCount",
        Python_INS_OperandCount ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandNameId",
        Python_INS_OperandNameId ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsMemory",
        Python_INS_OperandIsMemory ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandMemoryBaseReg",
        Python_INS_OperandMemoryBaseReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandMemoryIndexReg",
        Python_INS_OperandMemoryIndexReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandMemorySegmentReg",
        Python_INS_OperandMemorySegmentReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandMemoryScale",
        Python_INS_OperandMemoryScale ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandMemoryDisplacement",
        Python_INS_OperandMemoryDisplacement ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsFixedMemop",
        Python_INS_OperandIsFixedMemop ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsBranchDisplacement",
        Python_INS_OperandIsBranchDisplacement ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsReg",
        Python_INS_OperandIsReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandReg",
        Python_INS_OperandReg ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsImmediate",
        Python_INS_OperandIsImmediate ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandImmediate",
        Python_INS_OperandImmediate ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandIsImplicit",
        Python_INS_OperandIsImplicit ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandWidth",
        Python_INS_OperandWidth ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandRead",
        Python_INS_OperandRead ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandWritten",
        Python_INS_OperandWritten ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandReadOnly",
        Python_INS_OperandReadOnly ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandWrittenOnly",
        Python_INS_OperandWrittenOnly ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_OperandReadAndWritten",
        Python_INS_OperandReadAndWritten ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"INS_MemoryOperandIndexToOperandIndex",
        Python_INS_MemoryOperandIndexToOperandIndex ,
        METH_VARARGS,
      "Move all attributes from one BBL to another"
    },
    {"set_pointer",
        set_pointer,
        METH_VARARGS,
        "Write a value to a raw pointer"
    },
    {"get_pointer",
        get_pointer,
        METH_VARARGS,
        "Read a value to a raw pointer"
    },
    {NULL, NULL, 0, NULL}
};
#endif

