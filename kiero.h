#pragma once

#include <Windows.h>
#include <stdint.h>

#define KIERO_VERSION "1.2.12"

#define KIERO_INCLUDE_D3D9   0 // 1 if you need D3D9 hook
#define KIERO_INCLUDE_D3D10  0 // 1 if you need D3D10 hook
#define KIERO_INCLUDE_D3D11  0 // 1 if you need D3D11 hook
#define KIERO_INCLUDE_D3D12  0 // 1 if you need D3D12 hook
#define KIERO_INCLUDE_OPENGL 0 // 1 if you need OpenGL hook
#define KIERO_INCLUDE_VULKAN 0 // 1 if you need Vulkan hook
#define KIERO_USE_MINHOOK    0 // 1 if you will use kiero::bind function

namespace kiero
{
	struct Status
	{
		enum Enum
		{
			UnknownError = -1,
			NotSupportedError = -2,
			ModuleNotFoundError = -3,
			AlreadyInitializedError = -4,
			NotInitializedError = -5,
			Success = 0,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,
			D3D9,
			D3D10,
			D3D11,
			D3D12,
			OpenGL,
			Vulkan,
			Auto
		};
	};

	Status::Enum init(RenderType::Enum renderType);
	void shutdown();

	Status::Enum bind(uint16_t index, void** original, void* function);
	Status::Enum bindApi(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal);
	void unbind(uint16_t index);

	RenderType::Enum getRenderType();
	uintptr_t* getMethodsTable();
}