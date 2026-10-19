#pragma once

#include "memory.h"
#include "types.h"

struct CPU
{
    Mem mem;

    Word PC;           //program counter
    Word SP;           //stack pointer

    Byte A, X, Y;    //registers

    Byte C : 1;     //status flags
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    void reset();
    Byte fetch();
    Word resolve_addr(Mode m);
    void execute(Byte opcode);
};
