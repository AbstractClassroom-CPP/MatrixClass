# MatrixClass

A simple matrix class template that other C++ projects can use as a CMake dependency.
Version `3.0.0` provides `MatrixClass<int>` and `MatrixClass<double>` from one implementation.
The template parameter `T` selects the value type used by storage, `get()`, and `set()`.

| Library version | Classes | Example consumer |
| --- | --- | --- |
| [1.0.0](https://github.com/AbstractClassroom-CPP/MatrixClass/tree/1.0.0) | `MatrixClass` with `int` values | NSBE-Demo `0.1.0` |
| [2.0.0](https://github.com/AbstractClassroom-CPP/MatrixClass/tree/2.0.0) | `IntegerMatrixClass` and `DoubleMatrixClass` | NSBE-Demo `0.2.0` |
| [3.0.0](https://github.com/AbstractClassroom-CPP/MatrixClass/tree/3.0.0) | `MatrixClass<int>` and `MatrixClass<double>` | NSBE-Demo `0.3.0` |

The earlier APIs remain available in tags `1.0.0` and `2.0.0`. Version `3.0.0`
replaces the two separately named classes with `MatrixClass<T>` in `MatrixClass.h`.
The CMake target remains `MatrixClass::MatrixClass`.

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

## Use the template

```cpp
#include "MatrixClass.h"

#include <iostream>

int main() {
    MatrixClass<int> a(2, 3); // Rows, columns; every entry starts at zero.
    MatrixClass<int> b(2, 3);
    a.set(0, 1, 4);     // Row and column indices start at zero.
    b.set(0, 1, 2);
    MatrixClass<int> c = a.add(b);
    int value = c.get(0, 1); // 6
    // c.numRows() returns 2; c.numCols() returns 3.

    MatrixClass<double> x(2, 3);
    MatrixClass<double> y(2, 3);
    x.set(0, 1, 4.5);
    y.set(0, 1, 1.25);
    MatrixClass<double> z = x.add(y);
    double approximateValue = z.get(0, 1); // 5.75

    std::cout << value << ' ' << approximateValue << '\n';
    return 0;
}
```

Addition takes another matrix with the same value type, returns a new matrix, and
leaves both inputs unchanged. Dimensions and indices remain `int`.
Adding different dimensions throws `std::invalid_argument`; an invalid index throws `std::out_of_range`.

This release supports `int` and `double`. `src/MatrixClass.cpp` explicitly
instantiates both types from the same template definitions, so those definitions
can stay in the source file. Include the header and link the library to use either type.

## Add it to another CMake project

With Git, CMake 3.14 or newer, and a C++ compiler installed, put this in the consuming project's `CMakeLists.txt` alongside its `main.cpp`:

```cmake
cmake_minimum_required(VERSION 3.14)
project(MyMatrixApp LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    matrixclass
    GIT_REPOSITORY https://github.com/AbstractClassroom-CPP/MatrixClass.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(matrixclass)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE MatrixClass::MatrixClass)
```

CMake fetches the source during configuration and builds the library with your program.
The target supplies the header directory and the requirement for at least C++11.
There is no manual source copying or separate library installation.
The library's example is built only when configuring the MatrixClass repository directly.

`GIT_TAG 3.0.0` selects the template release. Older applications can still select
`1.0.0` or `2.0.0` to use their corresponding interfaces.
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
