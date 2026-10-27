#include <array>
#include "../include/cpu.h"
#include "../include/instructions.h"

CPU::CPU()
    : PC(0), SP(0), A(0), X(0), Y(0), C(0), Z(0), I(0), D(0), B(0), V(0), N(0) {}

Word CPU::getPC() const {return PC;}
Word CPU::getSP() const {return SP;}
Byte CPU::getSPByte() const {return static_cast<Byte>(SP);}
Byte CPU::get_status_for_push() const {return get_status_flag(true);}
Byte CPU::getA() const {return A;}
Byte CPU::getX() const {return X;}
Byte CPU::getY() const {return Y;}

void CPU::setPC(Word value) {PC = value;}
void CPU::setSP(Byte value) {SP = 0x0100 + value;}
void CPU::setA(Byte value) {A = value;}
void CPU::setX(Byte value) {X = value;}
void CPU::setY(Byte value) {Y = value;}

Byte CPU::read_bit(Word data, int bit_index) {return ((data >> bit_index) & 1);}

Byte CPU::get_status_flag(bool b_flag) const {return (getN() << 7) | (getV() << 6) | (1 << 5)
                            | (b_flag << 4) | (getD() << 3) | (getI() << 2)
                            | (getZ() << 1) | getC();}

void CPU::set_status_flag(Byte data) {
    setN(read_bit(data, 7));
    setV(read_bit(data, 6));
    setD(read_bit(data, 3));
    setI(read_bit(data, 2));
    setZ(read_bit(data, 1));
    setC(read_bit(data, 0));
}

Byte CPU::getN() const {return N;}
Byte CPU::getV() const {return V;}
Byte CPU::getD() const {return D;}
Byte CPU::getB() const {return B;}
Byte CPU::getI() const {return I;}
Byte CPU::getZ() const {return Z;}
Byte CPU::getC() const {return C;}

void CPU::setN(Byte value) {N = value;}
void CPU::setV(Byte value) {V = value;}
void CPU::setD(Byte value) {D = value;}
void CPU::setB(Byte value) {B = value;}
void CPU::setI(Byte value) {I = value;}
void CPU::setZ(Byte value) {Z = value;}
void CPU::setC(Byte value) {C = value;}

void CPU::reset()                             //method to mimic the resetting proccess
{
    setPC(0xFFFC);
    setSP(0x0100);                      //the stack beings at 0x0100 in the memory
    setC(0);
    setZ(0);
    setI(0);
    setD(0);
    setB(0);
    setV(0);
    setN(0);
    setA(0x00);
    setX(0x00);
    setY(0x00);
}

Byte CPU::mem_read(Word addr) {return mem.read(addr);}
void CPU::mem_write(Word addr, Byte data) {mem.write(addr, data);}

Byte CPU::stack_read() {return mem_read(getSP());}
void CPU::stack_write(Byte data) {mem_write(getSP(), data);}

void CPU::stack_push(Byte data) {
    stack_write(data);
    Word sp = getSP();
    setSP(static_cast<Byte>(sp - 1));
}

Byte CPU::stack_pull() {
    Word sp = getSP();
    setSP(static_cast<Byte>(sp + 1));
    return stack_read();
}

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
        table[0xA9] = {load, Mode::Immediate, {nullptr, &CPU::setA}};
        table[0xA5] = {load, Mode::ZeroPage, {nullptr, &CPU::setA}};
        table[0xB5] = {load, Mode::ZeroPageX, {nullptr, &CPU::setA}};
        table[0xAD] = {load, Mode::Absolute, {nullptr, &CPU::setA}};
        table[0xBD] = {load, Mode::AbsoluteX, {nullptr, &CPU::setA}};
        table[0xB9] = {load, Mode::AbsoluteY, {nullptr, &CPU::setA}};
        table[0xA1] = {load, Mode::IndirectPreX, {nullptr, &CPU::setA}};
        table[0xB1] = {load, Mode::IndirectPostY, {nullptr, &CPU::setA}};

        // LDX
        table[0xA2] = {load, Mode::Immediate, {nullptr, &CPU::setX}};
        table[0xA6] = {load, Mode::ZeroPage, {nullptr, &CPU::setX}};
        table[0xB6] = {load, Mode::ZeroPageY, {nullptr, &CPU::setX}};
        table[0xAE] = {load, Mode::Absolute, {nullptr, &CPU::setX}};
        table[0xBE] = {load, Mode::AbsoluteY, {nullptr, &CPU::setX}};

        // LDY
        table[0xA0] = {load, Mode::Immediate, {nullptr, &CPU::setY}};
        table[0xA4] = {load, Mode::ZeroPage, {nullptr, &CPU::setY}};
        table[0xB4] = {load, Mode::ZeroPageX, {nullptr, &CPU::setY}};
        table[0xAC] = {load, Mode::Absolute, {nullptr, &CPU::setY}};
        table[0xBC] = {load, Mode::AbsoluteX, {nullptr, &CPU::setY}};

        // STA
        table[0x85] = {store, Mode::ZeroPage, {&CPU::getA, nullptr}};
        table[0x95] = {store, Mode::ZeroPageX, {&CPU::getA, nullptr}};
        table[0x8D] = {store, Mode::Absolute, {&CPU::getA, nullptr}};
        table[0x9D] = {store, Mode::AbsoluteX, {&CPU::getA, nullptr}};
        table[0x99] = {store, Mode::AbsoluteY, {&CPU::getA, nullptr}};
        table[0x81] = {store, Mode::IndirectPreX, {&CPU::getA, nullptr}};
        table[0x91] = {store, Mode::IndirectPostY, {&CPU::getA, nullptr}};

        // STX
        table[0x86] = {store, Mode::ZeroPage, {&CPU::getX, nullptr}};
        table[0x96] = {store, Mode::ZeroPageY, {&CPU::getX, nullptr}};
        table[0x8E] = {store, Mode::Absolute, {&CPU::getX, nullptr}};

        // STY
        table[0x84] = {store, Mode::ZeroPage, {&CPU::getY, nullptr}};
        table[0x94] = {store, Mode::ZeroPageX, {&CPU::getY, nullptr}};
        table[0x8C] = {store, Mode::Absolute, {&CPU::getY, nullptr}};

        // Transfers
        table[0xAA] = {transfer, Mode::Implied, {&CPU::getA, &CPU::setX}};
        table[0xA8] = {transfer, Mode::Implied, {&CPU::getA, &CPU::setY}};
        table[0xBA] = {transfer, Mode::Implied, {&CPU::getSPByte, &CPU::setX}};
        table[0x8A] = {transfer, Mode::Implied, {&CPU::getX, &CPU::setA}};
        table[0x9A] = {transfer_without_flags, Mode::Implied, {&CPU::getX, &CPU::setSP}};
        table[0x98] = {transfer, Mode::Implied, {&CPU::getY, &CPU::setA}};

        // Stack operations
        table[0x48] = {push, Mode::Implied, {&CPU::getA, nullptr}};
        table[0x08] = {push, Mode::Implied, {&CPU::get_status_for_push, nullptr}};
        table[0x68] = {pla, Mode::Implied, {nullptr, &CPU::setA}};
        table[0x28] = {plp, Mode::Implied, {nullptr, &CPU::set_status_flag}};
        return table;
    }();
    return instruction_table[opcode];
}

void CPU::execute(Byte opcode) {
    Instruction ins = decode(opcode);
    if (!ins.op) return; // unused opcode
    Word addr = resolve_addr(ins.mode);
    ins.op(*this, addr, ins.args);
}
