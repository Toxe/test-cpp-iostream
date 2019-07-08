cmake_minimum_required(VERSION 3.14)
project("IOStream" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(fstream_simple_write fstream_simple_write.cpp)
add_executable(streambuf_array_reader streambuf_array_reader.cpp)
add_executable(streambuf_file_reader streambuf_file_reader.cpp)
add_executable(streambuf_capitalization_writer streambuf_capitalization_writer.cpp)
add_executable(streambuf_uppercase_writer streambuf_uppercase_writer.cpp)

target_compile_features(fstream_simple_write PUBLIC cxx_std_17)
target_compile_features(streambuf_array_reader PUBLIC cxx_std_17)
target_compile_features(streambuf_file_reader PUBLIC cxx_std_17)
target_compile_features(streambuf_capitalization_writer PUBLIC cxx_std_17)
target_compile_features(streambuf_uppercase_writer PUBLIC cxx_std_17)

target_compile_options(fstream_simple_write PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast)
target_compile_options(streambuf_array_reader PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast)
target_compile_options(streambuf_file_reader PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast)
target_compile_options(streambuf_capitalization_writer PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast)
target_compile_options(streambuf_uppercase_writer PRIVATE -Wall -Wextra -Wmost -pedantic -Wconversion -Wfloat-equal -Wold-style-cast)

set_target_properties(fstream_simple_write PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(streambuf_array_reader PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(streambuf_file_reader PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(streambuf_capitalization_writer PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(streambuf_uppercase_writer PROPERTIES CXX_EXTENSIONS OFF)
