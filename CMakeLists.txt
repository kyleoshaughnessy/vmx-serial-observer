cmake_minimum_required(VERSION 3.16)

#
# If building the client application, we need to fetch stm32-cmake and set the
# toolchain before declaring the project
#
if(VSO_BUILD_CLIENT)
    # Fetch stm32-cmake
    include(FetchContent)
    FetchContent_Declare(
        stm32-cmake
        GIT_REPOSITORY https://github.com/ObKo/stm32-cmake/
        GIT_TAG        845373b1562ca7ff34ef8c5762d5976749ac1478
        GIT_PROGRESS   TRUE
    )
    FetchContent_MakeAvailable(stm32-cmake)

    # Set the toolchain file
    set(CMAKE_TOOLCHAIN_FILE ${stm32-cmake_SOURCE_DIR}/cmake/stm32_gcc.cmake)
endif()

project(
    vmx-serial-observer
    VERSION 0.0.1
    LANGUAGES CXX C ASM
)

# TODO: Find a better way to represent what is really an enum option
option(VSO_BUILD_SERVER "whether or not to generate server build environment" OFF)
option(VSO_BUILD_CLIENT "whether or not to generate client build environment" OFF)

add_subdirectory(src)
