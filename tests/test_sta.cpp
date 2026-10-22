#include <gtest/gtest.h>
#include "../include/cpu.h"

class STAAddressingModesTest : public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
            cpu.setA(0x42);
        }
};

TEST_F(STAAddressingModesTest, StoresZeroPageValue) {
    cpu.mem_write(0xFFFC, 0x03);

    cpu.execute(0x85);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAAddressingModesTest, StoresZeroPageXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x02);

    cpu.execute(0x95);

    EXPECT_EQ(cpu.mem_read(0x03), 0x42);
}

TEST_F(STAAddressingModesTest, StoresAbsoluteValue) {
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x8D);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}

TEST_F(STAAddressingModesTest, StoresAbsoluteXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x9D);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}

TEST_F(STAAddressingModesTest, StoresAbsoluteYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0x00);
    cpu.mem_write(0xFFFD, 0x20);

    cpu.execute(0x99);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}

TEST_F(STAAddressingModesTest, StoresIndirectPreXValue) {
    cpu.setX(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0x00, 0x00);
    cpu.mem_write(0x01, 0x20);

    cpu.execute(0x81);

    EXPECT_EQ(cpu.mem_read(0x2000), 0x42);
}

TEST_F(STAAddressingModesTest, StoresIndirectPostYValue) {
    cpu.setY(1);
    cpu.mem_write(0xFFFC, 0xFF);
    cpu.mem_write(0xFF, 0x00);
    cpu.mem_write(0x00, 0x20);

    cpu.execute(0x91);

    EXPECT_EQ(cpu.mem_read(0x2001), 0x42);
}
