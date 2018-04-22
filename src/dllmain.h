#ifndef _DLLMAIN_H_
#define _DLLMAIN_H_

#define DLL_API extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
);


#endif // !_DLLMAIN_H_
