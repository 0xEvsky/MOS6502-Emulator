#include <gtest/gtest.h>
#include "../include/cpu.h"

class CPUTest : public ::testing::Test {
    protected:
        CPU cpu;
        void SetUp() override {cpu.reset();}
};

TEST_F(CPUTest, ResetInitializesRegisters) {
    EXPECT_EQ(cpu.PC, 0xFFFC);
    EXPECT_EQ(cpu.SP, 0x0100);
    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_EQ(cpu.X, 0x00);
    EXPECT_EQ(cpu.Y, 0x00);
    EXPECT_EQ(cpu.C, 0);
    EXPECT_EQ(cpu.Z, 0); 
    EXPECT_EQ(cpu.I, 0);
    EXPECT_EQ(cpu.D, 0);
    EXPECT_EQ(cpu.B, 0);
    EXPECT_EQ(cpu.V, 0);
    EXPECT_EQ(cpu.N, 0);
}

TEST_F(CPUTest, FetchByteIncrementsPC) {
    cpu.mem_write(0xFFFC, 0x42);
    Byte value = cpu.fetch_byte();
    EXPECT_EQ(value, 0x42);
    EXPECT_EQ(cpu.PC, 0xFFFD);
}

TEST_F(CPUTest, FetchWordIncrementsPC) {
    cpu.mem_write(0xFFFC, 0x34);
    cpu.mem_write(0xFFFD, 0x12);
    Word value = cpu.fetch_word();
    EXPECT_EQ(value, 0x1234);
    EXPECT_EQ(cpu.PC, 0xFFFE);
}

TEST_F(CPUTest, ExecutesLDAInstruction) {
    // LDA Immediate
    cpu.mem_write(0xFFFC, 0x01);
    cpu.execute(0xA9); 
    EXPECT_EQ(cpu.A, 0x01);

    // LDA ZeroPageX
    cpu.X = 1;
    cpu.mem_write(0xFFFD, 0x02);
    cpu.mem_write(0x03, 0x04);
    cpu.execute(0xB5); 
    EXPECT_EQ(cpu.A, 0x04);
}