cmake_minimum_required(VERSION 3.20)

# The Python package is called libCBDetect, keep the same CMake project name
project(libCBDetect VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(GNUInstallDirs)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB CBDETECT_CORE_SRC CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        "${PROJECT_SOURCE_DIR}/src/*.cpp")

list(REMOVE_ITEM CBDETECT_CORE_SRC
        "${PROJECT_SOURCE_DIR}/src/bindings.cpp")

add_library(cbdetect_core STATIC ${CBDETECT_CORE_SRC})
target_compile_definitions(cbdetect_core PRIVATE CBDETECT_EXPORTS)
target_include_directories(cbdetect_core PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(cbdetect_core PUBLIC ${OpenCV_LIBRARIES})
target_compile_features(cbdetect_core PUBLIC cxx_std_17)

if (MSVC)
    set_target_properties(cbdetect_core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

pybind11_add_module(Checkerboard MODULE
        src/bindings.cpp
        $<TARGET_OBJECTS:cbdetect_core>)

target_compile_definitions(Checkerboard PRIVATE CBDETECT_EXPORTS)
target_include_directories(Checkerboard
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Checkerboard
        PRIVATE
        cbdetect_core
        pybind11::module
        ${OpenCV_LIBRARIES})

if (MSVC)
    set_target_properties(Checkerboard PROPERTIES PREFIX "")
endif()

install(TARGETS Checkerboard
        LIBRARY DESTINATION ${PROJECT_NAME})
