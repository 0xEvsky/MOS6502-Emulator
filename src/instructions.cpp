#include "instructions.h"
#include "cpu.h"

void LDA_Immediate(CPU& cpu) {
    Byte value = cpu.mem.Read(cpu.PC++);
    cpu.A = value;
}

void STA_ZeroPage(CPU& cpu) {
    Byte addr = cpu.mem.Read(cpu.PC++);
    cpu.mem.Write(addr, cpu.A);
}
