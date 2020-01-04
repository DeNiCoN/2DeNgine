CMAKE_MINIMUM_REQUIRED(VERSION 3.12.1)

project(2DeNgine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(2DeNgine STATIC
  "src/resource/ResourceManager.cpp"
  )

target_include_directories(2DeNgine
  PUBLIC "src"
  )

