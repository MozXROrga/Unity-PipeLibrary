cmake_minimum_required(VERSION 3.22)

project(CSWrapper LANGUAGES CSharp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/csWrapper")

file(GLOB_RECURSE SRC_MAIN
    "${PROJECT_SOURCE_DIR}/src/program.cs"
    "${PROJECT_SOURCE_DIR}/src/IPCLibWrapper.cs"
)

add_executable(CSWrapper ${SRC_MAIN})

set_target_properties(CSWrapper PROPERTIES
    FOLDER cs)

source_group("" FILES ${SRC_MAIN})

set_target_properties(
    CSWrapper PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/csWrapper/$(Configuration)"
    VS_DEBUGGER_COMMAND_ARGUMENTS "master")

add_custom_command(TARGET CSWrapper PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/src/IPCLibWrapper.cs ${CMAKE_SOURCE_DIR}/include/IPCLibWrapper.cs
)

add_custom_command(TARGET CSWrapper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/$(Configuration)/IPCLib.dll ${CMAKE_SOURCE_DIR}/bin/test/csWrapper/$(Configuration)/IPCLib.dll
)
