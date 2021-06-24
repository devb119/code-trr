
add_executable(test test.c)

add_subdirectory(cgraph)
target_link_libraries(test cgraph)