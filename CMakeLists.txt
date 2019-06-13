cmake_minimum_required(VERSION 3.14)
project("IOStream" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(fstream_simple_write fstream_simple_write.cpp)

target_compile_features(fstream_simple_write PUBLIC cxx_std_17)

set_target_properties(fstream_simple_write PROPERTIES CXX_EXTENSIONS OFF)
