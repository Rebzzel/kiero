<h1 align="center">kiero</h1>
<p align="center">
  <a href="https://github.com/Rebzzel/kiero/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/Rebzzel/kiero.svg?style=flat-square"/>
  </a>
  <a href="https://github.com/Rebzzel/kiero/stargazers">
    <img src="https://img.shields.io/github/stars/Rebzzel/kiero.svg?style=flat-square"/>
  </a>
  <br>
  Universal graphical hook for a D3D9-D3D12, OpenGL and Vulkan based games
</p>

### Requirement
[Windows SDK](https://www.microsoft.com/en-us/download/details.aspx?id=8279) (For D3D9/D3D10/D3D11/OpenGL hook)

[DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=4064) (For D3D9/D3D10/D3D11 hook)

[Vulkan SDK](https://www.lunarg.com/vulkan-sdk) (For Vulkan hook)

[MinHook](https://github.com/TsudaKageyu/minhook) (For kiero::bind function)

### Example
To start, go to the kiero.h and select the desired hooks
```C++
// Example for D3D9 hook
#define KIERO_INCLUDE_D3D9   1 // 1 if you need D3D9 hook
#define KIERO_INCLUDE_D3D10  0 // 1 if you need D3D10 hook
#define KIERO_INCLUDE_D3D11  0 // 1 if you need D3D11 hook
#define KIERO_INCLUDE_D3D12  0 // 1 if you need D3D12 hook
#define KIERO_INCLUDE_OPENGL 0 // 1 if you need OpenGL hook
#define KIERO_INCLUDE_VULKAN 0 // 1 if you need Vulkan hook
```

Then proceed to the main work
```C++
// Example for D3D9 hook

// Include required libraries
#include "kiero.h"
#include <d3d9.h>
#include <Windows.h>

// Create the type of function that we will hook
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
static EndScene oEndScene = NULL;

// Declare the detour function
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
  // ... Your magic here ...
  
  // static bool init = false;
  // if (!init)
  // {
  //  MessageBox(0, "Boom! It's works!", "Kiero", MB_OK);
  //  init = true;
  // }
  
  return oEndScene(pDevice);
}

int kieroExampleThread()
{
  if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
  // or
  if (kiero::init(kiero::RenderType::Auto) == kiero::Status::Success)
  {
    // define KIERO_USE_MINHOOK must be 1
    // the index of the required function can be found in the METHODSTABLE.txt
    kiero::bind(42, (void**)&oEndScene, hkEndScene);
    
    // If you just need to get the function address you can use the kiero::getMethodsTable function
    oEndScene = (EndScene)kiero::getMethodsTable()[42];
  }

  return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
  DisableThreadLibraryCalls(hInstance);

  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)kieroExampleThread, NULL, 0, NULL);
      break;
  }

  return TRUE;
}

```

### License
```
MIT License

Copyright (c) 2014-2021 Rebzzel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
