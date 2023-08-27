cmake_minimum_required(VERSION 3.22)
project(cpp_samples)

set(CMAKE_CXX_STANDARD 20)


# cmake -D USER_STATIC_LIBRARY=ON
option(ENABLE_UNIT_TEST  "enables the unit tests" ON)

if(ENABLE_UNIT_TEST)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.0
    )

    FetchContent_GetProperties(googletest)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        add_subdirectory(
            ${googletest_SOURCE_DIR}
            ${googletest_BINARY_DIR}
        )
    endif()
endif()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
