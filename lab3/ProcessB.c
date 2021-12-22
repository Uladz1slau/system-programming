#include <windows.h>
#include <stdio.h>

int main(void) {

	

	LPCTSTR pipename = "\\\\.\\pipe\\mynamedpipe";					
	HANDLE hNamedPipe;												
	DWORD szAddress;												
	DWORD cbRead, cbWritten;										
	char* msg;														
	BOOL Success;													
	printf("Creating named pipe...");
	hNamedPipe = CreateNamedPipe(
		pipename,												
		PIPE_ACCESS_DUPLEX,											
		PIPE_TYPE_MESSAGE |										
		PIPE_READMODE_MESSAGE |	
		PIPE_WAIT,													PIPE_UNLIMITED_INSTANCES,						
		sizeof(DWORD),												
		sizeof(DWORD),												
		100,														NULL);														
	if (hNamedPipe == INVALID_HANDLE_VALUE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nConnecting to pipe...");
	ConnectNamedPipe(hNamedPipe, NULL);

	printf("Success!!!\nReading from pipe...");
	Success = ReadFile(
		hNamedPipe,													&szAddress,													
		sizeof(szAddress),											
		&cbRead,													
		NULL);														
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg);

	printf("Sending answer to ProccessA...");
	Success = WriteFile(
		hNamedPipe,													
		&szAddress,													
		sizeof(szAddress),											
		&cbWritten,													
		NULL);		
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nDisconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nClosing named pipe...");
	Success = CloseHandle(hNamedPipe);
	if (Success == FALSE) {
		printf("Failure!!!\n");
		system("pause");
		return -1;
	}

	printf("Success!!!\nProcessB was finished...\n");
	system("pause");
	return 0;
}