project(Kiero LANGUAGES CXX)

option(DYNAMIC "If Kiero should be linked dynamically or not" OFF)
if(DYNAMIC)
add_library(Kiero SHARED)
else()
add_library(Kiero STATIC)
endif()

option(KIERO_INCLUDE_D3D9 "if you need D3D9 hook" OFF)
if(KIERO_INCLUDE_D3D9)
add_compile_definitions(KIERO_INCLUDE_D3D9 1)
endif()

option(KIERO_INCLUDE_D3D10 "if you need D3D10 hook" OFF)
if(KIERO_INCLUDE_D3D10)
add_compile_definitions(KIERO_INCLUDE_D3D10 1)
endif()

option(KIERO_INCLUDE_D3D11 "if you need D3D11 hook" OFF)
if(KIERO_INCLUDE_D3D11)
add_compile_definitions(KIERO_INCLUDE_D3D11 1)
endif()

option(KIERO_INCLUDE_D3D12 "if you need D3D12 hook" OFF)
if(KIERO_INCLUDE_D3D12)
add_compile_definitions(KIERO_INCLUDE_D3D12 1)
endif()

option(KIERO_INCLUDE_OPENGL "if you need OpenGL hook" OFF)
if(KIERO_INCLUDE_OPENGL)
add_compile_definitions(KIERO_INCLUDE_OPENGL 1)
endif()

option(KIERO_INCLUDE_VULKAN "if you need Vulkan hook" OFF)
if(KIERO_INCLUDE_VULKAN)
add_compile_definitions(KIERO_INCLUDE_VULKAN 1)
endif()

option(KIERO_USE_MINHOOK "if you will use kiero::bind function" OFF)
if(KIERO_USE_MINHOOK)
add_compile_definitions(KIERO_USE_MINHOOK 1)
endif()

option(KIERO_USE_POLYHOOK "if you will use kiero::bind function" OFF)
if(KIERO_USE_POLYHOOK)
add_compile_definitions(KIERO_USE_POLYHOOK 1)
endif()

target_sources(Kiero PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/kiero.cpp"
)

target_include_directories(Kiero INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
if(KIERO_USE_POLYHOOK)
target_link_libraries(Kiero PRIVATE PolyHook_2)
elseif(KIERO_USE_MINHOOK)
target_link_libraries(Kiero PRIVATE minhook)
endif()