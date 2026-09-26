cmake_minimum_required(VERSION 3.20)

project(strategy_jam_bots
    VERSION 0.1.0
    DESCRIPTION "Bots for the strategy jam"
    LANGUAGES CXX
)

option(SJB_BUILD_TESTS "Build unit tests" ON)
option(SJB_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Common warning flags, applied per target.
function(sjb_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
        if(SJB_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
            -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
        )
        if(SJB_WARNINGS_AS_ERRORS)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

# Core library: game state, rules, and the simulator. No bot logic, no I/O.
add_library(sjb_core
    src/rules.cpp
    src/simulator.cpp
)
add_library(sjb::core ALIAS sjb_core)
target_include_directories(sjb_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
sjb_set_warnings(sjb_core)

# Bots: each implements the sjb::Bot interface against sjb::core.
add_library(sjb_bots
    bots/random_bot.cpp
    bots/greedy_bot.cpp
    bots/heuristic_bot.cpp
    bots/minimax_bot.cpp
)
add_library(sjb::bots ALIAS sjb_bots)
target_include_directories(sjb_bots PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sjb_bots PUBLIC sjb::core)
sjb_set_warnings(sjb_bots)

# Main executable.
add_executable(strategy_jam_bots
    app/main.cpp
)
target_link_libraries(strategy_jam_bots PRIVATE sjb::core sjb::bots)
sjb_set_warnings(strategy_jam_bots)

if(SJB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
