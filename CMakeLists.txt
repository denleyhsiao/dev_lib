cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(dev_lib)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
add_compile_options(-std=c++17)

enable_testing()
find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem thread date_time)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include
    ${Boost_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIR}
)

target_sources(${PROJECT_NAME}
  PRIVATE
    src/decimal_comparer.cpp
    src/dev_helper.cpp
    src/boost_helper.cpp
    src/math_helper.cpp
    src/linux_os_helper.cpp
    src/log/console_log.cpp
    src/comm/comm.cpp
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

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
)

add_executable(${PROJECT_NAME}-test
  test/test_decimal_comparer.cpp
  test/test_dev_helper.cpp
  test/test_boost_helper.cpp
  test/main.cpp
)

target_link_libraries(${PROJECT_NAME}-test
  PRIVATE
  ${PROJECT_NAME}
  ${GTEST_BOTH_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME}-test DESTINATION test)
