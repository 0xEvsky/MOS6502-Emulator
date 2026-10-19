#pragma once

#include "types.h"
#include <vector>

struct Mem
{
    std::vector<Byte> data;

    Mem() : data(1024 * 64, 0) {}

    bool validate(Word addr);
    Byte read(Word addr);
    void write(Word addr, Byte value);
    void loadProgram(Word start_addr, const Byte* program, int size);
    void reset();
};
