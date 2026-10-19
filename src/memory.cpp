#include "../include/memory.h"
#include <cassert>
using namespace std;

size_t Mem::size() {return data.size();}

Byte Mem::read(Word addr) {return data[addr];}
void Mem::write(Word addr, Byte value) {data[addr] = value;}

void Mem::load(Word start_addr, const Byte* program, size_t size) {
    assert(static_cast<size_t>(start_addr) + size <= this->size());
    for (size_t i = 0; i < size; ++i) {
        data[start_addr + i] = program[i];
    }
}

void Mem::reset() {fill(data.begin(), data.end(), 0);}
