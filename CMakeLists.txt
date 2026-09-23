cmake_minimum_required(VERSION 4.3)
project(SimpleTurnServer C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleTurnServer main.c
        Infrastructure/udp.c
        Infrastructure/queue.c
        Infrastructure/queue.h
        Components/NetworkMainLoop.c
        Components/NetworkMainLoop.h
        Infrastructure/packet.h
        Infrastructure/packet.c)
