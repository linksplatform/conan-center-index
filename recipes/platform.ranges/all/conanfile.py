from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.files import get, copy
from conan.errors import ConanInvalidConfiguration
from conan.tools.layout import basic_layout
from conan.tools.scm import Version
import os

required_conan_version = ">=2.0"


class PlatformRangesConan(ConanFile):
    name = "platform.ranges"
    license = "Unlicense"
    homepage = "https://github.com/linksplatform/Ranges"
    url = "https://github.com/conan-io/conan-center-index"
    description = """The Platform.Ranges library, as shown in this C++ code, is a comprehensive toolkit for handling and manipulating ranges of values. It provides a customizable Range data structure, equipped with methods for range containment checks, string conversion, stream output, and hash computation, making it a powerful tool for handling ranges in various computational scenarios."""
    topics = ("linksplatform", "cpp20", "any", "ranges", "native")
    settings = "os", "arch", "compiler", "build_type"
    no_copy_source = True

    @property
    def _subfolder_sources(self):
        return os.path.join(self.source_folder, "cpp", "Platform.Ranges")

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
            raise ConanInvalidConfiguration("platform.ranges/{} requires C++{}, "
                                            "which is not supported by apple-clang {}.".format(
                self.version, self._min_cppstd, self.settings.compiler.version))

        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

        minimum_version = self._compilers_minimum_version.get(str(self.settings.compiler), False)
        if minimum_version and Version(self.settings.compiler.version) < minimum_version:
            raise ConanInvalidConfiguration("{}/{} requires C++{}, "
                                            "which is not supported by {} {}.".format(
                self.name, self.version, self._min_cppstd, self.settings.compiler, self.settings.compiler.version))

    def build_requirements(self):
            self.requires("platform.exceptions/0.3.2")
            self.requires("platform.converters/0.2.0")
            self.requires("platform.delegates/0.3.7")
            self.requires("platform.hashing/0.5.6")

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
        self.cpp_info.set_property("cmake_file_name", "Platform.Ranges")
        self.cpp_info.set_property("cmake_target_name", "Platform.Ranges::Platform.Ranges")
        self.cpp_info.names["cmake_find_package"] = "Platform.Ranges"
        self.cpp_info.names["cmake_find_package_multi"] = "Platform.Ranges"