Creating and testing a `conan` package
======================================

Following the [simple example to use a Conan package](setup-gtest-with-conan.md), the next step is to learn how to create my own package and use it.

`conanfile.py`
-------------

Conan packages are created and published using python code specified in a file named `conanfile.py`. The `conanfile.txt` used previously is a simplified form of `conanfile.py`. `conanfile.py` can be used to both consume and publish a package.

Using the `conan new` command
-----------------------------

While the `conanfile.py` can be written manually, the `conan new` command makes it more convenient by generating a template.

    conan new -s -t conan_gtest/0.1@aravind/testing

The `-t` flag also creates a `test_package` directory, which can be used to test the package.

Note that this command overwrites any files in the same directory with the same name. Hence, it is recommended to run it in an empty directory, then copy the `conanfile.py` and `test_package` into the directory where the source is present.

Updating the auto-generated files
---------------------------------

The generated `conanfile.py` then needs to be modified as per the `conan_gtest` package. In particular, the attribute `exports_sources` and the `source_folder` in `cmake.configure()` call need to be modified, as they differ from conan's auto-generated hello example. The other package dependencies should also be specified with the `requires` attribute. The updated file is [here](../sources/conan_gtest/conanfile.py).

Then the `example.cpp` file in `test_package` should be updated to test the `conan_gtest` package. The updated file is [here](../sources/conan_gtest/test_package/example.cpp).

Using the `conan create` command
--------------------------------

We are now ready to create the package. The `conan create` command takes care of everything.

    conan create . conan_gtest/0.1@aravind/testing

This performs the following steps:

1. Export the sources as specified in the `package()` method in `conanfile.py`.
2. Download the specified dependencies from the remote server, if not found in local cache.
3. Build the local packages from sources.
4. Execute the package tests if a `test_package` directory is present.

The complete console output of the `conan create` command is [here](../logs/conan-create-console-output.txt).

The `conan_gtest` package is now available in the local cache:

    aravind@dragondive:~/conan_learning/conan_gtest$ conan search
    Existing package recipes:

    conan_gtest/0.1@aravind/testing
    gtest/1.10.0

Using the package
-----------------

The package `conan_gtest` can now be used in C++ code. Specify it in the `[requires]` section of `conanfile.txt` then build as usual with `conan install` and `cmake` calls. The example code which uses the `conan_gtest` package is [here](../sources/conan_gtest_use).

    aravind@dragondive:~/conan_learning/conan_gtest_use/build$ ./bin/conan_gtest_use
    hello 42
