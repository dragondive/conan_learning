from conans import ConanFile, CMake


class ConanGtestConan(ConanFile):
    name = "conan_gtest"
    version = "0.1"
    author = "Aravind Pai dragondive@outlook.in"
    url = "https://github.com/dragondive/conan_learning"
    description = "Simple project to demonstrate and learn use of Conan"
    topics = ("conan", "gtest", "self-learning")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "**/*.cpp", "**/*.h", "**/CMakeLists.txt"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["conan_gtest"]
