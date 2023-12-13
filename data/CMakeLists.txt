cmake_minimum_required(VERSION 3.22.1)

project("simba_spectra_parser_app")

set(CMAKE_CXX_STANDARD 23)
set(TARGET simba_parser)

# set directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add exec
add_executable(${TARGET} main.cpp utils.cpp)
target_include_directories(${TARGET} PRIVATE ..)

# link libs
file(GLOB LIBS ${CMAKE_SOURCE_DIR}/pcap_reader/lib/*)
target_link_libraries(${TARGET} PRIVATE ${LIBS})