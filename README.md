# VMX Serial Observer

This project contains the following:
- Windows user-mode application that acts as a server for VMX interactions over a serial protocol
- STM32 embedded application that serves as a client to the serial protocol and acts as a "front-end" for the volume mixer

## Building

The CMake project contains two primary targets that require different build environments to support their unique tool-chains -- As such, we must generate the two environments separate from each other (as per CMake limitations).

```console
cmake -S vmx-serial-observer -B build_server_debug -DCMAKE_BUILD_TYPE=Debug -DVSO_BUILD_SERVER=ON
cmake -S vmx-serial-observer -B build_client_debug -DCMAKE_BUILD_TYPE=Debug -DVSO_BUILD_CLIENT=ON

cmake --build build_server_debug
cmake --build build_client_debug
```

> **_NOTE:_**  Some generators like Visual Studio do not play nicely with the stm32 toolchain used in the client build. Recommended generators when building from Windows are: MinGW Makefiles, Ninja, or NMake Makefiles.
