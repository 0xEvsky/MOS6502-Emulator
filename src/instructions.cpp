#include "instructions.h"
#include "cpu.h"

void lda(CPU& cpu, Word addr) {cpu.A = cpu.mem.read(addr);}
