import pin, sys

def print_chain(ins_object):
    if pin.INS_IsDirectCall(ins_object):
        name = pin.RTN_FindNameByAddress(int(pin.INS_DirectBranchOrCallTargetAddress(ins_object)))
        callee_name = pin.RTN_FindNameByAddress(int(pin.INS_Address(ins_object)))
        if name and name[0] != "." and callee_name and callee_name[0] != "." and name[0] != "_" and callee_name[0] != "_":
            print "call", callee_name, "->", name
    return

    if pin.INS_IsMov(ins_object):
        if pin.INS_IsMemoryWrite(ins_object):
            print pin.INS_Disassemble(ins_object)
            print pin.INS_MemoryWriteSize(ins_object)
    if pin.INS_IsNop(ins_object):
        print pin.INS_Disassemble(ins_object)
        return
    if pin.INS_IsRet(ins_object):
        print pin.INS_Disassemble(ins_object)
        return
        if pin.INS_IsMemoryWrite(ins_object):
            print pin.INS_Disassemble(ins_object)
            print pin.INS_MemoryWriteSize(ins_object)
    return

pin.INS_AddInstrumentFunction(print_chain)
