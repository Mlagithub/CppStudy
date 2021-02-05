
cmake_minimum_required(VERSION 3.17)

project(TemplateTest)

set(SOURCE_FILES 
    test_main.cpp
    test_typelist.cpp
)

SET (GTEST_LDFLAGS "-L$ENV{GTEST_ROOT}/lib -lgtest -pthread")
SET (GTEST_CFLAGS "-I$ENV{GTEST_ROOT}/include")

include_directories(../TypeList)

ADD_EXECUTABLE(runTests.exe ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(runTests.exe ${GTEST_LDFLAGS})
TARGET_COMPILE_OPTIONS(runTests.exe PUBLIC ${GTEST_CFLAGS})
INSTALL(TARGETS runTests.exe DESTINATION ../bin)
