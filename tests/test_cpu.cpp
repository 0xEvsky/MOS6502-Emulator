#include <gtest/gtest.h>
#include "../include/cpu.h"

class CPUTest : public ::testing::Test {
    protected:
        CPU cpu;
        void SetUp() override {cpu.reset();}
};

TEST_F(CPUTest, ResetInitializesRegisters) {
    EXPECT_EQ(cpu.getPC(), 0xFFFC);
    EXPECT_EQ(cpu.getSP(), 0x0100);
    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getX(), 0x00);
    EXPECT_EQ(cpu.getY(), 0x00);
    EXPECT_EQ(cpu.getC(), 0);
    EXPECT_EQ(cpu.getZ(), 0);
    EXPECT_EQ(cpu.getI(), 0);
    EXPECT_EQ(cpu.getD(), 0);
    EXPECT_EQ(cpu.getB(), 0);
    EXPECT_EQ(cpu.getV(), 0);
    EXPECT_EQ(cpu.getN(), 0);
}

TEST_F(CPUTest, AccessorsUpdateRegistersAndFlags) {
    cpu.setPC(0x1234);
    cpu.setSP(0x78);
    cpu.setA(0x01);
    cpu.setX(0x02);
    cpu.setY(0x03);
    cpu.setC();
    cpu.setZ();
    cpu.setI();
    cpu.setD();
    cpu.setB();
    cpu.setV();
    cpu.setN();

    EXPECT_EQ(cpu.getPC(), 0x1234);
    EXPECT_EQ(cpu.getSP(), 0x0178);
    EXPECT_EQ(cpu.getA(), 0x01);
    EXPECT_EQ(cpu.getX(), 0x02);
    EXPECT_EQ(cpu.getY(), 0x03);
    EXPECT_EQ(cpu.getC(), 1);
    EXPECT_EQ(cpu.getZ(), 1);
    EXPECT_EQ(cpu.getI(), 1);
    EXPECT_EQ(cpu.getD(), 1);
    EXPECT_EQ(cpu.getB(), 1);
    EXPECT_EQ(cpu.getV(), 1);
    EXPECT_EQ(cpu.getN(), 1);

    cpu.setC();
    cpu.setZ();
    cpu.setI();
    cpu.setD();
    cpu.setB();
    cpu.setV();
    cpu.setN();

    EXPECT_EQ(cpu.getC(), 0);
    EXPECT_EQ(cpu.getZ(), 0);
    EXPECT_EQ(cpu.getI(), 0);
    EXPECT_EQ(cpu.getD(), 0);
    EXPECT_EQ(cpu.getB(), 0);
    EXPECT_EQ(cpu.getV(), 0);
    EXPECT_EQ(cpu.getN(), 0);
}

TEST_F(CPUTest, FetchByteIncrementsPC) {
    cpu.mem_write(0xFFFC, 0x42);
    Byte value = cpu.fetch_byte();
    EXPECT_EQ(value, 0x42);
    EXPECT_EQ(cpu.getPC(), 0xFFFD);
}

TEST_F(CPUTest, FetchWordIncrementsPC) {
    cpu.mem_write(0xFFFC, 0x34);
    cpu.mem_write(0xFFFD, 0x12);
    Word value = cpu.fetch_word();
    EXPECT_EQ(value, 0x1234);
    EXPECT_EQ(cpu.getPC(), 0xFFFE);
}
