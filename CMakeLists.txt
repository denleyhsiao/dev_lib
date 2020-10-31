cmake_minimum_required(VERSION 2.8.3)
project(dev_lib)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
add_compile_options(-std=c++17)

enable_testing()
find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread date_time)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIR}
)

add_library(${PROJECT_NAME}
  src/decimal_comparer.cpp
  src/deadline_timer.cpp
  src/dev_helper.cpp
  src/boost_helper.cpp
  src/math_helper.cpp
  src/linux_os_helper.cpp
  src/log/console_log.cpp
  src/comm/comm.cpp
  src/comm/mock_comm.cpp
  src/comm/serial_port.cpp
  src/message_loop/message.cpp
  src/message_loop/boost_message_loop.cpp
  src/message_loop/functor_message_loop.cpp
  src/message_loop/message_loops.cpp
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
