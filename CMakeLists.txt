cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project (GameDevelopmentProject)

set(PROJECT_SOURCE_FILES
  source/main.cpp
  source/Game.h
  source/Game.cpp
)

include_directories(engine/thirdparty/glew/include)

# add the application
include_directories(source)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} "source/Game.h")

add_subdirectory(engine "${CMAKE_CURRENT_BINARY_DIR}/engine_build")

#adding engine source directory to include path
include_directories(engine/source)

# link engine library
target_link_libraries(${PROJECT_NAME} 
    Engine
)


