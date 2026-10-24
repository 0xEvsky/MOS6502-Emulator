
from pathlib import Path
import re
import html

ROOT = Path(__file__).resolve().parent.parent
CPU_CPP = ROOT / "src" / "cpu.cpp"
README = ROOT / "README.md"
SVG = ROOT / "assets" / "instruction-progress.svg"

# The 56 official NMOS 6502 instruction mnemonics.
MNEMONICS = """
ADC AND ASL BCC BCS BEQ BIT BMI BNE BPL BRK
BVC BVS CLC CLD CLI CLV CMP CPX CPY DEC DEX
DEY EOR INC INX INY JMP JSR LDA LDX LDY LSR
NOP ORA PHA PHP PLA PLP ROL ROR RTI RTS SBC
SEC SED SEI STA STX STY TAX TAY TSX TXA TXS TYA
""".split()

# Count mnemonics whose handlers are actually registered in the
# opcode table, rather than merely declared or defined as functions.
source = CPU_CPP.read_text(encoding="utf-8")
registered = set(
    re.findall(
        r"table\s*\[\s*0x[0-9A-Fa-f]+\s*\]\s*=\s*\{\s*(\w+)\s*,",
        source,
    )
)
implemented = {name.upper() for name in registered} & set(MNEMONICS)

total = len(MNEMONICS)
count = len(implemented)
percent = round(count / total * 100)

# Draw one labeled box per official instruction mnemonic.
columns = 14
cell_w, cell_h = 46, 38
rows = (total + columns - 1) // columns
width, height = columns * cell_w, rows * cell_h + 32

parts = [
    f'<svg xmlns="http://www.w3.org/2000/svg" '
    f'width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
    '<rect width="100%" height="100%" rx="8" fill="#ffffff"/>',
    f'<text x="8" y="20" font-family="sans-serif" font-size="14" '
    f'fill="#24292f">Instruction coverage: {count}/{total} ({percent}%)</text>',
]

for i, mnemonic in enumerate(MNEMONICS):
    x = (i % columns) * cell_w + 3
    y = (i // columns) * cell_h + 30
    color = "#22c55e" if mnemonic in implemented else "#e5e7eb"
    text_color = "#14532d" if mnemonic in implemented else "#374151"

    parts.append(
        f'<rect x="{x}" y="{y}" width="40" height="28" rx="4" '
        f'fill="{color}"/>'
        f'<text x="{x + 20}" y="{y + 18}" text-anchor="middle" '
        f'font-family="monospace" font-size="11" font-weight="600" '
        f'fill="{text_color}">{html.escape(mnemonic)}</text>'
    )

parts.append("</svg>")

SVG.parent.mkdir(parents=True, exist_ok=True)
SVG.write_text("\n".join(parts), encoding="utf-8")

# Replace the progress image and its summary in README.
readme = README.read_text(encoding="utf-8")
readme = re.sub(
    r"!\[Instruction Progress\]\([^)]+\)",
    "![Instruction Progress](assets/instruction-progress.svg)",
    readme,
)
readme = re.sub(
    r"\*\*\d+\s*/\s*56 official instruction mnemonics implemented "
    r"\(\d+%\)\*\*",
    f"**{count} / {total} official instruction mnemonics implemented "
    f"({percent}%)**",
    readme,
)
README.write_text(readme, encoding="utf-8")

print(f"Instruction progress: {count}/{total} ({percent}%)")
print(f"Implemented: {', '.join(sorted(implemented))}")
