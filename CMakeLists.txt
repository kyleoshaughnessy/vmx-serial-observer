cmake_minimum_required(VERSION 3.16)

project(
    vmx-serial-observer
    VERSION 0.0.1
    LANGUAGES CXX
)

# TODO: Find a better way to represent what is really an enum option
option(VSO_BUILD_SERVER "whether or not to generate server build environment" OFF)
option(VSO_BUILD_CLIENT "whether or not to generate client build environment" OFF)

add_subdirectory(src)
