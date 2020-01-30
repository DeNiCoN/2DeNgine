add_subdirectory(tinyxml2)

add_library(dependencies INTERFACE)
target_link_libraries(dependencies
	INTERFACE tinyxml2
	)

