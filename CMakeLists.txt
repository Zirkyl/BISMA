cmake_minimum_required(VERSION 3.30)
project(BISMA C)

set(CMAKE_C_STANDARD 23)

add_executable(BISMA main.c
        Headers/CRUDPaketBimbel.h
        Headers/CRUDDiskon.h)
