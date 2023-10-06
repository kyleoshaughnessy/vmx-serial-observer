if(VSO_BUILD_SERVER AND VSO_BUILD_CLIENT)
  message(FATAL_ERROR "only one of {VSO_BUILD_SERVER, VSO_BUILD_CLIENT} may be specified.")
endif()

if((NOT VSO_BUILD_SERVER) AND (NOT VSO_BUILD_CLIENT))
  message(FATAL_ERROR "one of {VSO_BUILD_SERVER, VSO_BUILD_CLIENT} must be specified.")
endif()

if(VSO_BUILD_SERVER)
  add_subdirectory(server)
endif()

if(VSO_BUILD_CLIENT)
  add_subdirectory(client)
endif()
