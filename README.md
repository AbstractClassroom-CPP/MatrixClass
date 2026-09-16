# MatrixClass

Two simple matrix classes that other C++ projects can use as one CMake dependency.
Version `2.0.0` provides `IntegerMatrixClass` for `int` values and `DoubleMatrixClass`
for approximate values stored as `double`.

We copied the original implementation, changed the class names, and changed the
value type in the double implementation. Neither matrix class is a template.

| Library version | Classes | Example consumer |
| --- | --- | --- |
| [1.0.0](https://github.com/AbstractClassroom-CPP/MatrixClass/tree/1.0.0) | `MatrixClass` with `int` values | NSBE-Demo `0.1.0` |
| [2.0.0](https://github.com/AbstractClassroom-CPP/MatrixClass/tree/2.0.0) | `IntegerMatrixClass` and `DoubleMatrixClass` | NSBE-Demo `0.2.0` |

The original class is preserved in tag `1.0.0`. Version `2.0.0` replaces
`MatrixClass.h` and the `MatrixClass` C++ class with the two named classes below.
The CMake target is still `MatrixClass::MatrixClass`.

```text
MatrixClass/
├── CMakeLists.txt
├── include/
│   ├── IntegerMatrixClass.h
│   └── DoubleMatrixClass.h
├── src/
│   ├── IntegerMatrixClass.cpp
│   └── DoubleMatrixClass.cpp
├── example/
│   └── main.cpp
├── README.md
└── .gitignore
```

## Use the classes

```cpp
#include "IntegerMatrixClass.h"
#include "DoubleMatrixClass.h"

#include <iostream>

int main() {
    IntegerMatrixClass a(2, 3); // Rows, columns; every entry starts at zero.
    IntegerMatrixClass b(2, 3);
    a.set(0, 1, 4);     // Row and column indices start at zero.
    b.set(0, 1, 2);
    IntegerMatrixClass c = a.add(b);
    int value = c.get(0, 1); // 6
    // c.numRows() returns 2; c.numCols() returns 3.

    DoubleMatrixClass x(2, 3);
    DoubleMatrixClass y(2, 3);
    x.set(0, 1, 4.5);
    y.set(0, 1, 1.25);
    DoubleMatrixClass z = x.add(y);
    double approximateValue = z.get(0, 1); // 5.75

    std::cout << value << ' ' << approximateValue << '\n';
    return 0;
}
```

Each class adds another matrix of its own type. Addition returns a new matrix and
leaves both inputs unchanged. Dimensions and indices remain `int` in both classes.
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
    GIT_TAG 2.0.0
)
FetchContent_MakeAvailable(matrixclass)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE MatrixClass::MatrixClass)
```

CMake fetches the source during configuration and builds the library with your program.
The target supplies the header directory and the requirement for at least C++11.
There is no manual source copying or separate library installation.
The library's example is built only when configuring the MatrixClass repository directly.

`GIT_TAG 2.0.0` selects the release containing both classes. Use `GIT_TAG 1.0.0`
with the original `MatrixClass.h` interface when building an older application.
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
Integer matrix
2 rows, 2 cols
6 8
10 12

Double matrix
2 rows, 2 cols
1.75 3
4.25 5.5
```
