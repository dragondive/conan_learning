from conans import ConanFile, tools


class RandomConan(ConanFile):
    name = "random"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    options = { "shared": [True, False] }
    description = "Library to provide a standard IEEE-vetted random number"
    url = "None"
    license = "None"
    author = "Aravind Pai dragondive@outlook.in"
    topics = None

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


    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
