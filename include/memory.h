#pragma once

#include "types.h"
#include <vector>

struct Mem
{
    std::vector<Byte> data;

    Mem() : data(1024 * 64, 0) {}

    size_t size();
    Byte read(Word addr);
    void write(Word addr, Byte value);
    void load(Word start_addr, const Byte* program, size_t size);
    void reset();
};
