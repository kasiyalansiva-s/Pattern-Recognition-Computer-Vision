cmake_minimum_required(VERSION 3.5)

project(task1)

set(CMAKE_CXX_STANDARD 14)

# Find OpenCV, you may need to set OpenCV_DIR variable 
# to root build or install path of OpenCV
find_package(OpenCV REQUIRED)

add_executable(task1 
  main.cpp
)

# Link against OpenCV libraries
target_link_libraries(task1 ${OpenCV_LIBS}) 

# Add include directories
target_include_directories(task1 PUBLIC 
  ${OpenCV_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)
