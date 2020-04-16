#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string>
#include<iostream>
using namespace std;
HANDLE ready;
int main()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	HANDLE canal;
	
	string message;
	TCHAR nameProcess[] = "Client.exe";
	canal = CreateNamedPipe(TEXT("\\\\.\\pipe\\readCanal"), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 1024 * 16, 1024 * 16, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (CreateProcess(NULL, nameProcess, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) == TRUE) {
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		printf("Created process \n");
		wchar_t buffer[20];
		_itow_s(pi.dwProcessId, buffer, 10);
		ready = CreateSemaphoreA(
			NULL,
			1,
			2,
			(LPCSTR)"Sem"//name object
		);
		DWORD d;
		while (&canal != INVALID_HANDLE_VALUE)
		{
			ReleaseSemaphore(ready, 1, NULL);
			std::cin >> message;
			WriteFile(canal, message.c_str(), message.size()+2, &d, NULL);
		}
	}
		return 0;
}



	


