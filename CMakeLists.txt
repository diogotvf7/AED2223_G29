cmake_minimum_required(VERSION 3.24)
project(AED2223_G29)

set(CMAKE_CXX_STANDARD 17)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

include_directories(headers)

add_executable(AED2223_G29
        main.cpp
        headers/Airport.h
        headers/Airline.h
        headers/Flight.h
        headers/DataManager.h
        headers/Coordinate.h
        headers/FlightGraph.h
        headers/Menu.h
        headers/City.h
        src/Airport.cpp
        src/Airline.cpp
        src/Flight.cpp
        src/DataManager.cpp
        src/Coordinate.cpp
        src/FlightGraph.cpp
        src/City.cpp
        src/Menu.cpp
        Test.hpp
        Statistics.hpp
        src/Country.cpp headers/Country.h)

