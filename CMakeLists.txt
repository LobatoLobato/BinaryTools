cmake_minimum_required(VERSION 3.28)
project(BinaryTools)

set(CMAKE_CXX_STANDARD 20)

add_library(BinaryTools STATIC
        BinaryTools/Binary.cpp
        BinaryTools/BinaryReader.cpp
        BinaryTools/BinaryTools.cpp
        BinaryTools/BinaryWriter.cpp

        BinaryTools/Binary.h
        BinaryTools/BinaryReader.h
        BinaryTools/BinaryWriter.h
        BinaryTools/MemoryBuffer.h
        BinaryTools/Span.h
)

target_include_directories(BinaryTools PUBLIC .)

