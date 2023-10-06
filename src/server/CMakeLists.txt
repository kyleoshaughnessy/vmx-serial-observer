get_filename_component(root_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../include ABSOLUTE)

include(FetchContent)

# --- Fetch CLI11 --------------------------------------------------------------
FetchContent_Declare(
  cli11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11
  GIT_TAG        v2.3.2
)
FetchContent_MakeAvailable(cli11)
# ------------------------------------------------------------------------------

# --- Fetch fmt ----------------------------------------------------------------
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        10.1.1
)
FetchContent_MakeAvailable(fmt)
# ------------------------------------------------------------------------------

# --- Fetch vmx ----------------------------------------------------------------
FetchContent_Declare(
  vmx
  GIT_REPOSITORY https://github.com/kyleoshaughnessy/vmx
  GIT_TAG        v0.0.1-alpha2
)
FetchContent_MakeAvailable(vmx)
# ------------------------------------------------------------------------------

add_executable(server
  main.cpp
)

target_link_libraries(server
  PRIVATE CLI11::CLI11
  PRIVATE fmt::fmt
  PRIVATE vmx::core
)

target_compile_features(server
  PUBLIC cxx_std_20
)

if (MSVC)
  target_compile_options(server
    PRIVATE /W4 /WX
  )
else()
  target_compile_options(server
    PRIVATE -Wall -Wextra -Wpedantic -Werror -Wmissing-declarations -Wdeprecated -Wshadow
  )
endif()

target_include_directories(server
  PRIVATE ${root_include_dir}
)
