#include "memory.h"
using namespace std;

bool Mem::validate(Word addr) {return addr > 0x0000 && addr < 0xFFFF;}
Byte Mem::read(Word addr) {
    if (validate(addr))
        return data[addr];
}

void Mem::write(Word addr, Byte value) {
    if (validate(addr))
        data[addr] = value;
}

void Mem::loadProgram(Word start_addr, const Byte* program, int size) {
    for (int i = 0; i < size; ++i) {
        data[start_addr + i] = program[i];
    }
}

void Mem::reset() {fill(data.begin(), data.end(), 0);}
