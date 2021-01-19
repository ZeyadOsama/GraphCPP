set(TESTFILES test_main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/concrete)

enable_testing()
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(system-tests ${TESTFILES})
