#ifndef __KIERO_H__
#define __KIERO_H__

#include <stdint.h>

#define KIERO_VERSION "1.2.12-extended"

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
	void unbind(uint16_t index);

	RenderType::Enum getRenderType();
	uint150_t* getMethodsTable();
}

#endif // __KIERO_H__