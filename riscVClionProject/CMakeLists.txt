cmake_minimum_required(VERSION 3.14)
project(tacticModel)

set(CMAKE_CXX_STANDARD 14)

add_executable(tacticModel main.cpp Memory.cpp Memory.h Emulator.cpp Emulator.h FetchPhase.cpp FetchPhase.h DecodePhase.cpp DecodePhase.h ExecutePhase.cpp ExecutePhase.h MemoryPhase.cpp MemoryPhase.h WriteBackPhase.cpp WriteBackPhase.h PipelineStructure.h Instructions.cpp Instructions.h)