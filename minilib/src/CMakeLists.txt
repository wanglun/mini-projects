set(MINILIB_SRCS
    ${PROJECT_SOURCE_DIR}/src/minilib/dummy.cpp
    )
add_library(minilib STATIC ${MINILIB_SRCS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/minilib/
    DESTINATION ${PROJECT_BINARY_DIR}/output/include/minilib/
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
    )

if (BUILD_UNIT_TESTS)
    set(MINILIB_TEST_SRCS
        ${PROJECT_SOURCE_DIR}/src/minilib/blocking_queue_test.cpp
        ${PROJECT_SOURCE_DIR}/src/minilib/priority_queue_test.cpp
        )

    find_path(GTEST_INCLUDE_PATH gtest/gtest.h)
    find_library(GTEST_LIBRARY NAMES libgtest.a)
    find_library(GTEST_MAIN_LIBRARY NAMES libgtest_main.a)
    if((NOT GTEST_INCLUDE_PATH) OR (NOT GTEST_LIBRARY) OR (NOT GTEST_MAIN_LIBRARY))
        message(FATAL_ERROR "Fail to find gtest")
    endif()
    include_directories(${GTEST_INCLUDE_PATH})

    set(CMAKE_CXX_FLAGS "${CMAKE_CPP_FLAGS} -Dprivate=public")
    add_executable(test_minilib ${MINILIB_TEST_SRCS})
    target_link_libraries(test_minilib
        minilib
        ${GTEST_MAIN_LIBRARY}
        ${GTEST_LIBRARY}
        ${LIBS}
        )
endif()
