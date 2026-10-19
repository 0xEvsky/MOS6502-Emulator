#include <gtest/gtest.h>
#include "../include/memory.h"

class MemoryTest : public ::testing::Test {
    protected:
        Mem mem;
        void SetUp() override {mem.reset();}
};

TEST_F(MemoryTest, StoresAndReadsBytes){
    mem.write(0x1234, 0xAB);
    EXPECT_EQ(mem.read(0x1234), 0xAB);
}

TEST_F(MemoryTest, StoresAndResets) {
    mem.write(0x1234, 0xAB);
    mem.reset();
    EXPECT_EQ(mem.read(0x1234), 0x00);
}

TEST_F(MemoryTest, LoadsAndReads) {
    Byte test_program_1[] = {0xDE, 0xAD, 0xBE, 0xEF};
    mem.load(0xFFFC, test_program_1, 4);
    EXPECT_EQ(mem.read(0xFFFC), 0xDE);
    EXPECT_EQ(mem.read(0xFFFD), 0xAD);
    EXPECT_EQ(mem.read(0xFFFE), 0xBE);
    EXPECT_EQ(mem.read(0xFFFF), 0xEF);

    // Truncate the program to fit within the memory size
    Byte test_program_2[] = {0x00, 0x01, 0x02, 0x03, 0x04};
    mem.load(0xFFFC, test_program_2, 5);
    EXPECT_EQ(mem.read(0xFFFC), 0x00);
    EXPECT_EQ(mem.read(0xFFFD), 0x01);
    EXPECT_EQ(mem.read(0xFFFE), 0x02);
    EXPECT_EQ(mem.read(0xFFFF), 0x03);
    EXPECT_EQ(mem.read(0x0000), 0x04);
}