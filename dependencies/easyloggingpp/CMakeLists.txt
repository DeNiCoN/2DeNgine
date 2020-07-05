  include(FetchContent)
  FetchContent_Declare(easyloggingpp
    GIT_REPOSITORY    https://github.com/amrayn/easyloggingpp
    GIT_TAG           master
    )
  FetchContent_GetProperties(easyloggingpp)
  if(NOT easyloggingpp_POPULATED)
    message("Populating easyloggingpp")
    FetchContent_Populate(easyloggingpp)
    add_subdirectory(${easyloggingpp_SOURCE_DIR} ${easyloggingpp_BINARY_DIR})
    add_library(easyloggingpp ${easyloggingpp_SOURCE_DIR}/src/easylogging++.cc)
    target_include_directories(easyloggingpp PUBLIC
      ${easyloggingpp_SOURCE_DIR}/src
      )
  endif()
