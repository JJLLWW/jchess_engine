find_package(GTest CONFIG REQUIRED)
add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
add_test(NAME main_test COMMAND tests)