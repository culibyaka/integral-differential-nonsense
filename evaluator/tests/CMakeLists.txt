cmake_minimum_required(VERSION 3.26)
project(idn_evaluator_tests LANGUAGES CXX)

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/../src
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    idn::common
    idn::evaluator
    gtest
    gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})