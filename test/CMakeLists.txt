# create an exe file for testing, adding the library to it for test. Nothing special here. 
add_executable(test_cpp "")
target_sources(test_cpp
    PRIVATE
    test.cpp
)
target_link_libraries(test_cpp gtest_main)

add_test(
    NAME test_cpp
    COMMAND $<TARGET_FILE:test_cpp>)