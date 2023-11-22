cmake_minimum_required(VERSION 3.12)

project(SchoolProject)

set(PROJECT_NAME SchoolLib)

set(PUBLIC_INCLUDES
	core/includes/UIModule.hpp
	core/includes/Application.hpp
	core/includes/Log.hpp
	core/includes/Window.hpp
	core/includes/Event.hpp
	main/includes/Interface.hpp
	models/includes/Gravity.hpp
)

set(PRIVATE_SOURCES
	core/src/UIModule.cpp
	core/src/Application.cpp
	core/src/Window.cpp
	main/src/Interface.cpp
	models/src/Gravity.cpp
)

set(MODEL_INCLUDES
	
)

set(MODEL_SOURCES
	
)

set(ALL_SOURCES
	${PUBLIC_INCLUDES}
	${MODEL_INCLUDES}
	${PRIVATE_SOURCES}
	${MODEL_SOURCES}
)



add_library(${PROJECT_NAME} STATIC
	${ALL_SOURCES}
)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
	${ALL_SOURCES}
)

add_executable(SchoolProject
	main/main.cpp
)

target_link_libraries(SchoolProject SchoolLib)

target_include_directories(${PROJECT_NAME} PUBLIC core/includes)
target_include_directories(${PROJECT_NAME} PRIVATE core/src)
target_include_directories(${PROJECT_NAME} PUBLIC models/includes)
target_include_directories(${PROJECT_NAME} PRIVATE models/src)
target_include_directories(${PROJECT_NAME} PUBLIC main/includes)
target_include_directories(${PROJECT_NAME} PRIVATE main/src)


target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)


set(IMGUI_INCLUDES
	external/imgui/imgui.h
	external/imgui/backends/imgui_impl_glfw.h
	external/imgui/backends/imgui_impl_opengl3.h
	
	external/implot/implot.h
	external/implot/implot_internal.h
)

set(IMGUI_SOURCES
	external/imgui/imgui.cpp
	external/imgui/backends/imgui_impl_glfw.cpp
	external/imgui/backends/imgui_impl_opengl3.cpp
	external/imgui/imgui_demo.cpp
	external/imgui/imgui_draw.cpp
	external/imgui/imgui_widgets.cpp
	external/imgui/imgui_tables.cpp
	
	external/implot/implot.cpp
	external/implot/implot_demo.cpp
	external/implot/implot_items.cpp	
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC external)
target_include_directories(ImGui PUBLIC external/imgui)
target_include_directories(ImGui PUBLIC external/implot)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)