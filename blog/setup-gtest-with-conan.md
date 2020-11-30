Setting up Google Test with Conan package manager
=================================================

I want to setup the Google Test framework from scratch. Using the conan package manager greatly simplifies setting up the build system.

cmake-based build setup
-----------------------

As I did not know about Conan when I started this setup, my first attempt was by using *only* cmake. This was a tedious exercise, especially as I did not know cmake very well. I finally got it running  after spending two days reading cmake documentation, google test readme files, and several failed attempts. This would be even more tedious if google test didn't helpfully provide a cmake file to download its binaries.

Prototype tests for the build setup
-----------------------------------

For this build setup, I use some simple functions and the corresponding google tests. The source code is available [here](../conan_learning/conan_gtest).  The prototype has the below source files:

```
conan_learning/
├── CMakeLists.txt
├── conanfile.txt
└── src
    ├── CMakeLists.txt
    ├── main.cpp
    ├── sample.cpp
    ├── sample.h
    └── test
        ├── CMakeLists.txt
        ├── gtest_main.cpp
        └── sample_test.cpp
```

The source code to be tested consists of two simple functions defined in `sample.cpp`:

```cpp
#include "sample.h"

int get_42()
{
    return 42;
}

std::string get_hello()
{
    return "hello";
}
```

The corresponding google tests are defined in `sample_test.cpp`:

```cpp
#include "gtest/gtest.h"
#include "sample.h"

TEST(SampleTest, get_42)
{
    EXPECT_EQ(42, get_42());
}

TEST(SampleTest, get_hello)
{
    EXPECT_EQ("hello", get_hello());
}
```

The file `gtest_main.cpp` is google test's boilerplate:

```cpp
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
```


The file `main.cpp` includes a `main()` function to enable creating a standalone application from the source code.

```cpp
#include <iostream>
#include "sample.h"

int main()
{
    std::cout << get_hello() << " " << get_42() << std::endl;
}
```

Configuring `cmake` and `conan`
-------------------------------

In a [previous post](getting-started-with-conan.md), I set up the conan package manager for a simple example. Now I have to adapt it for this slightly more complicated example.

* **Search for the `gtest` package**:

  ```bash
  conan search gtest --remote=conan-center
  Existing package recipes:

  gtest/1.7.0@bincrafters/stable
  gtest/1.8.0@bincrafters/stable
  gtest/1.8.1
  gtest/1.8.1@bincrafters/stable
  gtest/1.10.0
  ```

* **Specify the dependency in `conanfile.txt`**:

  ```bash
  [requires]
  gtest/1.10.0

  [generators]
  cmake
  ```      

* **Configure `cmake` in `CMakeLists.txt`**: Unlike the simple example, the protoype has multiple source files in different directories. Hence, we need multiple `CMakeLists.txt` files to organize the build configuration. There shall be a main `CMakeLists.txt` in the base directory, and one each in the source directory and the test directory.

  * `CMakeLists.txt` in `src`: The below configuration enables running the source as a standalone application and also creates a static library which shall be linked into the test executable later.

    ```cmake
    set(BINARY ${CMAKE_PROJECT_NAME})

    set(SOURCES
        main.cpp
        sample.h
        sample.cpp
    )

    add_executable(${BINARY}_run ${SOURCES})
    add_library(${BINARY} STATIC ${SOURCES})
    ```

  * `CMakeLists.txt` in `src/test`: The below configuration builds the test executable. Note the `target_link_libraries()` call where conan abstracts out the `gtest` dependency and its transitive dependencies.

    ```cmake
    set(BINARY ${CMAKE_PROJECT_NAME}_test)

    set(TEST_SOURCES
        gtest_main.cpp
        sample_test.cpp
    )

    add_executable(${BINARY} ${TEST_SOURCES})
    add_test(NAME ${BINARY} COMMAND ${BINARY})

    target_link_libraries(${BINARY} PUBLIC conan_gtest ${CONAN_LIBS})
    ```

  * `CMakeLists.txt` in the base directory: The main `CMakeLists.txt` is now much more simpilified and readable than in case of the cmake-only setup.

    ```cmake
    cmake_minimum_required(VERSION 3.18.1)
    project(conan_gtest)

    add_definitions("-std=c++14")

    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    include_directories(src)
    add_subdirectory(src)
    add_subdirectory(src/test)
    ```

Build and execute
-----------------

Finally build the tests and execute them.

```bash
mkdir build && cd build
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .

./bin/conan-gtest_test
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from SampleTest
[ RUN      ] SampleTest.get_42
[       OK ] SampleTest.get_42 (0 ms)
[ RUN      ] SampleTest.get_hello
[       OK ] SampleTest.get_hello (0 ms)
[----------] 2 tests from SampleTest (0 ms total)
[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 2 tests.
```

The standalone application can also be executed similarly.

```bash
./bin/conan-gtest_run
hello 42
```    
