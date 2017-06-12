cmake_minimum_required(VERSION 3.7)
project(Wet_Part)

set(CMAKE_C_STANDARD 99)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic-errors -Werror -DNDEBUG")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES mtm_ex3.h test_utilities.h set.h list.h utils.c utils.h
         room.c room.h company.c company.h escaper.c escaper.h reservation.c
        reservation.h faculty.c faculty.h escape_technion.c escape_technion.h
        escape_technion_test.c)
add_executable(Wet_Part ${SOURCE_FILES})

target_link_libraries(Wet_Part ${CMAKE_SOURCE_DIR}/libmtm.a)