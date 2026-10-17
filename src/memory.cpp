#include "memory.h"
using namespace std;

bool Mem::Validate(Word addr) {return addr > 0x0000 && addr < 0xFFFF;}
Byte Mem::Read(Word addr) {
    if (Validate(addr))
        return Data[addr];
}

void Mem::Write(Word addr, Byte value) {
    if (Validate(addr))
        Data[addr] = value;
}

void Mem::LoadProgram(Word start_addr, const Byte* program, int size) {
    for (int i = 0; i < size; ++i) {
        Data[start_addr + i] = program[i];
    }
}

void Mem::Reset() {fill(Data.begin(), Data.end(), 0);}
