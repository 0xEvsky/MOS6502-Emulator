cmake_minimum_required(VERSION 3.14)
project(emu6502 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Emulator code, without main()
add_library(core
    src/memory.cpp
    src/cpu.cpp
    src/instructions.cpp
)
target_include_directories(core PUBLIC include)

# The emulator program
add_executable(emu src/6502.cpp)
target_link_libraries(emu PRIVATE core)

# GoogleTest, downloaded at configure time
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# The test program
add_executable(tests
    tests/test_memory.cpp
    tests/test_cpu.cpp
    tests/test_ld.cpp
    tests/test_st.cpp
    tests/test_t.cpp
    tests/test_p.cpp
)
target_link_libraries(tests PRIVATE core GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)