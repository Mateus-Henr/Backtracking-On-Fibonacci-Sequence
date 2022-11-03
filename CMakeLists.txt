cmake_minimum_required(VERSION 3.22)

project(Backtracking_On_Fibonacci_Sequence C)

set(CMAKE_C_STANDARD 11)

add_executable(Backtracking_On_Fibonacci_Sequence
        src/file.c src/main.c src/fibonacci.c src/fibonacci.h src/matrix.c src/matrix.h src/file.h)

target_link_libraries(Backtracking_On_Fibonacci_Sequence m)