cmake_minimum_required(VERSION 3.20)
project(vulkan-leren)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glm)

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

file(GLOB_RECURSE SHADERS
	resources/shaders/*.vert
	resources/shaders/*.frag
)

set(SPIRV_SHADERS "")
foreach(SHADER ${SHADERS})
	get_filename_component(FILE_NAME ${SHADER} NAME)
	set(SPIRV ${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}.spv)
	
	list(APPEND SPIRV_SHADERS ${SPIRV})

	add_custom_command(
		OUTPUT ${SPIRV}
		COMMAND Vulkan::glslc ${SHADER} -o ${SPIRV}
		DEPENDS ${SHADER}
		COMMENT "Compiling shader ${FILE_NAME}"
	)
endforeach()

add_custom_target(Shaders
	DEPENDS ${SPIRV_SHADERS}
)

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} Shaders)

target_include_directories(${PROJECT_NAME}
	PRIVATE src/
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE glfw
	PRIVATE glm
	PRIVATE Vulkan::Vulkan
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
)
