import pin

def load(img):
    if pin.IMG_IsMainExecutable(img):
        print "Main executable loaded %s at %s" % (pin.IMG_Name(img), hex(pin.IMG_StartAddress(img)))
    else:
        print "Loaded %s at %s" % (pin.IMG_Name(img), hex(pin.IMG_StartAddress(img)))

    img_type = pin.IMG_Type(img)
    if img_type == pin.IMG_TYPE_STATIC:
        print "IMG_TYPE_STATIC"
    elif img_type == pin.IMG_TYPE_SHARED:
        print "IMG_TYPE_SHARED"
    elif img_type == pin.IMG_TYPE_SHAREDLIB:
        print "IMG_TYPE_SHAREDLIB"
    elif img_type == pin.IMG_TYPE_RELOCATABLE:
        print "IMG_TYPE_RELOCATABLE"
    else:
        print "unknown type"

def unload(img):
    print "Unloaded %s" % (pin.IMG_Name(img))

pin.IMG_AddInstrumentFunction(load)
pin.IMG_AddUnloadFunction(unload)
