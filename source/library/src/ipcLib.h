#ifndef IPC_LIB_H
#define IPC_LIB_H

#include <Windows.h>

#ifdef IPC_LIB_EXPORTS
#define IPC_LIB_API extern "C"  __declspec(dllexport)
#else
#define IPC_LIB_API extern "C"  __declspec(dllimport)
#endif

namespace PipeServer
{
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int InitServerPipe(const char* pipeName, HANDLE& pipeHandle, bool blocking);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int CreateOverlappedStruct(LPOVERLAPPED overlapped);

	// Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int AcceptConnection(HANDLE& pipeHandle, LPOVERLAPPED overlapped);

	// Non-Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int PeekPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead);

	// Blocking unless overlapped
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int ReadPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead, LPOVERLAPPED overlapped);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int DisconnectPipe(HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API void CloseServerPipe(HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int CheckOperationFinished(HANDLE& pipeHandle, LPOVERLAPPED overlapped, int waitTimeInMS);
}

namespace PipeClient
{
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int InitClientPipe(const char* pipeName, HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int WritePipe(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API void CloseClientPipe(HANDLE& pipeHandle);
}

namespace PipeUtility
{
	// pipeName without the preceding "\\\\.\\pipe\\"
	// Return: 0 if pipe was found, -1 if it wasn't, else result of GetLastError()
	IPC_LIB_API int PipeExistsByName(const char* pipeName);
}

#endif // IPC_LIB_H
