include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
)
# Keep MSVC runtime settings consistent with the parent project.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(sjb_tests
    sjb_test.cpp
)
target_link_libraries(sjb_tests PRIVATE sjb::core GTest::gtest_main)
sjb_set_warnings(sjb_tests)

include(GoogleTest)
gtest_discover_tests(sjb_tests)
