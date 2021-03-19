#include "../../../kiero.h"

#if KIERO_INCLUDE_D3D9

#include "d3d9_impl.h"
#include <d3d9.h>
#include <assert.h>

#include "win32_impl.h"

#include "../imgui/imgui.h"
#include "../imgui/examples/imgui_impl_win32.h"
#include "../imgui/examples/imgui_impl_dx9.h"

typedef long(__stdcall* Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
static Reset oReset = NULL;

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
static EndScene oEndScene = NULL;

long __stdcall hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	long result = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	static bool init = false;

	if (!init)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);

		impl::win32::init(params.hFocusWindow);

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(params.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);

		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	impl::showExampleWindow("D3D9");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}

void impl::d3d9::init()
{
	assert(kiero::bind(16, (void**)&oReset, hkReset) == kiero::Status::Success);
	assert(kiero::bind(42, (void**)&oEndScene, hkEndScene) == kiero::Status::Success);
}

#endif // KIERO_INCLUDE_D3D9