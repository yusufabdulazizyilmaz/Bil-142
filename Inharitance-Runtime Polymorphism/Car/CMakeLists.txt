cmake_minimum_required(VERSION 3.22)
project(inharitance)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(inharitance
        Audi.cpp
        Audi.h
        Bmw.cpp
        Bmw.h
        Car.cpp
        Car.h
        Fiat.cpp
        Fiat.h
        Fiat124.cpp
        Fiat124.h
        main.cpp
        Mercedes.cpp
        Mercedes.h
        Renault.cpp
        Renault.h
        Skoda.cpp
        Skoda.h
        Volvo.cpp
        Volvo.h)
