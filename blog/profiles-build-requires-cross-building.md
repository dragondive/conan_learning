Profiles, `build_requires` and cross-building
=============================================

Conan's profiles feature offers an easy way to run conan commands with various configurations. The settings, options, environment variables and build requirements can be stored to a file called the profile. One or more Conan profiles can be passed to several Conan commands to run them with the specified configurations.

The command line arguments specified in [creating a Conan package from pre-built binaries](working-with-nonconan-packages.md) can be replaced with profiles. The example profiles are available in the sources, for [Windows](../sources/nonconan/legacypkg/windows_vs.profile) and [Linux](../sources/nonconan/legacypkg/linux_gcc.profile). The `export-pkg` command can be run with profiles as below:

```bash
$ conan export-pkg . random/0.1@aravind/testing --profile-windows_vs.profile
$ conan export-pkg . random/0.1@aravind/testing --profile=linux_gcc.profile
```

Specifying build requirements with `build_requires`
--------------------------------------------------

It is useful to differentiate source code dependencies from dependencies required only for building or testing the package. The latter type of dependencies need not cascade to downstream consumers of the package. Such packages can be specified as `build_requires` dependencies instead of `requires` dependencies.

In the [example](publish-conan-package-to-artifactory.md), when `gtest` is specified as a `requires` dependency in `conan_gtest` package, it gets downloaded when the `conan_gtest` package is consumed as a dependency. However, the `gtest` package is only needed by the `conan_gtest` package, and not in the consuming context. By specifying it as a `build_requires` dependency instead, it is not cascaded to the downstream consumers.

Another use of the `build_requires` is to build the package with various versions of the build toolchain. The example [profile](../sources/conan_gtest/cmake_3.19.2.profile) specifies a version of `cmake`. When this profile is passed to a command, Conan will download the package and use it for the build. It can be combined with any other profile that specifies the settings, as with the `default` profile below:

```bash
$ conan create . conan_gtest/0.1@aravind/testing --profile=default --profile=cmake_3.19.2.profile
```

A "hack" to quickly verify the specified `cmake` version is used in the build is to specify a cmake version lower than the `cmake_minimum_required` specified in the `CMakeLists.txt`.

Cross-building using Conan
--------------------------

Cross-building means generating the binaries for a configuration different from the one where the build process runs. This is used when it is impractical to run the build process directly on the target platform due to memory or processor speed limitations. A common example of such a target platform is embedded systems with less memory and slower processors (in comparison to general purpose workstation).

Cross-building with Conan is just like a "normal" build. Provide the cross-build toolchains and configurations in a profile, and run the usual conan commands. Here, I take the [example profile](../sources/crossbuild/conan_gtest/linux_to_win64.profile) directly from the [Conan documentation](https://docs.conan.io/en/latest/systems_cross_building/cross_building.html) to perform a Linux to Windows cross-build.

```bash
$ conan create . random/0.1@aravind/testing --profile=linux_to_win64.profile
```

The complete console log is available [here](../logs/conan-crossbuild-console-output.txt).
