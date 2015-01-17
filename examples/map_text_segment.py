import sys, pin
total = 0
info = file("map.out", "w")

#map the text segment of an executable
def map(ins_addr):
	x = pin.INS_Address(ins_addr)
	if x < 0x500000:
		info.write("Instruction Address_1: %x  OPCODE %s\n" % (x, pin.INS_Disassemble(ins_addr)))


pin.INS_AddInstrumentFunction(map)
