cmake_minimum_required(VERSION 3.20)
project(74HC595 C)

set(CMAKE_C_STANDARD 99)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME STM32Core
        GITHUB_REPOSITORY ximtech/STM32Core
        GIT_TAG origin/main)

set(74HC595_DIRECTORY
        ${SPI_POLLING_DIRECTORY}
        ${74HC595_SOURCE_DIR}
        ${74HC595_SOURCE_DIR}/include
        CACHE STRING "74HC595 directories include to the main project" FORCE)

set(74HC595_SOURCES
        ${SPI_POLLING_SOURCES}
        ${74HC595_SOURCE_DIR}/74HC595.c
        ${74HC595_SOURCE_DIR}/include/74HC595.h
        CACHE STRING "74HC595 source files include to the main project" FORCE)