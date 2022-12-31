cmake_minimum_required(VERSION 3.24)
project(AED2223_G29)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)

add_executable(AED2223_G29
                main.cpp
                headers/Airport.h
                headers/Airline.h
                headers/Flight.h
                headers/DataManager.h
                headers/Coordinate.h
                headers/FlightGraph.h
                src/Airport.cpp
                src/Airline.cpp
                src/Flight.cpp
                src/DataManager.cpp
                src/Coordinate.cpp
                src/FlightGraph.cpp
                Test.hpp
                Statistics.hpp
        src/City.cpp headers/City.h)
