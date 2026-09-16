cmake_minimum_required(VERSION 3.14)
project(MatrixClass LANGUAGES CXX)

add_library(MatrixClass STATIC src/MatrixClass.cpp)
add_library(MatrixClass::MatrixClass ALIAS MatrixClass)

target_include_directories(MatrixClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(MatrixClass PUBLIC cxx_std_11)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    add_executable(matrix_example example/main.cpp)
    target_link_libraries(matrix_example PRIVATE MatrixClass::MatrixClass)
endif()
