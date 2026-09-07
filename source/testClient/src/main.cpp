#include "ipcLib.h"

#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE pipe;
	int result = PipeClient::InitClientPipe("fooPipe", pipe);

	while (result != 0
		&& pipe == (HANDLE)0xffffffffffffffff)
	{
		result = PipeClient::InitClientPipe("fooPipe", pipe);

		Sleep(15);

		printf("Repeat client pipe init\n");
	}

	printf("Client pipe initialized: %i\n", result);

	char* msg = "Ceci n'est pas une pipe\0";
	DWORD bytesWritten = 0;

	PipeClient::WritePipe(pipe, msg, strlen(msg) + 1, bytesWritten);

	Sleep(500);

	// PipeClient::CloseClientPipe(pipe);

	// PipeServer::CloseServerPipe(pipe);

	return 0;
}