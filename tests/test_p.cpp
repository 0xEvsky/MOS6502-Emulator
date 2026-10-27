#include <gtest/gtest.h>
#include "../include/cpu.h"

class PAddressingModesTest : public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
        }
};

TEST_F(PAddressingModesTest, PHAPushesAccumulator) {
    cpu.setA(0x42);
    cpu.setSP(0x00);

    cpu.execute(0x48);

    EXPECT_EQ(cpu.mem_read(0x0100), 0x42);
    EXPECT_EQ(cpu.getSP(), 0x01FF);
}

TEST_F(PAddressingModesTest, PHPushesStatusWithBreakFlag) {
    cpu.setC(1);
    cpu.setZ(1);
    cpu.setSP(0x00);

    cpu.execute(0x08);

    EXPECT_EQ(cpu.mem_read(0x0100), 0x33);
    EXPECT_EQ(cpu.getSP(), 0x01FF);
}

TEST_F(PAddressingModesTest, PLAPullsAccumulatorAndUpdatesZeroNegativeFlags) {
    cpu.setSP(0xFF);
    cpu.mem_write(cpu.getSP(), 0x80);

    cpu.execute(0x68);

    EXPECT_EQ(cpu.getA(), 0x80);
    EXPECT_EQ(cpu.getSP(), 0x0100);
    EXPECT_EQ(cpu.getZ(), 0);
    EXPECT_EQ(cpu.getN(), 1);
}

TEST_F(PAddressingModesTest, PLAPullsZeroAndSetsZeroFlag) {
    cpu.setSP(0xFF);
    cpu.mem_write(cpu.getSP(), 0x00);

    cpu.execute(0x68);

    EXPECT_EQ(cpu.getA(), 0x00);
    EXPECT_EQ(cpu.getZ(), 1);
    EXPECT_EQ(cpu.getN(), 0);
}

TEST_F(PAddressingModesTest, PLPPullsStatusFlags) {
    cpu.setSP(0xFF);
    cpu.mem_write(0x0100, 0xC5);

    cpu.execute(0x28);

    EXPECT_EQ(cpu.getN(), 1);
    EXPECT_EQ(cpu.getV(), 1);
    EXPECT_EQ(cpu.getD(), 0);
    EXPECT_EQ(cpu.getI(), 1);
    EXPECT_EQ(cpu.getZ(), 0);
    EXPECT_EQ(cpu.getC(), 1);
    EXPECT_EQ(cpu.getSP(), 0x0100);
}
