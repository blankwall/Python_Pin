/*without read write checks 
real    0m0.348s
user    0m0.229s
sys     0m0.074s
*/

/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2014 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */

#include "pin.H"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

/* ===================================================================== */
/* Names of malloc and free */
/* ===================================================================== */
#if defined(TARGET_MAC)
#define MALLOC "_malloc"
#define FREE "_free"
#else
#define MALLOC "malloc"
#define REALLOC "realloc"
#define FREE "free"
#endif

#define GUARD_SIZE 32

/* ===================================================================== */
/* Global Variables */
/* ===================================================================== */

std::ofstream TraceFile;

ADDRINT last_malloc = 0;
ADDRINT last_addr = 0;

ADDRINT realloc_x = 0;
ADDRINT ac_re = 0;

ADDRINT canary =  0x0f0f0f0f0f0f0f0f;
ADDRINT canary2 = 0xf0f0f0f0f0f0f0f0;

struct uaf{
    ADDRINT address;
    ADDRINT size;
};

typedef uaf UAF;
vector<UAF*> free_list;
/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "malloctrace.out", "specify trace file name");


VOID ReallocBefore(ADDRINT* name, ADDRINT* size)
{
    if ( realloc_x == 0){
      realloc_x = 1;
    } else {
        if(*size == 0){*name = 0;*size = 0;}
        else if(*name == 0) { return;}    
        else{
          last_malloc = *size;
          *size = *size+GUARD_SIZE*2 + 8;
          *name -= GUARD_SIZE+8;
          realloc_x = 0;
          ac_re = 1;
        }
    }
}


VOID ReallocAfter(ADDRINT* rax_reg)
{
    if(ac_re) { 
        last_addr = *rax_reg;
        *(ADDRINT*)(*rax_reg) = last_malloc;


        unsigned int i;
        for(i = 8; i < GUARD_SIZE+8; i += 8){
            *(ADDRINT*)(*rax_reg+i) = canary;
        }

        for(i = GUARD_SIZE+last_malloc+8; i < last_malloc+(GUARD_SIZE*2)+8 ; i += 8){
            *(ADDRINT*)(*rax_reg+i) = canary;
        }

        *rax_reg = *rax_reg+GUARD_SIZE+8;
    }
    ac_re = 0;
}
 
VOID MallocBefore(CHAR * name, ADDRINT size, ADDRINT* rdi)
{
    *rdi = (GUARD_SIZE*2)+size+8;
    last_malloc = size;
}

VOID MallocAfter(CHAR * name, ADDRINT* rax_reg)
{
        if(!rax_reg) return;

        *(ADDRINT*)(*rax_reg) = last_malloc;

        unsigned int i;
        for(i = 8; i < GUARD_SIZE+8; i += 8){
            *(ADDRINT*)(*rax_reg+i) = canary;
        }

        for(i = GUARD_SIZE+last_malloc+8; i < last_malloc+(GUARD_SIZE*2)+8 ; i += 8){
            *(ADDRINT*)(*rax_reg+i) = canary;
        }

        *rax_reg = *rax_reg+GUARD_SIZE+8;
}


VOID free_1(CHAR * name, ADDRINT size, ADDRINT* val)
{
    ADDRINT k = *(ADDRINT*)(*val-40);
    UAF *tmp = new UAF();
    tmp->address = (ADDRINT)(*val-40);
    tmp->size = k+GUARD_SIZE+8;
    free_list.push_back(tmp);
    *val = 0;
}

VOID ReadAnalysis(CHAR * name, ADDRINT* read, ADDRINT* instruc)
{
        cout << "READ AT: " << read << " : "<< instruc  << " LAST MALLOC : " << last_addr << endl;

        if(read){
            printf("%lx\n", *read);
        }
}

// VOID WriteMem(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, UINT64 memOp)
VOID WriteAnalysis(UINT64 insAddr, std::string insDis, UINT32 opCount, REG reg_r, UINT64 memOp)
{
        //std::cout << std::hex << insAddr << ": " << insDis << " -- Heap  " << memOp << " VALUE: "<<*(ADDRINT*)memOp<< std::endl;

        if(*(ADDRINT*)memOp == canary || *(ADDRINT*)memOp == canary2){
            cout << "HEAP OVERFLOW DETECTED" << endl;
            std::cout << std::hex << insAddr << ": " << insDis << " -- Heap  " << memOp << " VALUE: "<<*(ADDRINT*)memOp<< std::endl;

        }
        ADDRINT add = (ADDRINT)memOp;
        for(unsigned int i = 0; i < free_list.size(); ++i){
            UAF* tmp = free_list[i];
            if(add >= tmp->address && add <= (tmp->address+tmp->size)){
                cout << "UAF DETECTED" << endl;
                std::cout << std::hex << insAddr << ": " << insDis << " -- Heap  " << memOp << " VALUE: "<<*(ADDRINT*)memOp<< std::endl;
            }
        }
}


/* ===================================================================== */
/* Instrumentation routines                                              */
/* ===================================================================== */
   
VOID Image(IMG img, VOID *v)
{
    // Instrument the malloc() and free() functions.  Print the input argument
    // of each malloc() or free(), and the return value of malloc().
    //
    //  Find the malloc() function.
    RTN mallocRtn = RTN_FindByName(img, MALLOC);

    RTN reallocRtn = RTN_FindByName(img, REALLOC);

    if (RTN_Valid(reallocRtn))
    {
        RTN_Open(reallocRtn);

         RTN_InsertCall(reallocRtn, IPOINT_BEFORE, (AFUNPTR)ReallocBefore, 
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0,
            IARG_FUNCARG_ENTRYPOINT_REFERENCE, 1,
            IARG_END);

         RTN_InsertCall(reallocRtn, IPOINT_AFTER, (AFUNPTR)ReallocAfter, 
            IARG_FUNCRET_EXITPOINT_REFERENCE,            
            IARG_END);

        RTN_Close(reallocRtn);

    }


    if (RTN_Valid(mallocRtn))
    {
        RTN_Open(mallocRtn);

        // Instrument malloc() to print the input argument value and the return value.
        RTN_InsertCall(mallocRtn, IPOINT_BEFORE, (AFUNPTR)MallocBefore,
                       IARG_ADDRINT, MALLOC,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                       IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0,
                       IARG_END);

        RTN_InsertCall(mallocRtn, IPOINT_AFTER, (AFUNPTR)MallocAfter,
                       IARG_ADDRINT, MALLOC,
                       IARG_FUNCRET_EXITPOINT_REFERENCE,
                       IARG_END);

        RTN_Close(mallocRtn);
    }

    // Find the free() function.
    RTN freeRtn = RTN_FindByName(img, FREE);
    if (RTN_Valid(freeRtn))
    {
        RTN_Open(freeRtn);
        // Instrument free() to print the input argument value.
        RTN_InsertCall(freeRtn, IPOINT_BEFORE, (AFUNPTR)free_1,
                       IARG_ADDRINT, FREE,
                       IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                       IARG_FUNCARG_ENTRYPOINT_REFERENCE, 0,
                       IARG_END);
        RTN_Close(freeRtn);
    }
}

VOID Instruction(INS ins, VOID *v)
{
  PIN_LockClient();
  IMG img = IMG_FindByAddress(INS_Address(ins));
  PIN_UnlockClient();
  
  if (IMG_Valid(img) && IMG_IsMainExecutable(img)){
        if (INS_OperandCount(ins) > 1 && INS_MemoryOperandIsWritten(ins, 0)){
           INS_InsertCall(
              ins, IPOINT_BEFORE, (AFUNPTR)WriteAnalysis,
              IARG_ADDRINT, INS_Address(ins),
              IARG_PTR, new string(INS_Disassemble(ins)),
              IARG_UINT32, INS_OperandCount(ins),
              IARG_UINT32, INS_OperandReg(ins, 1),
              IARG_MEMORYOP_EA, 0,
              IARG_END);
        }
    }

}

        // if (INS_IsMemoryRead(ins)){
        //   INS_InsertCall(
        //       ins, 
        //       IPOINT_BEFORE, (AFUNPTR)ReadAnalysis,
        //       IARG_ADDRINT, INS_Address(ins),
        //       IARG_MEMORYREAD_EA,
        //       IARG_END);
        // }
        // else 
/* ===================================================================== */

VOID Fini(INT32 code, VOID *v)
{
    TraceFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */
   
INT32 Usage()
{
    cerr << "This tool produces a trace of calls to malloc." << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char *argv[])
{
    // Initialize pin & symbol manager
    PIN_InitSymbols();
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    
    // Write to a file since cout and cerr maybe closed by the application
    TraceFile.open(KnobOutputFile.Value().c_str());
    TraceFile << hex;
    TraceFile.setf(ios::showbase);
    
    // Register Image to be called to instrument functions.
    IMG_AddInstrumentFunction(Image, 0);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
