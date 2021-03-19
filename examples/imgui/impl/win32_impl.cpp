#include "../../../kiero.h"

#include "win32_impl.h"
#include <Windows.h>

#include "../imgui/imgui.h"
#include "../imgui/examples/imgui_impl_win32.h"

static WNDPROC oWndProc = NULL;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK hkWindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
		return 1L;	
	return ::CallWindowProcA(oWndProc, hwnd, uMsg, wParam, lParam);
}

void impl::win32::init(void* hwnd)
{
	oWndProc = (WNDPROC)::SetWindowLongPtr((HWND)hwnd, GWLP_WNDPROC, (LONG)hkWindowProc);
}