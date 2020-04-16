#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<string>
int main()
{
	char buf[1024];
	DWORD d;
	HANDLE hSem = CreateSemaphoreA(
		NULL,
		1,
		2,
		(LPCSTR)"Sem"//name object
	);
	HANDLE canal = CreateFile(TEXT("\\\\.\\pipe\\readCanal"), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (&hSem == INVALID_HANDLE_VALUE) { std::cout << "error"; }
	while (&canal != INVALID_HANDLE_VALUE) {
		if (WaitForSingleObject(hSem, 0) == WAIT_OBJECT_0) {
			while (ReadFile(canal, buf, sizeof(buf) - 1, &d, NULL) != FALSE)
			{
				buf[d] = '/0';
				printf("%s", buf);
				printf("\n");	
			}	
		}
		else
		{
		//	std::cout << GetLastError();
		}
	}
}