cmake_minimum_required (VERSION 3.1)
project (recito)

add_executable (recito src/common.cpp src/main/main.cpp src/main/Control.cpp src/main/ControlFactory.cpp src/main/Database.cpp src/main/Display.cpp src/main/Fragment.cpp src/main/MainLoop.cpp src/main/Record.cpp src/main/View.cpp src/main/ViewFactory.cpp src/main/Widget.cpp src/main/CommandLineParser.cpp)
add_library (algorithm SHARED src/algorithm/recito_algorithm.cpp)
target_link_libraries (recito algorithm)

# uncomment to build test
# add_executable (recito_test test/test.cpp src/common.cpp src/algorithm/recito_algorithm.cpp src/main/Control.cpp src/main/ControlFactory.cpp src/main/Database.cpp src/main/Display.cpp src/main/Fragment.cpp src/main/MainLoop.cpp src/main/Record.cpp src/main/View.cpp src/main/ViewFactory.cpp src/main/Widget.cpp src/main/CommandLineParser.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
