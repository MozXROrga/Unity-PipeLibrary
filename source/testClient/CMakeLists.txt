cmake_minimum_required(VERSION 3.22)

project(TestClient)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test/client")

file(GLOB_RECURSE SRC_MAIN
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(TestClient ${SRC_MAIN})

set_target_properties(TestClient PROPERTIES
    CXX_STANDARD 17)

source_group("" FILES ${SRC_MAIN})

target_link_libraries(TestClient IPCLib)

add_custom_command(TARGET TestClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/$(Configuration)/IPCLib.dll ${CMAKE_SOURCE_DIR}/bin/test/client/$(Configuration)/IPCLib.dll
)
