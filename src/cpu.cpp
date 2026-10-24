#include <array>
#include "../include/cpu.h"
#include "../include/instructions.h"

CPU::CPU()
    : PC(0), SP(0), A(0), X(0), Y(0), C(0), Z(0), I(0), D(0), B(0), V(0), N(0) {}

Word CPU::getPC() const {return PC;}
void CPU::setPC(Word value) {PC = value;}
Word CPU::getSP() const {return SP;}
void CPU::setSP(Byte value) {SP = 0x0100 + value;}
Byte CPU::getA() const {return A;}
void CPU::setA(Byte value) {A = value;}
Byte CPU::getX() const {return X;}
void CPU::setX(Byte value) {X = value;}
Byte CPU::getY() const {return Y;}
void CPU::setY(Byte value) {Y = value;}

Byte CPU::getC() const {return C;}
void CPU::setC() {C = !C;}
Byte CPU::getZ() const {return Z;}
void CPU::setZ() {Z = !Z;}
Byte CPU::getI() const {return I;}
void CPU::setI() {I = !I;}
Byte CPU::getD() const {return D;}
void CPU::setD() {D = !D;}
Byte CPU::getB() const {return B;}
void CPU::setB() {B = !B;}
Byte CPU::getV() const {return V;}
void CPU::setV() {V = !V;}
Byte CPU::getN() const {return N;}
void CPU::setN() {N = !N;}

void CPU::reset()                             //method to mimic the resetting proccess
{
    setPC(0xFFFC);
    setSP(0x0100);                      //the stack beings at 0x0100 in the memory
    if (getC()) setC();
    if (getZ()) setZ();
    if (getI()) setI();
    if (getD()) setD();
    if (getB()) setB();
    if (getV()) setV();
    if (getN()) setN();
    setA(0x00);
    setX(0x00);
    setY(0x00);
}

Byte CPU::mem_read(Word addr) {return mem.read(addr);}
void CPU::mem_write(Word addr, Byte data) {mem.write(addr, data);}

Byte CPU::stack_read() {return mem_read(getSP());}
void CPU::stack_write(Byte data) {mem_write(getSP(), data);}

Byte CPU::fetch_byte() {
    Word addr = getPC();
    setPC(addr + 1);
    return mem_read(addr);
}
Word CPU::fetch_word() {
    Byte low = fetch_byte();
    Word high = fetch_byte();
    high <<= 8; // Shift the high byte to the left by 8 bits
    Word addr = high | low; // Combine the high and low bytes to form the address
    return addr;
}

Word CPU::fetch_indexed_indirect(Byte reg) {
    Byte operand = fetch_byte();
    Byte ptr = Byte(operand + reg);
    Byte low = mem_read(ptr);
    Byte high = mem_read(Byte(ptr + 1));
    return (high << 8) | low;
}

Word CPU::fetch_indirect_indexed(Byte reg) {
    Byte operand = fetch_byte();
    Byte ptr = Byte(operand);
    Byte low = mem_read(ptr);
    Byte high = mem_read(Byte(ptr + 1));
    return ((high << 8) | low) + reg;
}

Byte CPU::fetch() {
    Byte opcode = fetch_byte();
    return opcode;
}


Word CPU::resolve_addr(Mode m) {
    switch (m) {
        case (Mode::Immediate): {
            Word addr = getPC();
            setPC(addr + 1);
            return addr;
        }
        case (Mode::ZeroPage):      return fetch_byte();
        case (Mode::ZeroPageX):     return Byte(fetch_byte() + getX());
        case (Mode::ZeroPageY):     return Byte(fetch_byte() + getY());
        case (Mode::Absolute):      return fetch_word();
        case (Mode::AbsoluteX):     return fetch_word() + getX();
        case (Mode::AbsoluteY):     return fetch_word() + getY();
        case (Mode::IndirectPreX):  return fetch_indexed_indirect(getX());
        case (Mode::IndirectPostY): return fetch_indirect_indexed(getY());

    default:
        return 0x0000;
    }
}

const Instruction& CPU::decode(Byte opcode) {
    static const std::array<Instruction, 256> instruction_table = []{
        std::array<Instruction, 256> table{};
        // LDA
        table[0xA9] = {lda, Mode::Immediate};
        table[0xA5] = {lda, Mode::ZeroPage};
        table[0xB5] = {lda, Mode::ZeroPageX};
        table[0xAD] = {lda, Mode::Absolute};
        table[0xBD] = {lda, Mode::AbsoluteX};
        table[0xB9] = {lda, Mode::AbsoluteY};
        table[0xA1] = {lda, Mode::IndirectPreX};
        table[0xB1] = {lda, Mode::IndirectPostY};

        //ldx
        table[0xA2] = {ldx, Mode::Immediate};
        table[0xA6] = {ldx, Mode::ZeroPage};
        table[0xB6] = {ldx, Mode::ZeroPageY};
        table[0xAE] = {ldx, Mode::Absolute};
        table[0xBE] = {ldx, Mode::AbsoluteY};

        //ldy
        table[0xA0] = {ldy, Mode::Immediate};
        table[0xA4] = {ldy, Mode::ZeroPage};
        table[0xB4] = {ldy, Mode::ZeroPageX};
        table[0xAC] = {ldy, Mode::Absolute};
        table[0xBC] = {ldy, Mode::AbsoluteX};

        // STA
        table[0x85] = {sta, Mode::ZeroPage};
        table[0x95] = {sta, Mode::ZeroPageX};
        table[0x8D] = {sta, Mode::Absolute};
        table[0x9D] = {sta, Mode::AbsoluteX};
        table[0x99] = {sta, Mode::AbsoluteY};
        table[0x81] = {sta, Mode::IndirectPreX};
        table[0x91] = {sta, Mode::IndirectPostY};

        // STX
        table[0x86] = {stx, Mode::ZeroPage};
        table[0x96] = {stx, Mode::ZeroPageY};
        table[0x8E] = {stx, Mode::Absolute};

        // STY
        table[0x84] = {sty, Mode::ZeroPage};
        table[0x94] = {sty, Mode::ZeroPageX};
        table[0x8C] = {sty, Mode::Absolute};

        // T--
        table[0xAA] = {tax, Mode::Implied};
        table[0xA8] = {tay, Mode::Implied};
        table[0xBA] = {tsx, Mode::Implied};
        table[0x8A] = {txa, Mode::Implied};
        table[0x9A] = {txs, Mode::Implied};
        table[0x98] = {tya, Mode::Implied};
        return table;
    }();
    return instruction_table[opcode];
}

void CPU::execute(Byte opcode) {
    Instruction ins = decode(opcode);
    if (!ins.op) return; // unused opcode
    Word addr = resolve_addr(ins.mode);
    ins.op(*this, addr);
}
