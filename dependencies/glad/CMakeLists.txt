include(FetchContent)
FetchContent_Declare(glad
  GIT_REPOSITORY    https://github.com/Dav1dde/glad
  GIT_TAG           master
  )
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
  FetchContent_Populate(glad)
  SET(GLAD_PROFILE "core")
  SET(GLAD_API "gl=4.5")
  add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()
