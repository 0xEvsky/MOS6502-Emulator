#include "../include/instructions.h"
#include "../include/cpu.h"

void lda(CPU& cpu, Word addr) {cpu.A = cpu.mem_read(addr);}
