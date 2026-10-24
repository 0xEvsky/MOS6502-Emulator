#pragma once

#include <array>
#include "memory.h"
#include "types.h"

enum class Mode;
struct Instruction;

struct CPU
{
    Mem mem;

private:
    Word PC;           //program counter
    Word SP;           //stack pointer

    Byte A, X, Y;      //registers

    Byte C : 1;        //status flags
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

public:
    CPU();

    Word getPC() const;
    void setPC(Word value);
    Word getSP() const;
    void setSP(Byte value);
    Byte getA() const;
    void setA(Byte value);
    Byte getX() const;
    void setX(Byte value);
    Byte getY() const;
    void setY(Byte value);

    Byte getC() const;
    void setC();
    Byte getZ() const;
    void setZ();
    Byte getI() const;
    void setI();
    Byte getD() const;
    void setD();
    Byte getB() const;
    void setB();
    Byte getV() const;
    void setV();
    Byte getN() const;
    void setN();

    void reset();
    Byte mem_read(Word addr);
    void mem_write(Word addr, Byte data);
    Byte stack_read();
    void stack_write(Byte data);
    Byte fetch_byte();
    Word fetch_word();
    Word fetch_indexed_indirect(Byte reg);
    Word fetch_indirect_indexed(Byte reg);
    Byte fetch();
    Word resolve_addr(Mode m);
    const Instruction& decode(Byte opcode);
    void execute(Byte opcode);
};
