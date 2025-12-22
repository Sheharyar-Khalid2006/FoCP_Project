cmake_minimum_required(VERSION 3.10)

# Project name and version
project(InvestmentSimulator VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    src/main.cpp
    src/interface.cpp
    src/graph.cpp
    src/investment.cpp
    src/validation.cpp
    src/market.cpp
    src/pbPlots.cpp
    src/supportLib.cpp
)

# Header files (for IDE support)
set(HEADERS
    src/interface.hpp
    src/graph.hpp
    src/investment.h
    src/validation.h
    src/market.h
    src/pbPlots.hpp
    src/supportLib.hpp
)

# Create executable
add_executable(InvestmentSimulator ${SOURCES} ${HEADERS})

# Include directory for headers
target_include_directories(InvestmentSimulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Compiler-specific settings
if(MSVC)
    # MSVC-specific compiler flags
    target_compile_options(InvestmentSimulator PRIVATE
        /W4                 # Warning level 4
        /WX-                # Don't treat warnings as errors
        /permissive-        # Standards conformance mode
        /Zc:__cplusplus     # Enable updated __cplusplus macro
        /EHsc               # Exception handling model
        /MP                 # Multi-processor compilation
    )
    
    # Disable specific MSVC warnings
    target_compile_options(InvestmentSimulator PRIVATE
        /wd4244             # Conversion warnings (double to float)
        /wd4267             # Size_t conversion warnings
        /wd4305             # Truncation warnings
    )
    
    # Set subsystem to console
    set_target_properties(InvestmentSimulator PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
    
    # Define _CRT_SECURE_NO_WARNINGS for MSVC
    target_compile_definitions(InvestmentSimulator PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _CRT_NONSTDC_NO_DEPRECATE
    )
    
elseif(MINGW)
    # MinGW-specific compiler flags
    target_compile_options(InvestmentSimulator PRIVATE
        -Wall               # Enable most warnings
        -Wextra             # Enable extra warnings
        -Wno-unused-parameter
        -Wno-sign-compare
        -static-libgcc      # Static link libgcc
        -static-libstdc++   # Static link libstdc++
    )
    
    # Static linking for MinGW to create standalone executable
    target_link_options(InvestmentSimulator PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
    
    # Console subsystem for MinGW
    if(WIN32)
        target_link_options(InvestmentSimulator PRIVATE -mconsole)
    endif()
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC-specific compiler flags (for Linux/other)
    target_compile_options(InvestmentSimulator PRIVATE
        -Wall
        -Wextra
        -Wno-unused-parameter
        -Wno-sign-compare
    )
endif()

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    target_compile_definitions(InvestmentSimulator PRIVATE
        WIN32_LEAN_AND_MEAN     # Exclude rarely-used Windows headers
        NOMINMAX                # Prevent Windows.h from defining min/max macros
    )
endif()

# Link libraries
if(UNIX)
    # For Linux/Unix systems, link pthread and math libraries
    target_link_libraries(InvestmentSimulator PRIVATE pthread m)
endif()

# Installation rules
install(TARGETS InvestmentSimulator
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Print build information
message(STATUS "")
message(STATUS "Investment Simulator - Build Configuration")
message(STATUS "==========================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "==========================================")
message(STATUS "")

# Optional: Create build configurations
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build: Debug Release RelWithDebInfo MinSizeRel"
        FORCE)
endif()

# Debug configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(InvestmentSimulator PRIVATE DEBUG_BUILD)
    if(MSVC)
        target_compile_options(InvestmentSimulator PRIVATE /Od /Zi)
    else()
        target_compile_options(InvestmentSimulator PRIVATE -O0 -g)
    endif()
endif()

# Release configuration
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(InvestmentSimulator PRIVATE RELEASE_BUILD)
    if(MSVC)
        target_compile_options(InvestmentSimulator PRIVATE /O2)
    else()
        target_compile_options(InvestmentSimulator PRIVATE -O3)
    endif()
endif()
