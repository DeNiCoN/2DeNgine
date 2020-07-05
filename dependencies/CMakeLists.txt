add_subdirectory(tinyxml2)
add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(easyloggingpp)

find_package(OpenGL REQUIRED)

add_library(dependencies INTERFACE)
target_link_libraries(dependencies
    INTERFACE glad
    INTERFACE glfw
    INTERFACE tinyxml2
    INTERFACE OpenGL::GL
    INTERFACE easyloggingpp
    )
