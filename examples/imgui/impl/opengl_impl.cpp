#include "kiero.h"

#if KIERO_INCLUDE_OPENGL

#include "opengl_impl.h"
#include <gl/GL.h>

#include "win32_impl.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/backends/imgui_impl_opengl3.h"

typedef bool(__stdcall* wglSwapBuffers)(HDC);
static wglSwapBuffers oWglSwapBuffers = NULL;

bool __stdcall hkWglSwapBuffers(HDC hdc)
{
	static bool init = false;

	if (!init)
	{
		HWND hWindow = WindowFromDC(hdc);

		impl::win32::init(hWindow);

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWindow);
		ImGui_ImplOpenGL3_Init();

		init = true;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	impl::showExampleWindow("OpenGL");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return oWglSwapBuffers(hdc);
}

void impl::opengl::init()
{
	assert(kiero::bindApi(L"OpenGL32.dll", "wglSwapBuffers", hkWglSwapBuffers, (void**)&oWglSwapBuffers) == kiero::Status::Success);
}

#endif // KIERO_INCLUDE_OPENGL