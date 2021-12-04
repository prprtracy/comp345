cmake_minimum_required(VERSION 3.20)
project(comp345)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(comp345
        Cards.cpp
        Cards.h
        CardsDriver.cpp
        gameEngine.cpp
        gameEngine.h
        Map.cpp
        Map.h
        MapDriver.cpp
        MapLoader.cpp
        MapLoader.h
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        Player.cpp
        Player.h
        PlayerDriver.cpp Part3Driver.cpp
        commandProcessorDriver.cpp
        commandProcessor.h
        commandProcessor.cpp
        )
