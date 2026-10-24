#include <gtest/gtest.h>
#include "../include/cpu.h"

class LDAddressingModesTest : public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
        }
};

TEST_F(LDAddressingModesTest, LDALoadsImmediateValue) {
    cpu.mem_write(0xFFFC, 0x04);

    cpu.execute(0xA9);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsZeroPageValue) {
    cpu.mem_write(0xFFFC, 0x03);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xA5);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsZeroPageXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xB5);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsAbsoluteValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2000, 0x04);

    cpu.execute(0xAD);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsAbsoluteXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);

    cpu.execute(0xBD);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsAbsoluteYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);

    cpu.execute(0xB9);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsIndirectPreXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0x00, 0x00);
    cpu.mem_write(0x01, 0x20);
    cpu.mem_write(0x2000, 0x04);

    cpu.execute(0xA1);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDALoadsIndirectPostYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0xFF, 0x00);
    cpu.mem_write(0x00, 0x20);
    cpu.mem_write(0x2001, 0x04);

    cpu.execute(0xB1);

    EXPECT_EQ(cpu.getA(), 0x04);
}

TEST_F(LDAddressingModesTest, LDXLoadsImmediateValue) {
    cpu.mem_write(0xFFFC, 0x04);

    cpu.execute(0xA2);

    EXPECT_EQ(cpu.getX(), 0x04);
}

TEST_F(LDAddressingModesTest, LDXLoadsZeroPageValue) {
    cpu.mem_write(0xFFFC, 0x03);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xA6);

    EXPECT_EQ(cpu.getX(), 0x04);
}

TEST_F(LDAddressingModesTest, LDXLoadsZeroPageYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x02);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xB6);

    EXPECT_EQ(cpu.getX(), 0x04);
}

TEST_F(LDAddressingModesTest, LDXLoadsAbsoluteValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2000, 0x04);

    cpu.execute(0xAE);

    EXPECT_EQ(cpu.getX(), 0x04);
}

TEST_F(LDAddressingModesTest, LDXLoadsAbsoluteYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);

    cpu.execute(0xBE);

    EXPECT_EQ(cpu.getX(), 0x04);
}

TEST_F(LDAddressingModesTest, LDYLoadsImmediateValue) {
    cpu.mem_write(0xFFFC, 0x04);

    cpu.execute(0xA0);

    EXPECT_EQ(cpu.getY(), 0x04);
}

TEST_F(LDAddressingModesTest, LDYLoadsZeroPageValue) {
    cpu.mem_write(0xFFFC, 0x03);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xA4);

    EXPECT_EQ(cpu.getY(), 0x04);
}

TEST_F(LDAddressingModesTest, LDYLoadsZeroPageXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);
    cpu.mem_write(0x03, 0x04);

    cpu.execute(0xB4);

    EXPECT_EQ(cpu.getY(), 0x04);
}

TEST_F(LDAddressingModesTest, LDYLoadsAbsoluteValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2000, 0x04);

    cpu.execute(0xAC);

    EXPECT_EQ(cpu.getY(), 0x04);
}

TEST_F(LDAddressingModesTest, LDYLoadsAbsoluteXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);
    cpu.mem_write(0x2001, 0x04);

    cpu.execute(0xBC);

    EXPECT_EQ(cpu.getY(), 0x04);
}
