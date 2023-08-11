cmake_minimum_required(VERSION 3.0.0)
project(asialpaca)

# module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

find_package(ASICamera REQUIRED)

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME drogon
    VERSION 1.7.5
    GITHUB_REPOSITORY drogonframework/drogon
    GIT_TAG v1.7.5
)

add_executable(${PROJECT_NAME} 
    src/helloworld.cpp
    src/ASIAlpaca_Camera.h
    src/ASIAlpaca_Camera.cc
)

# asi camera
target_link_libraries(${PROJECT_NAME} PRIVATE ASICAMERA_LIBRARY)

# drogon
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
