cmake_minimum_required(VERSION 3.22.1)

project("simba_spectra_parser")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
  pcap_file_reader
  GIT_REPOSITORY https://github.com/esirazeev/pcap_file_reader.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(pcap_file_reader)

# file(GLOB_RECURSE SIMBA_PARSER_SOURCES "simba_parser/*.cpp")
# add_executable(simba_spectra_parser main.cpp ${SIMBA_PARSER_SOURCES})
# target_include_directories(simba_spectra_parser PRIVATE sbe_message)
add_executable(simba_spectra_parser main.cpp)
target_link_libraries(simba_spectra_parser pcap_file_reader)