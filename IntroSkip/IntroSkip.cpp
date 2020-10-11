#include <Windows.h>
#include <Psapi.h>
#include <string>
#include <regex>
#include "HookFunctions.h"

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		HMODULE baseModule = GetModuleHandle(NULL);
		WCHAR baseModuleName[MAX_PATH];
		GetModuleFileName(baseModule, baseModuleName, sizeof(baseModuleName));
		int indexOfLastPathNode = StrEndsWith(baseModuleName, sizeof(baseModuleName), '\\') + 1;
		
		WCHAR exeName[MAX_PATH];
		auto lenght = std::wcslen(baseModuleName);
		wcscpy_s(exeName, lenght, baseModuleName + indexOfLastPathNode);
		StrToLower(exeName);

		std::wregex pattern(L"dead(\\s|\\_)space?(.+)\\.exe");
		if (std::regex_search(exeName, pattern))
		{
			MODULEINFO moduleInfo;
			GetModuleInformation(GetCurrentProcess(), baseModule, &moduleInfo, sizeof(moduleInfo));
			if (moduleInfo.SizeOfImage == 12009472 //Steam Unpacked 
				|| moduleInfo.SizeOfImage == 12353536 //Steam Normal
				|| moduleInfo.SizeOfImage == 12005376 //Origin
				|| moduleInfo.SizeOfImage == 12005376 //GOG
				)
				OverrideCharArray(0x00C7B13C, "XCENTKOWSK_C78C369_F71988A_v3", 29);
			else
			{
				std::wstring messageBoxText = L"Unknown module size: " + std::to_wstring(moduleInfo.SizeOfImage) + L".\nNothing was overriden!";
				MessageBox(NULL, messageBoxText.c_str(), L"Warning", MB_ICONWARNING | MB_OK);
			}
		}
		else
		{
			std::wstring messageBoxText = L"Unrecognized exe name: " + (std::wstring)exeName + L"\nFull path: " + (std::wstring)baseModuleName;
			MessageBox(NULL, messageBoxText.c_str(), L"Warning", MB_ICONWARNING | MB_OK);
		}
	}
	else if (reason == DLL_PROCESS_DETACH) {
	}
	return TRUE;
}