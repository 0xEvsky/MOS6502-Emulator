#include "../include/instructions.h"
#include "../include/cpu.h"
#include <stdexcept>

namespace {

    void require_callback(bool present, const char* name) {
        if (!present) {
            throw std::invalid_argument(name);
        }
    }

    Byte get_register(const CPU& cpu, RegisterGetter getter) {
        require_callback(getter != nullptr, "instruction requires a getter");
        return (cpu.*getter)();
    }

    void set_register(CPU& cpu, RegisterSetter setter, Byte value) {
        require_callback(setter != nullptr, "instruction requires a setter");
        (cpu.*setter)(value);
    }

}

void update_zn_flags(CPU& cpu, Byte value) {
    cpu.setZ(value == 0);
    cpu.setN((value >> 7) & 1);
}

void load(CPU& cpu, Word addr, const InstructionArgs& args) {
    Byte value = cpu.mem_read(addr);
    set_register(cpu, args.setter, value);
    update_zn_flags(cpu, value);
}

void store(CPU& cpu, Word addr, const InstructionArgs& args) {
    cpu.mem_write(addr, get_register(cpu, args.getter));
}

void transfer(CPU& cpu, Word, const InstructionArgs& args) {
    Byte value = get_register(cpu, args.getter);
    set_register(cpu, args.setter, value);
    update_zn_flags(cpu, value);
}

void transfer_without_flags(CPU& cpu, Word, const InstructionArgs& args) {
    set_register(cpu, args.setter, get_register(cpu, args.getter));
}

void push(CPU& cpu, Word, const InstructionArgs& args) {
    cpu.stack_push(get_register(cpu, args.getter));
}

void pla(CPU& cpu, Word, const InstructionArgs& args) {
    Byte value = cpu.stack_pull();
    set_register(cpu, args.setter, value);
    update_zn_flags(cpu, value);
}

void plp(CPU& cpu, Word, const InstructionArgs& args) {
    set_register(cpu, args.setter, cpu.stack_pull());
}
