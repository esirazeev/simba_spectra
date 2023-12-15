cmake_minimum_required(VERSION 3.22.1)

project("simba_spectra_parser_app")

set(CMAKE_CXX_STANDARD 23)
set(TARGET simba_parser)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add raw buffer dependency
include(FetchContent)
FetchContent_Declare(
  pcap_file_reader
  GIT_REPOSITORY https://github.com/esirazeev/pcap_file_reader.git
)
FetchContent_MakeAvailable(pcap_file_reader)

add_executable(simba_parser main.cpp utils.cpp)
target_link_libraries(simba_parser pcap_file_reader)
