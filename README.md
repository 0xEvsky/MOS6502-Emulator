# MOS Technology 6502 Emulator

A MOS 6502 CPU emulator written in C++ from scratch.

This project is a learning-oriented implementation of the 6502 microprocessor, focused on understanding CPU architecture, instruction decoding, addressing modes, memory access, and instruction execution.

**Status:** Work in progress.

## Instruction Set Progress

![Instruction Progress](https://progress-bar.xyz/7/?title=Instruction%20Coverage&width=400&color=22c55e)

**4 / 56 official instruction mnemonics implemented (7%)**

Progress is currently tracked by implemented instruction mnemonics. The goal is to implement all 56 official NMOS 6502 instruction types. This does not yet measure addressing-mode completeness, cycle accuracy, or overall emulator correctness.

## Features

- **CPU core:** Program counter, stack pointer, accumulator, X and Y index registers, and processor status flags.
- **Memory:** Memory read/write operations and byte/word fetching.
- **Instruction decoding:** Opcode lookup using a 256-entry instruction table.
- **Addressing modes:** Immediate, zero page, zero-page indexed, absolute, absolute indexed, indexed indirect, and indirect indexed.
- **Testing:** GoogleTest unit tests covering memory, CPU behavior, and instruction addressing modes.
- **Build system:** CMake with C++17.

## Getting Started

### Prerequisites

- A C++17-compatible compiler
- CMake 3.14 or later
- Git
- Internet access during initial CMake configuration to download GoogleTest

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

After execution, the accumulator contains `0x42`, assuming the CPU's program counter is positioned at the immediate operand.

## Development Roadmap

- [x] CPU and memory foundations
- [x] Instruction lookup and decoding
- [x] LDA, LDX, LDY, and STA implementations
- [x] Addressing-mode tests for LDA and STA
- [ ] Implement remaining official 6502 instructions
- [ ] Improve processor status flag handling
- [ ] Add instruction cycle counting and timing accuracy
- [ ] Implement a program-loading and execution loop
- [ ] Expand test coverage and validate against established 6502 test suites

## References

- [6502.org — Technical resources](https://www.6502.org/)
- [NESdev Wiki — 6502 instruction reference](https://www.nesdev.org/wiki/CPU)
- [6502 Opcode Reference](https://www.masswerk.at/6502/6502_instruction_set.html)

---

This project is intended for educational purposes and is under active development. It does not yet implement the complete 6502 instruction set or cycle-accurate CPU behavior.
