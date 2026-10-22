#include "../include/instructions.h"
#include "../include/cpu.h"

void lda(CPU& cpu, Word addr) {cpu.setA(cpu.mem_read(addr));}
void ldx(CPU& cpu, Word addr) {cpu.setX(cpu.mem_read(addr));}
void ldy(CPU& cpu, Word addr) {cpu.setY(cpu.mem_read(addr));}
void sta(CPU& cpu, Word addr) {cpu.mem_write(addr, cpu.getA());}
