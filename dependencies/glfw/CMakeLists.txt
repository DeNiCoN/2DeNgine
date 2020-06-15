find_package(glfw3 QUIET)

if(NOT glfw3_FOUND)
  message("Glfw3 not found. Downloading...")
  include(FetchContent)
  FetchContent_Declare(glfw
    GIT_REPOSITORY    https://github.com/glfw/glfw
    GIT_TAG           master
    )
  FetchContent_GetProperties(glfw)
  if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    SET(GLFW_BUILD_DOCS OFF)
    SET(GLFW_BUILD_EXAMPLES OFF)
    SET(GLFW_BUILD_TESTS OFF)
    SET(GLFW_INSTALL ON)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
  endif()
endif()
