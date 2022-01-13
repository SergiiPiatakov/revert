set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)


include (ExternalProject)

ExternalProject_Add (
    googletest
    GIT_REPOSITORY  "https://github.com/google/googletest.git"
    GIT_TAG         "release-1.11.0"
    CMAKE_ARGS      "-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR      "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    BINARY_DIR      "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)
set_target_properties (googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)

set (GTEST_ROOT             "${CMAKE_CURRENT_BINARY_DIR}/googletest")
set (GTEST_FOUND TRUE)
set (GTEST_INCLUDE_DIRS     "${GTEST_ROOT}/googletest/include")
set (GTEST_LIBRARIES        "${GTEST_ROOT}/lib/libgtest.a")
set (GTEST_MAIN_LIBRARIES   "${GTEST_ROOT}/lib/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES   ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})


set (revert_test_SOURCES
    ${PROJECT_SOURCE_DIR}/test/revert_test.cpp
)

add_executable (revert_test ${revert_test_SOURCES})

set_target_properties (revert_test
    PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
)

set_target_properties (revert_test
    PROPERTIES LINK_FLAGS "-fprofile-arcs -ftest-coverage"
)

target_include_directories (revert_test
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries (revert_test
    PRIVATE ${GTEST_BOTH_LIBRARIES}
    PRIVATE Threads::Threads
    PRIVATE Revert::Revert
)


# Test coverage report.
set (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
set (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
add_custom_command (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/test -o ${Coverage_REPORT}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/revert.h' -o ${Coverage_REPORT}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR}
    DEPENDS revert_test
)
add_custom_target (coverage DEPENDS ${Coverage_REPORT})


add_dependencies (revert_test googletest)

enable_testing ()
add_test (revert_test revert_test)
