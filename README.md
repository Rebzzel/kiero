<h1 align="center">kiero</h1>
<p align="center">
  <a href="https://github.com/Rebzzel/kiero/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/Rebzzel/kiero.svg?style=flat-square"/>
  </a>  
  <a href="https://github.com/Rebzzel/kiero/stargazers">
    <img src="https://img.shields.io/github/stars/Rebzzel/kiero.svg?style=flat-square"/>
  </a>
  <br>
  Universal graphical hook for a D3D9-D3D11<strike>12</strike>, OpenGL <strike>and Vulcan</strike> based games
</p>

### Requirement
![Windows SDK](https://www.microsoft.com/en-us/download/details.aspx?id=8279)

### Example
Becouse `bind` function in development, we use ![MinHook](https://github.com/TsudaKageyu/minhook)
```C++
#include "kiero.h"
#include <d3d9.h>
#include <MinHook.h>
#include <Windows.h>

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE);
EndScene oEndScene = NULL;

long __stdcall hkEndScene(LPDIRECT3DDEVICE pDevice)
{
  return oEndScene(pDevice);
}

int kieroExampleThread()
{
  if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
  {
    MH_Initialize();
    
    MH_CreateHook((LPVOID)kiero::getMethodsTable()[42], hkEndScene, (LPVOID*)&oEndScene);
    MH_EnableHook((LPVOID)kiero::getMethodsTable()[42]);
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

### Contributors
![Rebzzel](https://github.com/Rebzzel)

### License
```
MIT License

Copyright (c) 2014-2018 Rebzzel

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
