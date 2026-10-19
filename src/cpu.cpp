#include "cpu.h"
#include "instructions.h"

void CPU::reset()                             //method to mimic the resetting proccess
{
    PC = 0xFFFC;
    SP = 0x0100;                        //the stack beings at 0x01000 in the memory
    C = Z = I = D = B = V = N = 0;     //all flags are deactive
    A = X = Y = 0;                    //registers are empty
}

Byte CPU::fetch() {
    Byte opcode = mem.read(PC++);
    return opcode;
}

Word CPU::resolve_addr(Mode m) {
    switch (m) {
        case (Mode::Immediate): return PC++;
        case (Mode::ZeroPage): return this->mem.read(PC++);
        case (Mode::ZeroPageX): return Byte(this->mem.read(PC++) + X);
        case (Mode::ZeroPageY): return Byte(this->mem.read(PC++) + Y);
        case (Mode::Absolute): {
            Byte high = this->mem.read(PC++);
            high <<= 8; // Shift the high byte to the left by 8 bits
            Byte low = this->mem.read(PC++);
            Word addr = high | low; // Combine the high and low bytes to form the address
            return addr;
        }

    default:
        return 0x0000;
    }
}

void CPU::execute(Byte opcode) {
    static Instruction instructionTable[256] = {};

    instructionTable[0xA9] = {lda, Mode::Immediate};
    instructionTable[0xA5] = {lda, Mode::ZeroPage};
    instructionTable[0xB5] = {lda, Mode::ZeroPageX};
    instructionTable[0xAD] = {lda, Mode::Absolute};
    instructionTable[0xBD] = {lda, Mode::AbsoluteX};
    instructionTable[0xB9] = {lda, Mode::AbsoluteY};
    instructionTable[0xA1] = {lda, Mode::IndirectX};
    instructionTable[0xB1] = {lda, Mode::IndirectY};

    Instruction ins = instructionTable[opcode];
    if (!ins.op) return; // unused opcode
    Word addr = resolve_addr(ins.mode);
    ins.op(*this, addr);
}
