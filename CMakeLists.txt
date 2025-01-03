# Minimum version and project information  
cmake_minimum_required(VERSION 3.20)   

# Platform checks  
if(NOT WIN32)  
    message(FATAL_ERROR "This project supports Windows only")  
endif()   

# Configure vcpkg toolchain 
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)  
    if(DEFINED ENV{VCPKG_ROOT})  
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"  
            CACHE STRING "Vcpkg toolchain file")  
    else()  
        message(FATAL_ERROR "VCPKG_ROOT environment variable is not set")  
    endif()  
endif()  

# Project definition
project(dx12 VERSION 1.0.0 LANGUAGES CXX)  

# Add vcpkg installation path to CMAKE_PREFIX_PATH  
if(DEFINED ENV{VCPKG_ROOT})  
    list(APPEND CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-windows")  
endif()

# Global settings  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT dx12)  

# Function for automatic include directories  
function(auto_include_directories target_name base_dir)  
    file(GLOB_RECURSE HEADER_DIRS   
        LIST_DIRECTORIES true   
        "${base_dir}/*.h"  
        "${base_dir}/*.hpp"  
    )  

    set(INCLUDE_DIRS "")  
    foreach(DIR ${HEADER_DIRS})  
        get_filename_component(PARENT_DIR ${DIR} DIRECTORY)  
        list(APPEND INCLUDE_DIRS ${PARENT_DIR})  
    endforeach()  

    list(REMOVE_DUPLICATES INCLUDE_DIRS)  
    target_include_directories(${target_name} PRIVATE ${INCLUDE_DIRS})  
endfunction()  

# Function for automatic source grouping  
function(auto_source_group)  
    foreach(FILE ${ARGN})  
        file(RELATIVE_PATH REL_FILE "${CMAKE_CURRENT_SOURCE_DIR}" ${FILE})  
        get_filename_component(DIR_PATH ${REL_FILE} DIRECTORY)  
        string(REPLACE "/" "\\" GROUP_PATH "${DIR_PATH}")  
        
        if(${FILE} MATCHES ".*\\.h")  
            source_group("Header Files\\${GROUP_PATH}" FILES ${FILE})  
        elseif(${FILE} MATCHES ".*\\.cpp")  
            source_group("Source Files\\${GROUP_PATH}" FILES ${FILE})  
        endif()  
    endforeach()  
endfunction()  

# Paths and resources  
set(PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public)  
set(PRIVATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/Private)  

file(GLOB_RECURSE PUBLIC_HEADERS "${PUBLIC_DIR}/*.h")  
file(GLOB_RECURSE PRIVATE_SOURCES "${PRIVATE_DIR}/*.cpp")  

# C++ settings  
set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

# Find packages  
#list(APPEND CMAKE_PREFIX_PATH "C:/Users/fatba/vcpkg/installed/x64-windows")  
find_package(GTest CONFIG REQUIRED)  
find_package(benchmark CONFIG REQUIRED)  
find_package(directx-headers CONFIG REQUIRED)  
find_package(directxtk12 CONFIG REQUIRED)  

# Main executable  
add_executable(dx12 WIN32 ${PRIVATE_SOURCES} ${PUBLIC_HEADERS})  
auto_include_directories(dx12 ${CMAKE_SOURCE_DIR}/Source)  
auto_source_group(${PUBLIC_HEADERS} ${PRIVATE_SOURCES})  

# Test executable  
add_executable(Tests Test/Test.cpp)  
auto_include_directories(Tests ${CMAKE_SOURCE_DIR}/Source)  

# DirectX libraries  
set(DIRECTX_LIBS  
    Microsoft::DirectX-Headers  
    Microsoft::DirectXTK12  
    d3d12.lib  
    dxgi.lib  
    dxguid.lib  
)  

# Library linking  
target_link_libraries(dx12 PRIVATE ${DIRECTX_LIBS})  
target_link_libraries(Tests PRIVATE   
    GTest::gtest   
    GTest::gtest_main  
    benchmark::benchmark   
    benchmark::benchmark_main  
    ${DIRECTX_LIBS}  
)  

# Windows and MSVC settings  
if(WIN32 AND MSVC)  
    # Auto-detect Windows SDK path  
    get_filename_component(WINDOWS_SDK_PATH  
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot10]"  
        ABSOLUTE  
    )  

    message(STATUS "Windows SDK Path: ${WINDOWS_SDK_PATH}")  

    # Include DirectX paths  
    target_include_directories(dx12 PRIVATE  
        "${WINDOWS_SDK_PATH}/Include/${CMAKE_WINDOWS_KITS_VERSION}/um"  
        "${WINDOWS_SDK_PATH}/Include/${CMAKE_WINDOWS_KITS_VERSION}/shared"  
        "${WINDOWS_SDK_PATH}/Include/${CMAKE_WINDOWS_KITS_VERSION}/winrt"  
    )  

    # Common optimization flags safe for both Debug and Release  
    set(COMMON_OPTIMIZATION_FLAGS  
        /arch:AVX2    # Enable AVX2 SIMD instructions  
        /fp:fast      # Fast floating point model  
        /Oi           # Enable intrinsic functions  
        /GT           # Fiber-safe optimization  
        /Gy           # Enable function-level linking  
        /MP           # Multi-processor compilation  
        /Gw           # Optimize global data  
    )  

    # Release-specific optimization flags  
    set(RELEASE_OPTIMIZATION_FLAGS  
        /GL          # Whole program optimization  
        /O2          # Maximum optimization  
        /Ot          # Favor speed over size  
        /Ob2         # Aggressive inlining  
        /Qpar        # Auto-parallelization  
        /Qfast_transcendentals  # Fast transcendental functions  
    )  

    # Debug-specific optimization flags  
    set(DEBUG_OPTIMIZATION_FLAGS  
        /Od          # Disable optimization  
        /RTC1        # Runtime error checks  
        /Ob0         # Disable inlining  
    )  

    # Warning and code generation flags  
    set(WARNING_FLAGS  
        /W4           # Warning level 4  
        /WX-          # Treat warnings as warnings, not errors  
        /wd4100       # Ignore unused parameters  
        /wd4458       # Ignore class member hiding  
        /permissive-  # Strict standard compliance  
    )  

    # Apply configuration-specific flags to dx12  
    target_compile_options(dx12 PRIVATE   
        ${WARNING_FLAGS}  
        ${COMMON_OPTIMIZATION_FLAGS}  
        $<$<CONFIG:Release>:${RELEASE_OPTIMIZATION_FLAGS}>  
        $<$<CONFIG:Debug>:${DEBUG_OPTIMIZATION_FLAGS}>  
    )  

    # Apply configuration-specific flags to Tests  
    target_compile_options(Tests PRIVATE   
        ${WARNING_FLAGS}  
        ${COMMON_OPTIMIZATION_FLAGS}  
        $<$<CONFIG:Release>:${RELEASE_OPTIMIZATION_FLAGS}>  
        $<$<CONFIG:Debug>:${DEBUG_OPTIMIZATION_FLAGS}>  
    )  

    # Static runtime linking  
    set_target_properties(dx12 Tests PROPERTIES  
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"  
    )  

    # Release-only linker optimizations  
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")  
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")  

    # Additional Release optimizations  
    if(CMAKE_BUILD_TYPE STREQUAL "Release")  
        target_compile_definitions(dx12 PRIVATE  
            NDEBUG  
            _ITERATOR_DEBUG_LEVEL=0  
        )  
    endif()  
endif()  

# Copy resources to output directory  
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources  
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})  

message(STATUS "Project Configuration Complete")  