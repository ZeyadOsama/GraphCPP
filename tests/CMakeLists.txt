set(TESTFILES test_main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/concrete)

enable_testing()
add_executable(system-tests ${TESTFILES})
target_link_libraries(system-tests GraphCPP)
