#include <gtest/gtest.h>
#include "../include/cpu.h"

class TAddressingModesTest : public ::testing::Test {
    protected:
        CPU cpu;

        void SetUp() override {
            cpu.reset();
            cpu.mem.reset();
        }
};

TEST_F(TAddressingModesTest, TAXTransfersAccumulatorToX) {
    cpu.setA(0x42);
    cpu.setX(0x00);

    cpu.execute(0xAA);

    EXPECT_EQ(cpu.getX(), 0x42);
    EXPECT_EQ(cpu.getA(), 0x42);
}

TEST_F(TAddressingModesTest, TAYTransfersAccumulatorToY) {
    cpu.setA(0x42);
    cpu.setY(0x00);

    cpu.execute(0xA8);

    EXPECT_EQ(cpu.getY(), 0x42);
    EXPECT_EQ(cpu.getA(), 0x42);
}

TEST_F(TAddressingModesTest, TSXTransfersStackPointerToX) {
    cpu.setSP(0x42);
    cpu.setX(0x00);

    cpu.execute(0xBA);

    EXPECT_EQ(cpu.getX(), 0x42);
    EXPECT_EQ(cpu.getSP(), 0x0142);
}

TEST_F(TAddressingModesTest, TXATransfersXToAccumulator) {
    cpu.setX(0x42);
    cpu.setA(0x00);

    cpu.execute(0x8A);

    EXPECT_EQ(cpu.getA(), 0x42);
    EXPECT_EQ(cpu.getX(), 0x42);
}

TEST_F(TAddressingModesTest, TXSTransfersXToStackPointer) {
    cpu.setX(0x42);
    cpu.setSP(0x00);

    cpu.execute(0x9A);

    EXPECT_EQ(cpu.getSP(), 0x0142);
    EXPECT_EQ(cpu.getX(), 0x42);
}

TEST_F(TAddressingModesTest, TYATransfersYToAccumulator) {
    cpu.setY(0x42);
    cpu.setA(0x00);

    cpu.execute(0x98);

    EXPECT_EQ(cpu.getA(), 0x42);
    EXPECT_EQ(cpu.getY(), 0x42);
}
