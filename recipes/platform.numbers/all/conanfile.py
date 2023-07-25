from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.files import get, copy
from conan.errors import ConanInvalidConfiguration
from conan.tools.layout import basic_layout
from conan.tools.scm import Version
import os

required_conan_version = ">=2.0"

class PlatformNumbersConan(ConanFile):
    name = "platform.numbers"
    license = "Unlicense"
    homepage = "https://github.com/linksplatform/Numbers"
    url = "https://github.com/conan-io/conan-center-index"
    description = """The Platform.Numbers library, as presented in this C++ code, offers a specialized set of numerical computation and manipulation tools focused on bit-level operations. It provides functions for operations such as counting bits, identifying the position of the lowest bit, and partial reading and writing of numerical data at the bit level, making it a key asset for applications requiring low-level, bit-wise data manipulation."""
    topics = ("linksplatform", "cpp20", "exceptions", "any", "ranges", "native")
    settings = "os", "arch", "compiler", "build_type"
    no_copy_source = True

    @property
    def _subfolder_sources(self):
        return os.path.join(self.source_folder, "cpp", "Platform.Numbers")

    @property
    def _min_cppstd(self):
        return "20"

    @property
    def _compilers_minimum_version(self):
        return {
            "gcc": "10",
            "Visual Studio": "16",
            "msvc": "193",
            "clang": "11",
            "apple-clang": "12"
        }

    def layout(self):
        basic_layout(self, src_folder="src")

    def package_id(self):
        self.info.clear()

    def validate(self):
        if self.settings.compiler == "apple-clang" and Version(self.settings.compiler.version) < "12":
            raise ConanInvalidConfiguration("platform.exceptions/{} requires C++{}, "
                                            "which is not supported by apple-clang {}.".format(
                self.version, self._min_cppstd, self.settings.compiler.version))

        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

        minimum_version = self._compilers_minimum_version.get(str(self.settings.compiler), False)
        if minimum_version and Version(self.settings.compiler.version) < minimum_version:
            raise ConanInvalidConfiguration("{}/{} requires C++{}, "
                                            "which is not supported by {} {}.".format(
                self.name, self.version, self._min_cppstd, self.settings.compiler, self.settings.compiler.version))

    def source(self):
        get(self, **self.conan_data["sources"][self.version]["source"], strip_root=True)

    def package(self):
        copy(
                self,
                pattern="*.h",
                dst=os.path.join(self.package_folder, "include"),
                src=self.source_folder,
            )
        copy(self, pattern="LICENSE", dst="licenses", src=self.source_folder)
    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.set_property("cmake_file_name", "Platform.Numbers")
        self.cpp_info.set_property("cmake_target_name", "Platform.Numbers::Platform.Numbers")
        self.cpp_info.names["cmake_find_package"] = "Platform.Numbers"
        self.cpp_info.names["cmake_find_package_multi"] = "Platform.Numbers"