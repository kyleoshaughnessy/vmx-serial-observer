get_filename_component(root_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../include ABSOLUTE)

stm32_fetch_cmsis(F4)
stm32_fetch_hal(F4)

find_package(CMSIS COMPONENTS STM32F411CE REQUIRED)
find_package(HAL COMPONENTS STM32F4 REQUIRED)

add_executable(client
  main.c
  stm32f4xx_hal_msp.c
  stm32f4xx_it.c
  syscalls.c
  sysmem.c
  include/stm32_hal_conf/stm32f4xx_hal_conf.h
)

target_link_libraries(client
  HAL::STM32::F4::CORTEX
  HAL::STM32::F4::DMA
  HAL::STM32::F4::EXTI
  HAL::STM32::F4::FLASH
  HAL::STM32::F4::GPIO
  HAL::STM32::F4::PWR
  HAL::STM32::F4::RCC
  HAL::STM32::F4::TIM
  HAL::STM32::F4::UART
  CMSIS::STM32::F411CE
  STM32::NoSys
)

target_include_directories(client
  PRIVATE ${root_include_dir}
  PRIVATE include/stm32_hal_conf
)

stm32_print_size_of_target(client)
