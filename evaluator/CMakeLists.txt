cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(idn_evaluator CXX)

option(ENABLE_IDN_EVALUATOR_TESTING "Enables IDN::Evaluator testing" ON)

file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(idn::evaluator ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    idn::common
)

add_subdirectory(tests)