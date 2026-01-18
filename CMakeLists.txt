# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/pico/pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picloc C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(picloc picloc.c display.c)

pico_set_program_name(picloc "picloc")
pico_set_program_url(picloc "https://github.com/Tomunek/PiCloc")
pico_set_program_description(picloc "Simple Raspberry Pi Pico clock.")

# Get commit SHA
execute_process(COMMAND git log --pretty=format:'%h' -n 1
OUTPUT_VARIABLE GIT_REV
ERROR_QUIET)

if ("${GIT_REV}" STREQUAL "")
set(GIT_REV "N/A")
endif()
pico_set_program_version(picloc "${GIT_REV}")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(picloc 0)
pico_enable_stdio_usb(picloc 1)

# Add the standard library to the build
target_link_libraries(picloc
        hardware_rtc
        pico_stdlib
        pico_multicore
        )

# Add the standard include files to the build
target_include_directories(picloc PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(picloc)
