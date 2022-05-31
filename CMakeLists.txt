cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
project(kiero)

FetchContent_Declare(
        MinHook
        GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
        GIT_TAG master
)
FetchContent_MakeAvailable(MinHook)

add_library(kiero STATIC kiero.cpp kiero.h)

target_include_directories(kiero
        PRIVATE minhook
        PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(kiero
        PRIVATE minhook)