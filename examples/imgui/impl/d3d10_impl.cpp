#include "../../../kiero.h"

#if KIERO_INCLUDE_D3D10

#include "d3d10_impl.h"
#include <d3d10.h>
#include <assert.h>

#include "win32_impl.h"

#include "../imgui/imgui.h"
#include "../imgui/examples/imgui_impl_win32.h"
#include "../imgui/examples/imgui_impl_dx10.h"

typedef long(__stdcall* Present)(IDXGISwapChain*, UINT, UINT);
static Present oPresent = NULL;

long __stdcall hkPresent10(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static bool init = false;

	if (!init)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		pSwapChain->GetDesc(&desc);

		ID3D10Device* device;
		pSwapChain->GetDevice(__uuidof(ID3D10Device), (void**)&device);

		impl::win32::init(desc.OutputWindow);

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(desc.OutputWindow);
		ImGui_ImplDX10_Init(device);

		init = true;
	}

	ImGui_ImplDX10_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	impl::showExampleWindow("D3D10");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void impl::d3d10::init()
{
	assert(kiero::bind(8, (void**)&oPresent, hkPresent10) == kiero::Status::Success);
}

#endif // KIERO_INCLUDE_D3D10