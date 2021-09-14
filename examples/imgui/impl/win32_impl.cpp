#include "../../../kiero.h"

#include "win32_impl.h"
#include <Windows.h>

#include "../imgui/imgui.h"
#include "../imgui/examples/imgui_impl_win32.h"

static WNDPROC oWndProc = NULL;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK hkWindowProc(HWND hwnd, INT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	return ::CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

void impl::win32::init(void* hwnd)
{
	if (oWndProc == NULL)
		oWndProc = (WNDPROC)::SetWindowLongPtr((HWND)hwnd, GWLP_WNDPROC, (LONG_PTR)hkWindowProc);
}