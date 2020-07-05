find_package(tinyxml2 QUIET)

if(NOT tinyxml2_FOUND)
  message("tinyxml2 not found. Downloading...")
  include(FetchContent)
  FetchContent_Declare(tinyxml2
    GIT_REPOSITORY    https://github.com/leethomason/tinyxml2
    GIT_TAG           master
    )
  FetchContent_GetProperties(tinyxml2)
  if(NOT tinyxml2_POPULATED)
    FetchContent_Populate(tinyxml2)
    SET(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    SET(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    add_subdirectory(${tinyxml2_SOURCE_DIR} ${tinyxml2_BINARY_DIR})
  endif()
endif()
