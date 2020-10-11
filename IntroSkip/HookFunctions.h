#pragma once
#pragma once
#include <Windows.h>

static bool OverrideCharArray(intptr_t addressOfText, const char* textToOverrideWith, const size_t OriginalLenght)
{
	if (std::strlen(textToOverrideWith) > OriginalLenght)
	{
		MessageBox(NULL, "Char to override with is longer than original char", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	DWORD curProtectionFlag;
	VirtualProtect((void*)addressOfText, OriginalLenght, PAGE_EXECUTE_READWRITE, &curProtectionFlag);
	memcpy((void*)addressOfText, textToOverrideWith, OriginalLenght);
	DWORD temp;
	VirtualProtect((void*)addressOfText, OriginalLenght, curProtectionFlag, &temp);

	return true;
}

static int StrEndsWith(char* chrArray, int lenght, char character)
{
	int pos = -1;
	for (int i = 0; i < lenght; i++)
	{
		if (chrArray[i] == character)
			pos = i;
	}

	return pos;
}

static void StrToLower(char* chrArray, int Lenght)
{
	for (int i = 0; i < Lenght; i++)
	{
		chrArray[i] = ::tolower(chrArray[i]);
	}
}