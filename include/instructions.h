#pragma once

#include "types.h"

struct CPU;

enum class Mode { Implied, Immediate, ZeroPage, ZeroPageX, ZeroPageY, Absolute, AbsoluteX, AbsoluteY, IndirectPreX, IndirectPostY};

using RegisterGetter = Byte (CPU::*)() const;
using RegisterSetter = void (CPU::*)(Byte);

struct InstructionArgs {
    RegisterGetter getter = nullptr;
    RegisterSetter setter = nullptr;
};

using InstructionOperation = void (*)(CPU&, Word, const InstructionArgs&);

struct Instruction {
    InstructionOperation op = nullptr;
    Mode mode = Mode::Implied;
    InstructionArgs args;
};

void update_zn_flags(CPU& cpu, Byte value);
void load(CPU& cpu, Word addr, const InstructionArgs& args);
void store(CPU& cpu, Word addr, const InstructionArgs& args);
void transfer(CPU& cpu, Word addr, const InstructionArgs& args);
void transfer_without_flags(CPU& cpu, Word addr, const InstructionArgs& args);
void push(CPU& cpu, Word addr, const InstructionArgs& args);
void pla(CPU& cpu, Word addr, const InstructionArgs& args);
void plp(CPU& cpu, Word addr, const InstructionArgs& args);
