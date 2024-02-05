from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy

class DataTreeConan(ConanFile):
    name = 'datatree'
    version = '0.0.1'

    license = 'MIT'
    author = 'Matthew Guidry'
    url = 'https://github.com/mguid65/datatree'
    description = 'Datatree'
    topics = 'tree', 'JSON'
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeDeps', 'CMakeToolchain'

    def export_sources(self):
        copy(self, "LICENSE.md", self.recipe_folder, self.export_sources_folder)
        copy(self, "CMakeLists.txt", self.recipe_folder, self.export_sources_folder)
        copy(self, "include/*", self.recipe_folder, self.export_sources_folder)
        copy(self, "source/*", self.recipe_folder, self.export_sources_folder)
        copy(self, "test/*", self.recipe_folder, self.export_sources_folder)

    def requirements(self):
        pass

    def build_requirements(self):
        self.test_requires('catch2/3.5.2')

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def layout(self):
        cmake_layout(self)

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ['datatree']