cmake_minimum_required(VERSION 3.25)
project(idn LANGUAGES CXX)

option(IDN_ENABLE_TESTING "Enables all tests" ON)

include(cmake/SetupCompiler.cmake)
include(cmake/SetupVenv.cmake)
setup_venv(REQUIREMENTS "${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt")
include(cmake/SetupVissuite.cmake)
include(cmake/SetupGoogleTest.cmake)

add_subdirectory(common)
add_subdirectory(solver)
add_subdirectory(evaluator)
add_subdirectory(cli)
