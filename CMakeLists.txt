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

foreach(target ${ALL_TARGETS})
    add_executable(${target} ${target}.cpp)
    target_compile_features(${target} PUBLIC cxx_std_17)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast -fcolor-diagnostics)
    set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)
endforeach()
