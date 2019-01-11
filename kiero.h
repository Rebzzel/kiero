#ifndef __KIERO_H__
#define __KIERO_H__

#include <stdint.h>
#include <string.h>

#define KIERO_VERSION "1.1.8"

#define KIERO_USE_MINHOOK

#define KIERO_ARCH_X64 0
#define KIERO_ARCH_X86 0

#if defined(_M_X64)	
# undef  KIERO_ARCH_X64
# define KIERO_ARCH_X64 1
#else
# undef  KIERO_ARCH_X86
# define KIERO_ARCH_X86 1
#endif

#ifdef _UNICODE
# define KIERO_TEXT(text) L##text
#else
# define KIERO_TEXT(text) text
#endif

#define KIERO_ARRAY_SIZE(arr) ((size_t)(sizeof(arr)/sizeof(arr[0])))

namespace kiero
{
	struct Status
	{
		enum Enum
		{
			UnknownError = -1,
			NotSupportedError = -2,
			ModuleNotFoundError = -3,

			Success = 0,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,

			D3D9,   // Implemented
			D3D10,  // Implemented
			D3D11,  // Implemented
			D3D12,  // Implemented

			OpenGL, // Implemented
			Vulkan  // Implemented
		};
	};

	Status::Enum init(RenderType::Enum renderType);

	void shutdown();

	RenderType::Enum getRenderType();

#if KIERO_ARCH_X64
	uint64_t* getMethodsTable();
#else
	uint32_t* getMethodsTable();
#endif

	void bind(uint16_t index, void** original, void* function);
}

#endif // __KIERO_H__