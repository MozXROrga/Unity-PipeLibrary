cmake_minimum_required(VERSION 3.22)

project(TestRunner)

add_compile_definitions(PROJECT_CONFIGURATION="$(Configuration)")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/runner")

file(GLOB_RECURSE SRC_MAIN
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

add_executable(TestRunner ${SRC_MAIN})

set_target_properties(TestRunner PROPERTIES
    CXX_STANDARD 17)
    
set_property(TARGET TestRunner PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test")
    
source_group("" FILES ${SRC_MAIN})


