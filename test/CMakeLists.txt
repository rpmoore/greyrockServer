find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()

add_executable(socketTest socketTest.cxx)

target_link_libraries(socketTest gr_netSock ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(socketTest ${CMAKE_CURRENT_BINARY_DIR}/socketTest)
