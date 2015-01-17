import sys, pin
total = 0
info = file("odd.out", "w")


def counter(ins_addr):
	x = pin.INS_Address(ins_addr)
	y = pin.INS_IsMov(ins_addr)
	if y:
		info.write("MOV @ : " + hex(x) + pin.INS_Disassemble(ins_addr) + "\n")	

	y = pin.INS_IsNop(ins_addr)
	if y:
		info.write("NOP @ : " + hex(x) + pin.INS_Disassemble(ins_addr) + "\n")	

	y = pin.INS_IsLea(ins_addr)
	if y:
		info.write("LEA @ : " + hex(x) + pin.INS_Disassemble(ins_addr) + "\n")	


pin.INS_AddInstrumentFunction(counter)
