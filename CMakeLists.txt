cmake_minimum_required(VERSION 3.24)
project(AED2223_G29)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)

add_executable(AED2223_G29 main.cpp headers/Airport.h headers/Airline.h headers/Flight.h src/Airline.cpp src/Airport.cpp src/Flight.cpp src/DataManager.cpp headers/DataManager.h src/Coordinate.cpp headers/Coordinate.h Test.hpp src/FlightGraph.cpp)
