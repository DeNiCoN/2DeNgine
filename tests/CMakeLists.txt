CMAKE_MINIMUM_REQUIRED(VERSION 3.12.1)

project(2DeNgine_tests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  )

FetchContent_MakeAvailable(googletest)

include(GoogleTest)
add_executable(Tests
  "HashedStringTest.cpp"
  )
target_include_directories(Tests
  PUBLIC "../src"
  )
target_link_libraries(Tests gtest_main)
gtest_discover_tests(Tests)
