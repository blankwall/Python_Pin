import sys, pin
total = 0
info = file("inscount.out", "w")

def counter(trace_addr):
    global total
    x = pin.TRACE_BblHead(trace_addr)
    y = pin.BBL_Address(x)
    instrucs = pin.BBL_NumIns(x)
    total += instrucs
    info.write("Basic Block @ %x SIZE: %x NUM INS= IN BLOCK: %x  TOTAL: %x\n" % (y, pin.BBL_Size(x), instrucs, total ))

pin.TRACE_AddInstrumentFunction(counter)
