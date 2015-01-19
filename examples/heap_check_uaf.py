import pin, sys

debug = True
free_list = []
last_allocated_size = 0
hit = 1
real = 0
guard_size = 40
new_size = 0
log_file = open('uaf.txt', 'w')
low = -1
high = -1
canary  = 0x0f0f0f0f0f0f0f0f
canary2 = 0xf0f0f0f0f0f0f0f0
k = 0

def malloc_before(everything):
    global last_allocated_size
    last_allocated_size = everything['arg_0']
   # print "MALLOCING: " + hex(everything['arg_0'])
    new_size = guard_size*2+last_allocated_size
    pin.set_pointer(everything['reg_gdi'], pin.get_pointer(everything['reg_gdi'])+guard_size*2)

def malloc_after(everything):
    global last_allocated_size
    address = everything['return']
    #print "MALLOC " + hex((pin.get_pointer(everything['reg_gax'])))

    pin.set_pointer((pin.get_pointer(everything['reg_gax'])), last_allocated_size)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8, canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8+8, canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+16+8, canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+24+8, canary)
    pin.set_pointer((pin.get_pointer(everything['reg_gax'])+last_allocated_size+32+8), canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8+last_allocated_size+32+8, canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+16+last_allocated_size+32+8, canary)
    pin.set_pointer(pin.get_pointer(everything['reg_gax'])+24+last_allocated_size+32+8, canary)

    pin.set_pointer(everything['reg_gax'], pin.get_pointer(everything['reg_gax'])+guard_size)
    
def free(everything):
    global low,high
    #print "FREE " + hex(everything['arg_0'])
    addr = everything['arg_0']
    if addr == 0:
        return

    size = pin.get_pointer(pin.get_pointer(everything['reg_gdi'])-guard_size)
    free_list.append((addr,size+guard_size))

    if low == -1:
        low = addr
    high = addr+size+guard_size
    pin.set_pointer(everything['reg_gdi'], 0)

def realloc_before(everything):
    global last_allocated_size
    global hit, real
    if hit == 1:
        hit = 0
    else:
        name = pin.get_pointer(everything["reg_gdi"])
        size = pin.get_pointer(everything["reg_gsi"])
        if((size) == 0):
            pin.set_pointer(everything['reg_gdi'], 0)
            pin.set_pointer(everything['reg_gsi'], 0)
        elif(int(name) == 0):
            return
        else:
            last_allocated_size = everything['arg_1']
            pin.set_pointer(everything['reg_gsi'], pin.get_pointer(everything['reg_gsi'])+guard_size*2)
            pin.set_pointer(everything['reg_gdi'], pin.get_pointer(everything['reg_gdi'])-(guard_size))
            real = 1
        hit = 1

def realloc_after(everything):
    global real
    if real == 1:
        pin.set_pointer((pin.get_pointer(everything['reg_gax'])), last_allocated_size)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8, canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8+8, canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+16+8, canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+24+8, canary)
        pin.set_pointer((pin.get_pointer(everything['reg_gax'])+last_allocated_size+32+8), canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+8+last_allocated_size+32+8, canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+16+last_allocated_size+32+8, canary)
        pin.set_pointer(pin.get_pointer(everything['reg_gax'])+24+last_allocated_size+32+8, canary)

        pin.set_pointer(everything['reg_gax'], pin.get_pointer(everything['reg_gax'])+40)
    real = 0

def handle_write(ins_info):
    global low,high
    heap_read_addr = ins_info['MEM_OP0']
    x = ins_info['VAL']
    if x == canary or x == canary2:
        print "HEAP OVERFLOW located at 0x%x [%s]" % (heap_read_addr, ins_info['mnemonic'])

    if heap_read_addr >= low and heap_read_addr <= high and high != -1 and low != -1:
        for i in free_list:
            if heap_read_addr in range(i[0], i[0]+i[1]):  
                print "UAF located at 0x%x [0x%x %s]" % (heap_read_addr, ins_info['IP'], ins_info['mnemonic'])

def ins_test(ins):
    if pin.INS_IsMemoryWrite(ins):
        pin.INS_InsertCall(pin.IPOINT_BEFORE, ins, handle_write)

def image_load(img):
    rtn = pin.RTN_FindByName(img, "realloc")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "realloc", rtn, 3, realloc_before)
        pin.RTN_InsertCall(pin.IPOINT_AFTER, "realloc", rtn, 3, realloc_after)
        pin.RTN_Close(rtn)

    rtn = pin.RTN_FindByName(img, "malloc")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "malloc", rtn, 1, malloc_before)
        pin.RTN_InsertCall(pin.IPOINT_AFTER, "malloc", rtn, 1, malloc_after)
        pin.RTN_Close(rtn)

    rtn = pin.RTN_FindByName(img, "free")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "free", rtn, 1, free)
        pin.RTN_Close(rtn)

def exiting():
    global allocations

pin.IMG_AddInstrumentFunction(image_load)
pin.INS_AddInstrumentFunction(ins_test)
pin.AddFiniFunction(exiting)
