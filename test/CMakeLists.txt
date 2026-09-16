set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 063de7e9578f82b369302001269680b4b1553359 # v1.18.0
)
set(BUILD_GMOCK OFF CACHE BOOL "Build GoogleMock" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "Use the shared runtime on Windows" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests MatrixClassTest.cpp)
target_link_libraries(matrix_tests PRIVATE MatrixClass::MatrixClass GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)
