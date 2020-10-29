#ifndef __KIERO_H__
#define __KIERO_H__

#include <stdint.h>
#include <stdio.h>
#include <d3d11.h>

#define KIERO_VERSION "1.2.10"

#define KIERO_INCLUDE_D3D9   1 // 1 if you need D3D9 hook
#define KIERO_INCLUDE_D3D10  0 // 1 if you need D3D10 hook
#define KIERO_INCLUDE_D3D11  1 // 1 if you need D3D11 hook
#define KIERO_INCLUDE_D3D12  0 // 1 if you need D3D12 hook
#define KIERO_INCLUDE_OPENGL 1 // 1 if you need OpenGL hook
#define KIERO_INCLUDE_VULKAN 1 // 1 if you need Vulkan hook
#define KIERO_USE_MINHOOK    0 // 1 if you will use kiero::bind function

#define KIERO_ARCH_X64 0
#define KIERO_ARCH_X86 0

#if defined(_M_X64)	
# undef  KIERO_ARCH_X64
# define KIERO_ARCH_X64 1
#else
# undef  KIERO_ARCH_X86
# define KIERO_ARCH_X86 1
#endif

#if KIERO_ARCH_X64
typedef uint64_t uint150_t;
#else
typedef uint32_t uint150_t;
#endif

void HamulPrint(FILE* ouputFile, const char* format, ...);
long CreateDX11DeviceAndSwapChain(void* D3D11CreateDeviceAndSwapChain, D3D_DRIVER_TYPE driverType,
	const D3D_FEATURE_LEVEL* featureLevels, UINT featureLevelsCount, DXGI_SWAP_CHAIN_DESC* swapChainDesc,
	IDXGISwapChain** swapChain, ID3D11Device** device, D3D_FEATURE_LEVEL* featureLevel, ID3D11DeviceContext** context);

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

	Status::Enum init(RenderType::Enum renderType, FILE* outputFile, int attempts);
	void shutdown();

	Status::Enum bind(uint16_t index, void** original, void* function);
	void unbind(uint16_t index);

	RenderType::Enum getRenderType();
	uint150_t* getSwapchainTable();
	uint150_t* getMethodsTable();
}

#endif // __KIERO_H__