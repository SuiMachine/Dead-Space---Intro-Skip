#include <Windows.h>
#include <Psapi.h>
#include <string>
#include "HookFunctions.h"

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HMODULE baseModule = GetModuleHandle(NULL);
		char baseModuleName[MAX_PATH];
		GetModuleFileName(baseModule, baseModuleName, sizeof(baseModuleName));
		int indexOfLastPathNode = StrEndsWith(baseModuleName, sizeof(baseModuleName), '\\') + 1;
		char exeName[MAX_PATH];
		strcpy_s(exeName, baseModuleName + indexOfLastPathNode);
		StrToLower(exeName, sizeof(exeName));

		if (std::strstr((const char*)&exeName, "dead space.exe") || std::strstr((const char*)&exeName, "dead_space.exe") || std::strstr((const char*)&exeName, "dead space.exe.unpacked.exe"))
		{
			MODULEINFO moduleInfo;
			GetModuleInformation(GetCurrentProcess(), baseModule, &moduleInfo, sizeof(moduleInfo));
			if (moduleInfo.SizeOfImage == 12009472) //Steam
			{
				OverrideCharArray(0x00C7B13C, "XCENTKOWSK_C78C369_F71988A_v3", 29);
			}
			else
			{

				std::string messageBoxText = "Unknown module size: " + std::to_string(moduleInfo.SizeOfImage) + ".\nNothing was overriden!";
				MessageBox(NULL, messageBoxText.c_str(), "Warning", MB_ICONWARNING | MB_OK);

			}
		}
	}
	else if (reason == DLL_PROCESS_DETACH) {
	}
	return TRUE;
}