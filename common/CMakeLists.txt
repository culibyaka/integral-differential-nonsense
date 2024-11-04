project(idn_common CXX)

file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(idn::common ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
