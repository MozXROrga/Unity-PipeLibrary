#include <stdio.h>
#include "ipcLib.h"

#include <Windows.h>

int main()
{
	HANDLE pipe;
	int result = PipeServer::InitServerPipe("fooPipe", pipe, false);

	int pipeExistsResult = PipeUtility::PipeExistsByName("fooPipe");

	printf("Pipe exists (should be 0): %i\n", pipeExistsResult);

	PipeServer::DisconnectPipe(pipe);

	printf("Pipe initialized: %i\n", result);

	OVERLAPPED overlapped;
	result = PipeServer::CreateOverlappedStruct(&overlapped);

	printf("Overlapped created: %i\n", result);

	result = PipeServer::AcceptConnection(pipe, &overlapped);

	bool ovlpResult = (PipeServer::CheckOperationFinished(pipe, &overlapped, 1000 / 60) == 0);
	while (ovlpResult == false)
	{
		ovlpResult = (PipeServer::CheckOperationFinished(pipe, &overlapped, 1000 / 60) == 0);
	}

	// PipeServer::

	/*bool ovlpResult = false;

	while (ovlpResult == false)
	{
		WaitForSingleObject(overlapped.hEvent, 1000 / 60);

		DWORD btr = 0;
		ovlpResult = GetOverlappedResult(pipe, &overlapped, &btr, false);
	}*/

	int foo = 0;

	//while (result != 0)
	//{
	//	printf("Repeating accept connection: %i\n", result);

	//	Sleep(10); // in non-blocking mode it's a good idea to do a short sleep, had system performance issues without

	//	result = PipeServer::AcceptConnection(pipe, &overlapped);
	//}

	printf("Pipe connection accepted: %i\n", result);

	if (result == 0 || ovlpResult == true)
	{
		char* buffer = new char[1024];
		DWORD bytesRead = 0;
		result = PipeServer::ReadPipe(pipe, buffer, 1024, bytesRead, &overlapped);

		while (result != 0)
		{
			result = PipeServer::ReadPipe(pipe, buffer, 1024, bytesRead, &overlapped);
		}

		printf("Pipe read: %i\n", result);

		printf("Message: '%s'\n", buffer);

		int foo = 0;

		PipeServer::DisconnectPipe(pipe);
	}

	PipeServer::CloseServerPipe(pipe);

	system("Pause");
	
	return 0;
}
