# MatrixClass

A simple integer matrix class that other C++ projects can use as a CMake dependency.
Version `1.0.0` provides the original `MatrixClass` with integer values.

```text
MatrixClass/
├── CMakeLists.txt
├── include/
│   └── MatrixClass.h
├── src/
│   └── MatrixClass.cpp
├── example/
│   └── main.cpp
├── README.md
└── .gitignore
```

## Use the class

```cpp
#include "MatrixClass.h"

int main() {
    MatrixClass a(2, 3); // Rows, columns; every entry starts at zero.
    MatrixClass b(2, 3);
    a.set(0, 1, 4);     // Row and column indices start at zero.
    b.set(0, 1, 2);
    MatrixClass c = a.add(b);
    int value = c.get(0, 1); // 6
    // c.numRows() returns 2; c.numCols() returns 3.
    return value == 6 ? 0 : 1;
}
```

Values are `int`. Addition returns a new matrix and leaves both inputs unchanged.
Adding different dimensions throws `std::invalid_argument`; an invalid index throws `std::out_of_range`.

## Add it to another CMake project

With Git, CMake 3.14 or newer, and a C++ compiler installed, put this in the consuming project's `CMakeLists.txt` alongside its `main.cpp`:

```cmake
cmake_minimum_required(VERSION 3.14)
project(MyMatrixApp LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    matrixclass
    GIT_REPOSITORY https://github.com/AbstractClassroom-CPP/MatrixClass.git
    GIT_TAG 1.0.0
)
FetchContent_MakeAvailable(matrixclass)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE MatrixClass::MatrixClass)
```

CMake fetches the source during configuration and builds the library with your program.
The target supplies the header directory and the requirement for at least C++11.
There is no manual source copying or separate library installation.
The library's example is built only when configuring the MatrixClass repository directly.

`GIT_TAG 1.0.0` selects the original integer-only release.
[NSBE-Demo](https://github.com/AbstractClassroom-CPP/NSBE-Demo) is a complete consuming project.

## Build this repository's example

Run these commands from the `MatrixClass` directory.

### Mac

Install CMake and Apple's command-line tools (`xcode-select --install`) if needed.

```bash
cmake -S . -B build -G "Unix Makefiles"
cmake --build build
./build/matrix_example
```

### Windows (Git Bash)

Install CMake, Ninja, and a MinGW-w64 C++ compiler. Put their executable directories on your Windows `PATH` and reopen Git Bash.
Check that `cmake --version`, `ninja --version`, and `g++ --version` work.

```bash
cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
cmake --build build
./build/matrix_example.exe
```

Expected output:

```text
2 rows, 2 cols
6 8
10 12
```
