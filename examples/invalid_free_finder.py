import pin, sys

allocated_buffers = []

def malloc_before(a=None, b=None, c=None, d=None):
    sys.stdout.write("%s(%s) = "%(a, (hex(b))))

def malloc_after(a=None, b=None):
    print "0x%x" % (b)
    allocated_buffers.append(b)

def free(a, b):
    if b == 0:
        print "free(NULL) detected"
        return

    if b in allocated_buffers:
        "Freeing %s"%(hex(b))
        allocated_buffers.remove(b)
    else:
        print "freeing something that wasn't malloc'd (%d)" % (b)

def image_load(img):
    rtn = pin.RTN_FindByName(img, "malloc")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "malloc", rtn, 1, malloc_before)
        pin.RTN_InsertCall(pin.IPOINT_AFTER, "malloc", rtn, 1, malloc_after)
        pin.RTN_Close(rtn)

    rtn = pin.RTN_FindByName(img, "free")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "malloc", rtn, 1, free)
        pin.RTN_Close(rtn)

pin.IMG_AddInstrumentFunction(image_load)
