cmake_minimum_required(VERSION 3.5)

project(task5)

set(CMAKE_CXX_STANDARD 11)

# Find OpenCV, you may need to set OpenCV_DIR variable 
# to root build or install path of OpenCV
find_package(OpenCV REQUIRED)

add_executable(task5 
  task5.cpp
)

# Link against OpenCV libraries
target_link_libraries(task5 ${OpenCV_LIBS}) 

# Add include directories
target_include_directories(task5 PUBLIC 
  ${OpenCV_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)
