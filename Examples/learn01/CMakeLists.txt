add_subdirectory(learn01a)
add_executable(learn01 learn01.cpp)

# message(STATUS "Look Here: " ${CMAKE_CURRENT_SOURCE_DIR}/../learn02/myheader.hpp)

# set(header_file ${CMAKE_CURRENT_SOURCE_DIR}/../learn02/myheader.hpp )
# add_executable(learn01 learn01.cpp ${header_file} "learn01a/learn01_1_cmake.cpp")
# target_include_directories(learn01 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(learn01 ${QL_LINK_LIBRARY})
