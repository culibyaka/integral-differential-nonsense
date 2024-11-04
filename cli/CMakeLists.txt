project(idn_cli LANGUAGES CXX)

file(GLOB_RECURSE CXX_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME}
	${CXX_SOURCES}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
	idn::evaluator
	idn::solver
	idn::common)
