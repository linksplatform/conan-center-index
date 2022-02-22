import os

from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration

required_conan_version = ">=1.33.0"


class PlatformInterfacesConan(ConanFile):
    name = "platform.collections"
    license = "MIT"
    homepage = "https://github.com/linksplatform/Collections"
    url = "https://github.com/conan-io/conan-center-index"
    description = """lol"""
    topics = ("linksplatform", "cpp20", "Collections", "header-only")
    settings = "os", "compiler", "build_type", "arch"
    no_copy_source = True

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    @property
    def _internal_cpp_subfolder(self):
        return os.path.join(self._source_subfolder, "cpp", "Platform.Collections")

    @property
    def _compilers_minimum_version(self):
        return {
            "gcc": "10",
            "Visual Studio": "16",
            "clang": "11",
            "apple-clang": "11"
        }

    @property
    def _minimum_cpp_standard(self):
        return 20

    def requirements(self):
        self.requires("platform.interfaces/0.2.5")
        self.requires("platform.exceptions/0.2.0")
        self.requires("platform.equality/0.0.1")
        self.requires("platform.hashing/0.2.0")
        self.requires("platform.random/0.1.0")
        self.requires("ms-gsl/4.0.0")

    def validate(self):
        minimum_version = self._compilers_minimum_version.get(str(self.settings.compiler))

        if not minimum_version:
            self.output.warn("{} recipe lacks information about the {} compiler support.".format(
                self.name, self.settings.compiler))

        if tools.Version(self.settings.compiler.version) < minimum_version:
            raise ConanInvalidConfiguration("platform.collections/{} "
                                            "requires C++{} with {}, "
                                            "which is not supported "
                                            "by {} {}.".format(
                self.version, self._minimum_cpp_standard, self.settings.compiler, self.settings.compiler,
                self.settings.compiler.version))

        if self.settings.compiler.get_safe("cppstd"):
            tools.check_min_cppstd(self, self._minimum_cpp_standard)

    def source(self):
        tools.get(**self.conan_data["sources"][self.version],
        destination=self._source_subfolder, strip_root=True)

    def package(self):
        # self.output.error(self._internal_cpp_subfolder)
        self.copy("*.h", dst="include", src=self._internal_cpp_subfolder)
        self.copy("LICENSE", dst="licenses", src=self._source_subfolder)

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        self.cpp_info.names["cmake_find_package"] = "Platform.Collections"
        self.cpp_info.names["cmake_find_package_multi"] = "Platform.Collections"
