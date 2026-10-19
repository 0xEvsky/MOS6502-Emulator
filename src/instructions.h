#pragma once

#include "types.h"
#include "cpu.h"

enum class Mode { Implied, Immediate, ZeroPage, ZeroPageX, ZeroPageY, Absolute, AbsoluteX, AbsoluteY, IndirectX, IndirectY};

struct Instruction {
    void (*op)(CPU&, Word addr);   
    Mode mode;                    
};

void lda(CPU& cpu, Word addr);
