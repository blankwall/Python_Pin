#ifndef G_H
#define G_H


SPPY::PyObject* Python_INS_Category(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Extension(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryOperandSize(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryWriteSize(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_GetPredicate(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryReadSize(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMemoryRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMemoryWrite(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_HasMemoryRead2(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_HasFallThrough(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsLea(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsNop(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_OPCODE_StringShort(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Mnemonic(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_InsertCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsBranch(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsDirectBranch(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsDirectCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsDirectBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Stutters(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsProcedureCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsRet(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsSysret(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsPrefetch(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsAtomicUpdate(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsIndirectBranchOrCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RegR(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RegW(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Opcode(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_CATEGORY_StringShort(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_EXTENSION_StringShort(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MaxNumRRegs(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MaxNumWRegs(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RegRContain(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RegWContain(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsStackRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsStackWrite(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsIpRelRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsIpRelWrite(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsPredicated(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsOriginal(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Disassemble(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryOperandCount(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsAddressGenerator(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryOperandIsRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryOperandIsWritten(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsSyscall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_SyscallStd(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Rtn(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Next(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Prev(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Invalid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Valid(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Address(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_Size(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_DirectBranchOrCallTargetAddress(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_NextAddress(SPPY::PyObject* self, SPPY::PyObject* args);

/*AUTO GENERATED SKELETONS INSPECTION API*/
SPPY::PyObject* Python_INS_EffectiveAddressWidth(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsSysenter(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsXbegin(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsXend(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsHalt(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsPcMaterialization(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsFarCall(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsFarJump(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsDirectFarJump(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsVgather(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsVscatter(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_HasMemoryVector(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsInterrupt(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsFarRet(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsSub(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMov(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMovFullRegRegSame(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsRDTSC(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMaskMov(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsMaskedJump(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RepCountRegister(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_SegmentRegPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_SegPrefixIsMemoryRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_SegPrefixIsMemoryWrite(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_AddressSizePrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_BranchNotTakenPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_BranchTakenPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_LockPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandSizePrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RepPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_RepnePrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_SegmentPrefix(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsXchg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsStringop(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_IsIRet(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_HasRealRep(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryDisplacement(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryBaseReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryIndexReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryScale(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandCount(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandNameId(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsMemory(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandMemoryBaseReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandMemoryIndexReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandMemorySegmentReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandMemoryScale(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandMemoryDisplacement(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsFixedMemop(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsBranchDisplacement(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandReg(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsImmediate(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandImmediate(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandIsImplicit(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandWidth(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandRead(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandWritten(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandReadOnly(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandWrittenOnly(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_OperandReadAndWritten(SPPY::PyObject* self, SPPY::PyObject* args);
SPPY::PyObject* Python_INS_MemoryOperandIndexToOperandIndex(SPPY::PyObject* self, SPPY::PyObject* args);


#endif
