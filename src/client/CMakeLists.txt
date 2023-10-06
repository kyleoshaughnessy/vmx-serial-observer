get_filename_component(root_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../include ABSOLUTE)

stm32_fetch_cmsis(F4)
stm32_fetch_hal(F4)

find_package(CMSIS COMPONENTS STM32F411CE REQUIRED)
find_package(HAL COMPONENTS STM32F4 REQUIRED)

add_executable(client
  main.c
)

target_link_libraries(client
  CMSIS::STM32::F411CE
  STM32::NoSys
)

target_include_directories(client
  PRIVATE ${root_include_dir}
)

stm32_print_size_of_target(client)
