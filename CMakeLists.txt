cmake_minimum_required(VERSION 3.25)
project(AVLTrees)

set(CMAKE_CXX_STANDARD 14)

#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)

add_executable(Main Project1/src/main.cpp Project1/src/AVL.h Project1/src/AVL.h Project1/src/AVL.h)

add_executable(Tests Project1/test-unit/test.cpp)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)