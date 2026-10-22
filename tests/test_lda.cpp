#include <gtest/gtest.h>
#include "../include/cpu.h"

class LDAAddressingModesTest:public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
        }
};

TEST_F(LDAAddressingModesTest, LoadsImmediateValue) {
    cpu.mem_write(0xFFFC, 0x04);
    cpu.execute(0xA9);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsZeroPageValue) {
    cpu.mem_write(0xFFFC, 0x03);
    cpu.mem_write(0x03, 0x04);
    cpu.execute(0xA5);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsZeroPageXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);
    cpu.mem_write(0x03, 0x04);
    cpu.execute(0xB5);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsAbslouteValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2000, 0x04);
    cpu.execute(0xAD);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsAbslouteXValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);
    cpu.setX(1);
    cpu.execute(0xBD);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsAbslouteYValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);
    cpu.setY(1);
    cpu.execute(0xB9);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsIndirectPreXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0x00, 0x00);
    cpu.mem_write(0x01, 0x20);
    cpu.mem_write(0x2000, 0x04);
    cpu.execute(0xA1);
    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAAddressingModesTest, LoadsIndirectPostYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0xFF, 0x00);
    cpu.mem_write(0x00, 0x20);
    cpu.mem_write(0x2001, 0x04);
    cpu.execute(0xB1);
    EXPECT_EQ(cpu.getA(), 0x04);
}
