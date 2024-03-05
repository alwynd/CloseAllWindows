#include "closeWindows.h"

using namespace std;
wchar_t tbuffer[2048];



// Enum window callback
BOOL CALLBACK EnumWindowCallback(HWND hWnd, LPARAM lparam) 
{
	int length = GetWindowTextLength(hWnd);
	char buffer[1024];
	char windowText[2048];
	char ImageName[2048];
	
	ZeroMemory(buffer, 1024);
	ZeroMemory(windowText, 2048);
	ZeroMemory(ImageName, 2048);
	DWORD dwProcId = 0;

	// List visible windows with a non-empty title
	long result = GetWindowLong(hWnd, GWL_STYLE);
	if (IsWindowVisible(hWnd) && length != 0 && (result & (WS_VISIBLE | WS_CAPTION))) 
	{
		int wlen = length + 1;
		GetWindowText(hWnd, windowText, wlen);
		GetWindowThreadProcessId(hWnd, &dwProcId);
		if (dwProcId)
		{
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
			if (hProc)
			{
				HMODULE hMod;
				DWORD cbNeeded;
				bool IsMinimized = IsIconic(hWnd);
				if (EnumProcessModules(hProc, &hMod, sizeof(hMod), &cbNeeded))
				{
					GetModuleBaseNameA(hProc, hMod, ImageName, MAX_PATH);
				} //if
				CloseHandle(hProc);

				if (_strcmpi(windowText, "Program Manager") != 0
					&& _strcmpi(ImageName, "HxCalendarAppImm.exe") != 0
					&& _strcmpi(ImageName, "TextInputHost.exe") != 0
					&& _strcmpi(ImageName, "NVIDIA Share.exe") != 0
					&& _strcmpi(ImageName, "Video.UI.exe") != 0
					&& _strcmpi(windowText, "CloseAllWindowsCMD") != 0
					
					)
				{
					sprintf_s(buffer, "closeWindows.EnumWindowCallback, Window: hwnd: %p, Title: '%-55s', Executable: '%-55s', Min: '%-5s'\n\0", hWnd, windowText, ImageName, BOOL_TEXT(IsMinimized)); printf(buffer);
					
					SendMessage(hWnd, WM_CLOSE, NULL, (LPARAM) 0);
					SendMessage(hWnd, WM_QUIT, NULL, (LPARAM) 0);
					SendMessage(hWnd, WM_DESTROY, NULL, (LPARAM) 0);
					
				}
			} //if
		} //if
		
	}

	return TRUE;
}

//Main entry point.
int _tmain(int argc, _TCHAR* argv[])
{
	EnumWindows(EnumWindowCallback, NULL);

	return 0;
}