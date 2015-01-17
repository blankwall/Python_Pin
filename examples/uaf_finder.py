import pin, sys

debug = True
allocations = []
last_allocated_size = 0
log_file = open('uaf.txt', 'w')

def add_allocation(address, size):
    for allocation in allocations:
        if allocation['address'] == address:
            allocation['size'] = size
            allocation['in_use'] = True
            return

    allocations.append({"address":address, "size":size, "in_use": True})

def mark_free(address):
    global allocations
    for allocation in allocations:
        if allocation['address'] == address:
            allocation['in_use'] = False

def a_heap_thing(address):
    global allocations
    for allocation in allocations:
        if address in range(allocation['address'], allocation['address']+allocation['size']):
            return allocation

    return None

def in_use(address):
    global allocations
    for allocation in allocations:
        if allocation['address'] == address and allocation['in_use']:
            return True
    return False

def malloc_before(everything):
    global last_allocated_size
    last_allocated_size = everything['arg_0']
    #print everything['arg_0'], hex(everything['ref_arg_0'])
    #pin.set_pointer(everything['ref_arg_0'], 1)

def malloc_after(everything):
    global last_allocated_size
    address = everything['return']
    #print pin.get_pointer(everything['reg_gax']), everything['return']
    #print "gax:%x;gbx:%x;gcx:%x;gdx:%x"%(everything['reg_gax'], everything['reg_gbx'], everything['reg_gcx'], everything['reg_gdx'])
    if last_allocated_size == 0:
        return
    add_allocation(address, last_allocated_size)

def free(everything):
    mark_free(everything['arg_0'])

def handle_reads(ins_info):
    global log_file
    heap_read_addr = ins_info['MEM_OP0']
    h = a_heap_thing(heap_read_addr)
    if h and not h['in_use']:
        # print " 0x%x %s" % (ins_info['IP'], ins_info['mnemonic'])
        if (ins_info['IP'] > 0):
            print "Reading a freed object!"
            print "UAF located at 0x%x [0x%x %s]" % (heap_read_addr, ins_info['IP'], ins_info['mnemonic'])
    return

def ins_test(ins):
    if pin.INS_IsMov(ins) and (pin.INS_IsMemoryRead(ins) or pin.INS_IsMemoryWrite(ins)):
        pin.INS_InsertCall(pin.IPOINT_BEFORE, ins, handle_reads)

def memset_pre(everything):
    pin.set_pointer(everything['reg_gsi'], 0x43)

def image_load(img):
    rtn = pin.RTN_FindByName(img, "memset")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        pin.RTN_InsertCall(pin.IPOINT_BEFORE, "memset", rtn, 3, memset_pre)
        pin.RTN_Close(rtn)

    rtn = pin.RTN_FindByName(img, "malloc")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        #pin.RTN_InsertCall(pin.IPOINT_BEFORE, "malloc", rtn, 1, malloc_before)
        #pin.RTN_InsertCall(pin.IPOINT_AFTER, "malloc", rtn, 1, malloc_after)
        pin.RTN_Close(rtn)

    rtn = pin.RTN_FindByName(img, "free")
    if pin.RTN_Valid(rtn):
        pin.RTN_Open(rtn)
        #pin.RTN_InsertCall(pin.IPOINT_BEFORE, "malloc", rtn, 1, free)
        pin.RTN_Close(rtn)

def exiting():
    global allocations
    # print allocations

pin.IMG_AddInstrumentFunction(image_load)
pin.INS_AddInstrumentFunction(ins_test)
pin.AddFiniFunction(exiting)

