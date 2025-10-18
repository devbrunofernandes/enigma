cmake_minimum_required(VERSION 3.10)
project(EnigmaMachine)
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