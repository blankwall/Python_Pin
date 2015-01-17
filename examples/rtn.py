import pin
count = 0
def load(img):
	global count
	if count == 0:
		x = pin.TRACE_Rtn(img)
		sys.stdout.write("\nInteresting fact is I find this information statically :)! but sometimes Im wrong...\n")
		sys.stdout.write("NAME %s\n" % pin.RTN_Name(x))
		sys.stdout.write("SIZE %x\n" % pin.RTN_Size(x))
		sys.stdout.write("ID %x\n" % pin.RTN_Id(x))
		sys.stdout.write("RANGE %x\n" % pin.RTN_Range(x))
		sys.stdout.write("ADDRESS 0x%x\n" % pin.RTN_Address(x))
		pin.RTN_Open(x)
		y = pin.RTN_InsHead(x)
		sys.stdout.write("DISASSEMBLE HEAD INSTRUCTION: %s\n" % pin.INS_Disassemble(y))
		sys.stdout.write("NUMBER OF INSTRUCTIONS %x\n" % pin.RTN_NumIns(x))
		y = pin.RTN_InsTail(x)
		sys.stdout.write("DISASSEMBLE TAIL INSTRUCTION: %s\n\n" % pin.INS_Disassemble(y))
		pin.RTN_Close(x)
		count += 1

pin.TRACE_AddInstrumentFunction(load)

