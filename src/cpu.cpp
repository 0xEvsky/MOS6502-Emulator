#include "cpu.h"
#include "instructions.h"

void CPU::Reset()                             //method to mimic the resetting proccess
{
    PC = 0xFFFC;
    SP = 0x0100;                        //the stack beings at 0x01000 in the memory
    C = Z = I = D = B = V = N = 0;     //all flags are deactive
    A = X = Y = 0;                    //registers are empty
}

Byte CPU::Fetch() {
    Byte opcode = mem.Read(PC++);
    return opcode;
}

void CPU::Execute(Byte opcode) {
    static void (*instructionTable[256])(CPU&) = {};
    instructionTable[0xA9] = LDA_Immediate;
    instructionTable[0x85] = STA_ZeroPage;

    if (instructionTable[opcode]) {
        instructionTable[opcode](*this);
    }
}
