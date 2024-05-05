cmake_minimum_required(VERSION 3.17)

project(interpreter_book)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=stdlibc++")

add_library(token src/token/token.cpp)
target_link_libraries(token)
add_library(lexer src/lexer/lexer.cpp)
target_link_libraries(lexer)

find_package(GTest)
if (GTEST_FOUND)
  enable_testing()
  include_directories(${GTEST_INCLUDE_DIRS})

  add_executable(LexerTests tests/LexerTests.cpp)
  target_link_libraries(LexerTests ${GTEST_BOTH_LIBRARIES} token lexer pthread)
  GTEST_DISCOVER_TESTS(LexerTests)
endif()

# add_executable(2015_01 src/2015/day_01.cpp)
# target_link_libraries(2015_01 input)
