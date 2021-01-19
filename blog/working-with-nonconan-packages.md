Working with non-Conan packages
===============================

Well-architected large projects are organized into multiple components. These components have clearly defined dependencies on other project components and on external libraries. Changing the process in such projects is best done gradually because any "big bang" changes are difficult to execute correctly.

Adopting Conan in large projects would involve gradually extending it to a few components at a time. Some components and external dependencies may eventually not adopt Conan at all. Hence, working with non-Conan packages becomes an important requirement.

`export-pkg` command
--------------------

In the Conan recipe, only Conan packages can be specified as dependencies. Conan provides a command `export-pkg` to repackage pre-built binaries (that is, non-Conan packages) as Conan packages. The command takes a package recipe that specifies how to package the pre-built binaries into the Conan package. These repackaged Conan packages can then be specified as dependencies like any other Conan-built packages.

non-Conan package example
-------------------------

The source code used to create the non-Conan package in this example is available [here](../sources/nonconan/random). Using cmake (that is, without Conan), I built this code into shared libraries on both Windows and Linux. I also created the documentation using doxygen. I packaged all these artifacts into a non-Conan package, available [here](../sources/nonconan/legacypkg), with the following directory structure:

```
legacypkg/
├── binary_linux
│   └── librandom.so
├── binary_windows
│   ├── random.dll
│   ├── random.exp
│   └── random.lib
├── conanfile.py
├── doc
│   ├── html
│   └── latex
├── header
│   └── random.h
```

Recipe for repackaging into Conan package
-----------------------------------------

The template recipe for repackaging is created with the following command:

    conan new random/0.1@aravind/testing --bare

The recipe doesn't include a `build()` method because the package is pre-built. The repackaging is defined in the `package()` method. In this example, I create the package for only two configurations, but it can be extended further.

```py
def package(self):
    if self.settings.os == "Linux" and self.settings.compiler == "gcc" and self.settings.build_type == "Release" and self.settings.arch == "x86_64" and self.options.shared == True:
        self.copy("librandom.so", src="binary_linux", dst="lib", keep_path=False)
    elif self.settings.os == "Windows" and self.settings.compiler == "Visual Studio" and self.settings.build_type == "Release" and self.settings.arch == "x86_64" and self.options.shared == True:
        self.copy("random.*", src="binary_windows", dst="lib", keep_path=False)
    else:
        print("[Error] Unsupported settings for exporting the package.")
        return

    self.copy("*", src="doc", dst="documents", keep_path=True)
    self.copy("*.h", src="header", dst="include", keep_path=True)
```

Calling the `export-pkg` command
--------------------------------

As all the required artifacts are available, the `export-pkg` command can be called multiple times on the same machine for various configurations. In all cases, additional required settings (for example, `compiler.version`) not specified in the `package()` method need to be specified.

* **Windows**:

      aravind@dragondive:~/conan_learning/nonconan/legacypkg$ conan export-pkg . random/0.1@aravind/testing -s os=Windows -s compiler="Visual Studio" -s build_type=Release -s arch=x86_64 -s compiler.version=14 -o random:shared=True

  The complete console output is [here](../logs/conan-export-pkg-windows-console-output.txt).

* **Linux**:

      aravind@dragondive:~/conan_learning/nonconan/legacypkg$ conan export-pkg . random/0.1@aravind/testing -s os=Linux -s compiler=gcc -s build_type=Release -s arch=x86_64 -s compiler.version=9 -s compiler.libcxx=libstdc++11 -o random:shared=True

  The complete console output is [here](../logs/conan-export-pkg-linux-console-output.txt).

Using the package
-----------------

The package can be uploaded to Artifactory as described [here](publish-conan-package-to-artifactory.md) and specified as a dependency in the package recipe. The example source code is available [here](../sources/nonconan/random_use).

```
[requires]
random/0.1@aravind/testing

[generators]
cmake

[options]
random:shared=True

[imports]
lib, *.dll -> ./bin
```

Conan enables dynamic linking of the shared library at runtime in the following ways. On Linux with `cmake`, Conan invokes `find_library()` to make the `.so` file in the local cache visible to the runtime environment. On Windows, the `[imports]` declaration in the recipe copies the `.dll` file to the `bin` folder where the executable is created, which avoids having to modify system variables.

Build and execution of the consuming package
--------------------------------------------

On Linux, the consuming package can be built as described [here](getting-started-with-conan.md). On Windows, the `cmake` calls take some additional arguments to explicitly override the default architecture and build type:

```bash
λ cmake .. -A x64
λ cmake --build . --config Release
```

In both cases, running the executable gives the following result:

    IEEE-vetted random number = 4
