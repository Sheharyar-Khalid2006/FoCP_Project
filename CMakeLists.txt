cmake_minimum_required(VERSION 3.16)

# Project name and version
project(FoCP_Project VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic MOC, UIC, and RCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set UI files directory (Qt Designer .ui files)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

# Compiler detection and preference (MinGW first, then MSVC)
if(WIN32)
    if(MINGW)
        message(STATUS "Using MinGW compiler")
        set(CMAKE_CXX_COMPILER "g++")
        # MinGW specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    elseif(MSVC)
        message(STATUS "Using MSVC compiler")
        # MSVC specific flags
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif()
endif()

# Find Qt6 packages - ONLY Widgets (Charts removed - deprecated in Qt 6.10.1)
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

# If Qt6 is not found, print helpful error message
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found! Please install Qt 6.10 or later with Widgets module.")
endif()

# Source files from src/ directory
set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.hpp
    src/mainwindow.ui
    src/investment.cpp
    src/investment.hpp
    src/ui.cpp
    src/ui.hpp
    src/validation.cpp
    src/validation.hpp
    src/market.cpp
    src/market.hpp
    src/chart.cpp
    src/chart.hpp
    src/fileio.cpp
    src/fileio.hpp
    # reporting.cpp and reporting.hpp excluded for now
)

# NO RESOURCE FILES - Assets folder not used
# set(PROJECT_RESOURCES
#     Assets/assets.qrc
# )

# Create executable with sources only (no resources)
add_executable(FoCP_Project 
    ${PROJECT_SOURCES}
    # ${PROJECT_RESOURCES}  # Commented out - no assets
)

# Include directories for header files
target_include_directories(FoCP_Project PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Link Qt libraries - ONLY Widgets (no Charts)
target_link_libraries(FoCP_Project PRIVATE
    Qt6::Widgets
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings - make it a GUI application (not console)
    set_target_properties(FoCP_Project PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    
    # Deploy Qt dependencies after build (Windows only)
    if(Qt6_FOUND)
        # Get the Qt binary directory
        get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
        get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)
        
        # Find windeployqt
        find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")
        
        if(WINDEPLOYQT_EXECUTABLE)
            # Deploy Qt dependencies after build
            add_custom_command(TARGET FoCP_Project POST_BUILD
                COMMAND "${WINDEPLOYQT_EXECUTABLE}" 
                        --no-translations
                        --no-system-d3d-compiler
                        --no-opengl-sw
                        "$<TARGET_FILE:FoCP_Project>"
                COMMENT "Running windeployqt to deploy Qt runtime dependencies..."
            )
        else()
            message(WARNING "windeployqt not found. You may need to manually copy Qt DLLs.")
        endif()
    endif()
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Copy output to root build folder for easier access
add_custom_command(TARGET FoCP_Project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:FoCP_Project>
        ${CMAKE_BINARY_DIR}/FoCP_Project${CMAKE_EXECUTABLE_SUFFIX}
    COMMENT "Copying executable to build root for easy access..."
)

# Installation rules (optional)
install(TARGETS FoCP_Project
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Print configuration summary
message(STATUS "==============================================")
message(STATUS "FoCP_Project - Investment Simulator")
message(STATUS "==============================================")
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "Qt Version: ${Qt6_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
if(MINGW)
    message(STATUS "Compiler: MinGW (G++ ${CMAKE_CXX_COMPILER_VERSION})")
elseif(MSVC)
    message(STATUS "Compiler: MSVC ${MSVC_VERSION}")
endif()
message(STATUS "Assets: DISABLED (no resources included)")
message(STATUS "Qt Charts: NOT USED (deprecated in 6.10.1 - using custom QPainter)")
message(STATUS "Source Directory: ${CMAKE_SOURCE_DIR}/src")
message(STATUS "Output Directory: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "==============================================")