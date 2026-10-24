#include <gtest/gtest.h>
#include "../include/cpu.h"

class STAddressingModesTest : public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
        }
};

TEST_F(STAddressingModesTest, STAStoresZeroPageValue) {
    cpu.setA(0x42);
    cpu.mem_write(0xFFFC, 0x03);

    cpu.execute(0x85);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresZeroPageXValue) {
    cpu.setA(0x42);
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);

    cpu.execute(0x95);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresAbsoluteValue) {
    cpu.setA(0x42);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x8D);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresAbsoluteXValue) {
    cpu.setA(0x42);
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x9D);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresAbsoluteYValue) {
    cpu.setA(0x42);
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x99);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresIndirectPreXValue) {
    cpu.setA(0x42);
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0x00, 0x00);
    cpu.mem_write(0x01, 0x20);

    cpu.execute(0x81);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}

TEST_F(STAddressingModesTest, STAStoresIndirectPostYValue) {
    cpu.setA(0x42);
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0xFF, 0x00);
    cpu.mem_write(0x00, 0x20);

    cpu.execute(0x91);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}

TEST_F(STAddressingModesTest, STXStoresZeroPageValue) {
    cpu.setX(0x42);
    cpu.mem_write(0xFFFC, 0x03);

    cpu.execute(0x86);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STXStoresZeroPageYValue) {
    cpu.setX(0x42);
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x02);

    cpu.execute(0x96);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STXStoresAbsoluteValue) {
    cpu.setX(0x42);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x8E);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}

TEST_F(STAddressingModesTest, STYStoresZeroPageValue) {
    cpu.setY(0x42);
    cpu.mem_write(0xFFFC, 0x03);

    cpu.execute(0x84);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STYStoresZeroPageXValue) {
    cpu.setY(0x42);
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);

    cpu.execute(0x94);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAddressingModesTest, STYStoresAbsoluteValue) {
    cpu.setY(0x42);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x8C);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}
