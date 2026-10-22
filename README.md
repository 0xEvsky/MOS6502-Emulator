# MOS Technology 6502 Emulator

A MOS 6502 CPU emulator written in C++ from scratch.

This project is a learning-oriented implementation of the 6502 microprocessor, focused on understanding CPU architecture, instruction decoding, addressing modes, memory access, and instruction execution.

**Status:** Work in progress.

## Features

- **CPU core:** Program counter, stack pointer, accumulator, X and Y index registers, and processor status flags.
- **Memory:** Memory read/write operations and byte/word fetching.
- **Instruction decoding:** Opcode lookup using a 256-entry instruction table.
- **Addressing modes:** Immediate, zero page, zero-page indexed, absolute, absolute indexed, indexed indirect, and indirect indexed.
- **Implemented instructions:**
  - `LDA` — Load Accumulator
  - `LDX` — Load X Register
  - `LDY` — Load Y Register
  - `STA` — Store Accumulator
- **Testing:** GoogleTest unit tests covering memory, CPU behavior, and instruction addressing modes.
- **Build system:** CMake with C++17.

## Getting Started

### Prerequisites

- A C++17-compatible compiler
- CMake 3.14 or later
- Git
- Internet access during the initial CMake configuration to download GoogleTest

### Build

Clone the repository:

```bash
git clone https://github.com/0xEvsky/6502-Emulator.git
cd 6502-Emulator
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

### Run Tests

```bash
ctest --test-dir build --output-on-failure
```

The test executable covers the CPU, memory, and currently implemented instructions.

### Run the Emulator

```bash
./build/emu
```

On Windows, the executable will typically be located at `build/Debug/emu.exe` or `build/emu.exe`, depending on the generator.

The current executable is a minimal entry point; a program-loading and execution loop is still to be developed.

## Example: Loading a Value

The following 6502 assembly instruction loads the immediate value `0x42` into the accumulator:

```asm
LDA #$42
```

Its machine-code opcode is `0xA9`.

In the emulator's current testing approach, the instruction can be invoked directly:

```cpp
CPU cpu;

cpu.reset();
cpu.mem.reset();
cpu.mem_write(0xFFFC, 0x42);

cpu.execute(0xA9);
```

After execution, the accumulator contains `0x42`.


## References

- [6502.org — Technical resources](https://www.6502.org/)
- [NESdev Wiki — 6502 instruction reference](https://www.nesdev.org/wiki/CPU)
- [6502 Opcode Reference](https://www.masswerk.at/6502/6502_instruction_set.html)

---

This project is intended for educational purposes and is under active development. It does not yet implement the complete 6502 instruction set or cycle-accurate CPU behavior.
 
