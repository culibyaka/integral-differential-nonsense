project(idn-cli LANGUAGES CXX)

file(GLOB_RECURSE CXX_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME}
	${CXX_SOURCES}
	${ASM_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
	idn-parser
	idn-solver)
