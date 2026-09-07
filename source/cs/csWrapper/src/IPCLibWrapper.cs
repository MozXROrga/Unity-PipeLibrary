using System.Text;
using System.Runtime.InteropServices;
using System;
using System.Threading;

public static class LibIPC
{
    public const string name = "IPCLib";

    [DllImport(name, EntryPoint = "InitServerPipe")]
	public static extern int InitServerPipe(byte[] pipeName, ref IntPtr handle, bool blocking);

    [DllImport(name, EntryPoint = "CreateOverlappedStruct")]
    public static extern int CreateOverlappedStruct(ref NativeOverlapped overlapped);

    [DllImport(name, EntryPoint = "AcceptConnection")]
    public static extern int AcceptConnection(ref IntPtr handle, ref NativeOverlapped overlapped);

    [DllImport(name, EntryPoint = "PeekPipe")]
    public static extern int PeekPipe(ref IntPtr handle, byte[] buffer, int bufferSize, ref IntPtr bytesRead);

    [DllImport(name, EntryPoint = "ReadPipe")]
    public static extern int ReadPipe(ref IntPtr handle, byte[] buffer, int bufferSize, ref IntPtr bytesRead, ref NativeOverlapped overlapped);

    [DllImport(name, EntryPoint = "DisconnectPipe")]
    public static extern int DisconnectPipe(ref IntPtr handle);

    [DllImport(name, EntryPoint = "CloseServerPipe")]
    public static extern int CloseServerPipe(ref IntPtr handle);

    [DllImport(name, EntryPoint = "CheckOperationFinished")]
    public static extern int CheckOperationFinished(ref IntPtr handle, ref NativeOverlapped overlapped, int waitTimeInMS);

    [DllImport(name, EntryPoint = "InitClientPipe")]
    public static extern int InitClientPipe(byte[] pipeName, ref IntPtr handle);

    [DllImport(name, EntryPoint = "WritePipe")]
    public static extern int WritePipe(ref IntPtr handle, byte[] buffer, int bufferSize, ref IntPtr bytesWritten);

    [DllImport(name, EntryPoint = "CloseClientPipe")]
    public static extern int CloseClientPipe(ref IntPtr handle);
}

/*
 * 
 * 
 * IPC_LIB_API int InitServerPipe(const char* pipeName, HANDLE& pipeHandle);

	// Blocking
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int AcceptConnection(HANDLE& pipeHandle);

	// Blocking
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int ReadPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int DisconnectPipe(HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API void CloseServerPipe(HANDLE& pipeHandle);
}

namespace PipeClient
{
	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int InitClientPipe(const char* pipeName, HANDLE& pipeHandle);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API int WritePipe(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten);

	// Return: 0 if successful, else result of GetLastError()
	IPC_LIB_API void CloseClientPipe(HANDLE& pipeHandle);
 * 
 */
