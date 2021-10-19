# conan_learning

This repository contains example source codes and notes I wrote while learning the [Conan package manager for C/C++](https://conan.io/).

* [Getting started with Conan package manager](blog/getting-started-with-conan.md)
* [Setting up Google Test with Conan package manager](blog/setup-gtest-with-conan.md)
* [Creating and testing a `conan` package](blog/create-and-test-conan-package.md)
* [Publishing `conan` package to artifactory](blog/publish-conan-package-to-artifactory.md)
* [Working with non-Conan packages](blog/create-and-test-conan-package.md)
* [Profiles, `build_requires` and cross-building](blog/profiles-build-requires-cross-building.md)

@startuml
    title conan learning usecases

    actor "Developer 1" as Dev1
    actor "Developer 2" as Dev2
    actor "Developer 3" as Dev3
    actor "Developer 4" as Dev4

    package conan_gtest {
        usecase "build custom package" as Build
        usecase "run unit tests" as Test
        usecase "create new package" as Package
    }

    package conan_gtest_use {
        usecase "include package" as Include
    }

    package nonconan {
        usecase "adapt to conan package" as Adapt
    }

    package crossbuild {
        usecase "perform crossbuild" as Crossbuild
    }

    Dev1 --> Build
    Dev1 --> Test
    Dev1 --> Package

    Dev2 --> Include

    Dev3 --> Adapt

    Dev4 --> Crossbuild
@enduml
