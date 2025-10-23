cmake_minimum_required(VERSION 3.14)
project(EnigmaMachine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(cxxopts)

add_executable(enigma_machine
    main.cpp
    enigma.cpp
    plugboard.cpp
    reflector.cpp
    rotor.cpp
    argumentUI.cpp
    interactiveUI.cpp
)

target_include_directories(enigma_machine PUBLIC include)
target_link_libraries(enigma_machine PRIVATE cxxopts::cxxopts)