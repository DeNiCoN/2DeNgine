CMAKE_MINIMUM_REQUIRED(VERSION 3.12.1)

project(2DeNgine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(2DENGINE_BUILD_TESTS "Build 2DeNgine tests")

if(2DENGINE_BUILD_TESTS)
  enable_testing()
  add_subdirectory("tests")
endif()

add_library(2DeNgine STATIC
  "src/resource/DirectoryFilesystem.cpp"
  "src/resource/ResourceManager.cpp"
  "src/resource/ShaderResourceLoader.cpp"
  "src/Engine.cpp"
  "src/gamebasis/ActorFactory.cpp"
  "src/gamebasis/SceneFactory.cpp"
  "src/render/WindowManager.cpp"
  "src/render/RenderManager.cpp"
  "src/render/SpriteBatch.cpp"
  "src/render/SpriteComponent.cpp"
  )

target_include_directories(2DeNgine
  PUBLIC "src"
  )

add_subdirectory(dependencies)

target_link_libraries(2DeNgine
  PUBLIC dependencies
  )
