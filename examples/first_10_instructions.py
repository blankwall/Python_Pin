import pin, sys

def image_load(image):
    rtn = RTN_FindByName('printf')
    if pin.RTN_Valid(rtn):
        print "Found %s in %s" % (routine, pin.IMG_Name(img))
        pin.RTN_Open(rtn)
        print "0x%x"%pin.RTN_Address(rtn)
        first_instr = pin.RTN_InsHead(rtn)
        print pin.INS_Disassemble(first_instr)
        next_instr = pin.INS_Next(first_instr)
        for i in range(10):
            disp = pin.INS_Disassemble(next_instr)
            print pin.INS_Disassemble(next_instr)
            if "ret" in disp:
                break
            next_instr = pin.INS_Next(next_instr)
        pin.RTN_Close(rtn)
        print "\n"*5
 
pin.IMG_AddInstrumentFunction(image_load)
