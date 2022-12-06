cmake_minimum_required(VERSION 3.22)
project(shell_sort_course_work C)

set(CMAKE_C_STANDARD 11)

add_executable(shell_sort_course_work main.c libUtils/myTimer.c libUtils/myTimer.h libUtils/myArray.c libUtils/myArray.h libUtils/myInput.c libUtils/myInput.h libUtils/myAlloc.c libUtils/myAlloc.h libUtils/myFiles.c libUtils/myFiles.h)
