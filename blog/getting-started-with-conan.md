Getting started with Conan package manager
==========================================

I had to setup a build environment for C/C++ code that uses a library hosted on a [JFrog artifactory](https://jfrog.com/artifactory/). I realized even though I'm a self-declared C++ expert, I didn't know about any package manager for C/C++ libraries. 🤦🏽‍♂️ Thus, I discovered the [Conan package manager](https://conan.io/), and also found an official [webinar](https://www.youtube.com/watch?v=xBLjXdyh3zs&t=2561s) where my Conan learning journey began.

I decided to with the [Getting Started](https://docs.conan.io/en/latest/getting_started.html) document because ... that's what getting started means. 😐 For (my) future reference, I note the steps here. I did this setup on Linux OS.  

* **Install `pip`**: Conan [recommends](https://docs.conan.io/en/latest/installation.html) to use `pip` for installation, so `pip` needs to be installed first.

  ```bash
  sudo apt install python-pip
  ```

* **Install `conan`**: Now install conan using pip.

  ```bash
  pip install conan
  ```

* **Install `cmake`**: Conan works with any build system. The example uses the most popular `cmake` build system. I want to use the same anyway as I don't know it very well and want to learn. Hence, now is as good a time as any other to install it:

  ```bash
  sudo apt install cmake
  ```

* **Create the example source code**: The example code from conan uses the `poco` library.

* **Search for the `poco` package in conan-center**: The document asks to run the following command to search for the `poco` package:

  ```bash
  conan search poco --remote=conan-center
  Existing package recipes:

  poco/1.8.1
  poco/1.9.3
  poco/1.9.4
  poco/1.10.0
  poco/1.10.1
  ```

* **Create the `conanfile.txt`**: Place the given example file in the base directory (where the source code is placed.)

* **Use C++11 ABI for libcxx**: Since I intend to use `C++11` and later versions for my development, I do not need the backward compatibility with older versions. Hence, run the following commands:

  ```bash
  profile new default --detect  # Generates default profile detecting GCC and sets old ABI
  conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
  ```

* **Install dependencies and configure the build system**: Installing the dependencies with conan is quite simple. As with the `cmake` approach, create a `build` directory and then run the installation inside it. Thus, a clean installation becomes a matter of deleting the `build` directory and starting over. 😇

  ```bash
  mkdir build && cd build
  conan install ..
  ```

* **Include the generated dependency info into `CMakeLists.txt`**: The `CMakeLists.txt` is considerably simpilified with conan. Conan generates the dependency information and we just have to include the `conanbuildinfo.cmake` into the `CMakeLists.txt`, which is a lot easier than fiddling with various `cmake` commands to specify the include paths, etc. The example `CMakeLists.txt` file is also provided in the document.

* **Build and execute**: As usual, do the `cmake` build and execute the compiled executable:

  ```bash
  cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
  cmake --build .
  ./bin/md5
  ```
