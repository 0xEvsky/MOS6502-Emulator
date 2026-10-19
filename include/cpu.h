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

    // helpers
    Byte fetch_byte();
    Word fetch_word();
    Word resolve_addr(Mode m);

    
    void reset();
    Byte fetch();
    void execute(Byte opcode);
};
