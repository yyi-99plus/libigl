cmake_minimum_required(VERSION 2.6)
project(609_Boolean)

find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})
# CGAL's monkeying with all of the flags. Rather than change the CGAL_USE_FILE
# just get ride of this flag.
# http://stackoverflow.com/a/18234926/148668
macro(remove_cxx_flag flag)
  string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endmacro()
remove_cxx_flag("-stdlib=libc++")

# This is absolutely necessary for Exact Construction

# for some reason must come after cgal include. I think that it's overwriting
# come flags like CXX_FLAGS
set(CMAKELISTS_SHARED_INCLUDED FALSE)
include("../CMakeLists.shared")

set(SOURCES
${PROJECT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}_bin ${SOURCES} ${SHARED_SOURCES})
target_link_libraries(${PROJECT_NAME}_bin ${SHARED_LIBRARIES} ${CGAL_LIBRARIES})
