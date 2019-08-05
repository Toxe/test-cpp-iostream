cmake_minimum_required(VERSION 3.14)
project("IOStream" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ALL_TARGETS
    fstream_simple_write
    streambuf_array_reader
    streambuf_file_reader
    streambuf_capitalization_writer
    streambuf_uppercase_writer
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

foreach(target ${ALL_TARGETS})
    add_executable(${target} ${target}.cpp)
    target_compile_features(${target} PUBLIC cxx_std_17)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast -fcolor-diagnostics)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${target} PRIVATE /W4)
    endif()
endforeach()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(streambuf_file_reader PRIVATE /wd4996)
endif()
