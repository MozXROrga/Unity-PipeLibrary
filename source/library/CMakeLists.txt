cmake_minimum_required(VERSION 3.22)

project(IPCLib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/lib")
add_compile_definitions(IPC_LIB_EXPORTS)

file(GLOB_RECURSE SRC_MAIN
    "${PROJECT_SOURCE_DIR}/src/ipcLib.cpp"
    "${PROJECT_SOURCE_DIR}/src/ipcLib.h"
)

add_library(IPCLib  SHARED ${SRC_MAIN})

set_target_properties(IPCLib PROPERTIES
    CXX_STANDARD 17)

source_group("" FILES ${SRC_MAIN})

add_custom_command(TARGET IPCLib PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/src/ipcLib.h ${CMAKE_SOURCE_DIR}/include/ipcLib.h
)

add_custom_command(TARGET IPCLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/bin/lib/$(Configuration)/IPCLib.dll ${CMAKE_SOURCE_DIR}/lib/$(Configuration)/IPCLib.dll
)

file(COPY ${PROJECT_SOURCE_DIR}/src/ipcLib.h
    DESTINATION ${CMAKE_SOURCE_DIR}/include)
