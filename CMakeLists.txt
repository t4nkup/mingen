cmake_minimum_required(VERSION 3.15)
project(MyProgram C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(mingen ${SOURCES})

target_include_directories(mingen PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/lib"
)

target_link_libraries(mingen PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/raylib/windows/libraylib.a"
    opengl32
    gdi32
    winmm
)

set_target_properties(mingen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/windows/"
)

if(MINGW)
    target_compile_options(mingen PRIVATE -Wall -O2)
endif()
