cmake_minimum_required(VERSION 3.13)
project(REVERSI C)

set(CMAKE_C_STANDARD 99)

add_executable(REVERSI main.c multi.c multi.h executar.c executar.h stack.c stack.h botz.c botz.h)