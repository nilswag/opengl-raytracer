cmake_minimum_required(VERSION 3.10)
project(platformer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)
add_subdirectory(third_party/glm)

file(GLOB_RECURSE SOURCES src/*.cpp)

file(CREATE_LINK
	${CMAKE_SOURCE_DIR}/resources
	${CMAKE_BINARY_DIR}/resources
	SYMBOLIC
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PRIVATE src/
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE glfw
	PRIVATE glad
	PRIVATE glm
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
)
