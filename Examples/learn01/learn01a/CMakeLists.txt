message(STATUS "Look Here: " ${CMAKE_CURRENT_SOURCE_DIR}/../learn01b/myheader.hpp)

set(header_file ${CMAKE_CURRENT_SOURCE_DIR}/../learn01b/myheader.hpp )
# add_library(lib01 )
add_executable(learn01cmake learn01_1_cmake.cpp ${header_file})
# add_executable(learn01 learn01.cpp)
target_include_directories(learn01cmake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries(learn01cmake ${QL_LINK_LIBRARY})
