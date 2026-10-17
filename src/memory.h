#pragma once

#include "types.h"
#include <vector>

struct Mem
{
    std::vector<Byte> Data;

    Mem() : Data(1024 * 64, 0) {}

    bool Validate(Word addr);
    Byte Read(Word addr);
    void Write(Word addr, Byte value);
    void LoadProgram(Word start_addr, const Byte* program, int size);
    void Reset();
};
