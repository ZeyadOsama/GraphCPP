# add the example executable, linked with the GraphCPP library
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(GraphCPP_Example end-to-end/main.cpp)