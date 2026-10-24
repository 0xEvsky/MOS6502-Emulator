#pragma once

#include "types.h"
#include "cpu.h"

enum class Mode { Implied, Immediate, ZeroPage, ZeroPageX, ZeroPageY, Absolute, AbsoluteX, AbsoluteY, IndirectPreX, IndirectPostY};

struct Instruction {
    void (*op)(CPU&, Word addr);   
    Mode mode;                    
};

void lda(CPU& cpu, Word addr);
void ldx(CPU& cpu, Word addr);
void ldy(CPU& cpu, Word addr);

void sta(CPU& cpu, Word addr);
void stx(CPU& cpu, Word addr);
void sty(CPU& cpu, Word addr);

void tax(CPU& cpu, Word);
void tay(CPU& cpu, Word); 
void tsx(CPU& cpu, Word);
void txa(CPU& cpu, Word);
void txs(CPU& cpu, Word);
void tya(CPU& cpu, Word);
