cmake_minimum_required (VERSION 2.6)
project (SetDatabase)

add_library(TableHandle tablejhandler.cpp)

include_directories ("${PROJECT_SOURCE_DIR}")
add_subdirectory (MathFunctions) 
 
# add the executable
add_executable (setDatabase inputHandler.cpp)
target_link_libraries (setDatabase TableHandle)