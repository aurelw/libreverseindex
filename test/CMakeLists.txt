include_directories ("../lib/")

set (test_simple_index_files test_simple_index.cpp)
add_executable (test_simple_index ${test_simple_index_files})
target_link_libraries (test_simple_index reverseindex)

