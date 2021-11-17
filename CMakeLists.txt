cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(dev_lib)

option(DEVLIB_BUILD_TESTS "Build DevLib's unit tests" ON)
find_package(Boost REQUIRED COMPONENTS filesystem thread date_time)

add_library(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME}
  PUBLIC
    cxx_std_11
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
    ${Boost_INCLUDE_DIRS}
)
target_sources(${PROJECT_NAME}
  PRIVATE
    src/decimal_comparer.cpp
    src/dev_helper.cpp
    src/boost_helper.cpp
    src/math_helper.cpp
    src/log/console_log.cpp
    src/comm/comm.cpp
    src/comm/serial_port.cpp
    src/comm/mock_comm.cpp
    src/message/timer_message.cpp
    src/message/serial_port_message.cpp
    src/message/boost_timers.cpp
    src/message/boost_serial_ports.cpp
    src/message/boost_serial_port.cpp
    src/message/boost_message_loop.cpp
    src/message/functor_message_loop.cpp
    src/message/message_loop_thread.cpp
    src/message/message_loops.cpp
)
if(WIN32)
  target_sources(${PROJECT_NAME}
    PRIVATE
      src/platform/win32/os_helper.cpp
  )
else()
  target_sources(${PROJECT_NAME}
    PRIVATE
      src/platform/posix/os_helper.cpp
  )
endif()
target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(DEVLIB_BUILD_TESTS)
  set(PROJECT_TEST_NAME "${PROJECT_NAME}-test")
  find_package(GTest REQUIRED)
  add_executable(${PROJECT_TEST_NAME}
    test/test_decimal_comparer.cpp
    test/test_dev_helper.cpp
    test/test_boost_helper.cpp
    test/main.cpp
  )
  target_link_libraries(${PROJECT_TEST_NAME}
    PRIVATE
    ${PROJECT_NAME}
    ${GTEST_BOTH_LIBRARIES}
  )
  include(CTest)
  enable_testing()
  add_test(
    NAME ${PROJECT_TEST_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_TEST_NAME}>
  )
  install(TARGETS ${PROJECT_TEST_NAME} DESTINATION test)
endif()
