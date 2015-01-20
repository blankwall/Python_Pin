import sys, pin
total = 0
info = file("inscount.out", "w")
unistd = None
if sys.maxsize > 2**32:
	unistd = open("/usr/include/x86_64-linux-gnu/asm/unistd_64.h").read().split("\n")
else:
	unistd = open("/usr/include/i386-linux-gnu/asm/unistd_32.h").read().split("\n")
	
syscalls = []
for line in unistd:
    if "define __NR" in line:
        parts = line.split(" ")
        syscalls.append(parts[1].replace("__NR_",""))

def trace_syscall_exit(ctxt, std):
    return_value = hex(pin.GetSyscallReturn(ctxt, std))
    sys.stdout.write(" = %s\n" % return_value)

def debug_entry(ctxt, std):
    global syscalls
    syscall_function = syscalls[pin.GetSyscallNumber(ctxt, std)]
    syscall_args = [hex(pin.GetSyscallArgument(ctxt, std, x)) for x in range(4)]
    sys.stdout.write("%s(%s)" % (syscall_function, ', '.join(syscall_args)))

pin.AddSyscallEntryFunction(debug_entry)
pin.AddSyscallExitFunction(trace_syscall_exit)

# def trace_syscall_exit(trace_addr):
# 	global total

# 	x = pin.TRACE_BblHead(trace_addr)
# 	y = pin.BBL_Address(x)
# 	instrucs = pin.BBL_NumIns(x)
# 	total += instrucs
# 	info.write("Basic Block @ %x SIZE: %x NUM INS= IN BLOCK: %x  TOTAL: %x\n" % (y, pin.BBL_Size(x), instrucs, total ))

# pin.TRACE_AddInstrumentFunction(trace_syscall_exit)
