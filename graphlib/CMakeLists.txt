add_library(mylib STATIC graphlib.c)

add_executable(test test.c)
target_link_libraries(test mylib)

add_subdirectory(cgraph)
target_link_libraries(test cgraph)