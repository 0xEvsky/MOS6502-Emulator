#include "../include/instructions.h"
#include "../include/cpu.h"

void lda(CPU& cpu, Word addr) {cpu.setA(cpu.mem_read(addr));}
void ldx(CPU& cpu, Word addr) {cpu.setX(cpu.mem_read(addr));}
void ldy(CPU& cpu, Word addr) {cpu.setY(cpu.mem_read(addr));}

void sta(CPU& cpu, Word addr) {cpu.mem_write(addr, cpu.getA());}
void stx(CPU& cpu, Word addr) {cpu.mem_write(addr, cpu.getX());}
void sty(CPU& cpu, Word addr) {cpu.mem_write(addr, cpu.getY());}

void tax(CPU& cpu, Word) {cpu.setX(cpu.getA());}
void tay(CPU& cpu, Word) {cpu.setY(cpu.getA());}
void tsx(CPU& cpu, Word) {cpu.setX(cpu.getSP());}
void txa(CPU& cpu, Word) {cpu.setA(cpu.getX());}
void txs(CPU& cpu, Word) {cpu.setSP(cpu.getX());}
void tya(CPU& cpu, Word) {cpu.setA(cpu.getY());}
