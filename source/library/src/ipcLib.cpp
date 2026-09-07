#include "ipcLib.h"

#include <stdio.h>

#define DATA_SIZE 2097152

// https://learn.microsoft.com/en-us/windows/win32/ipc/named-pipe-server-using-overlapped-i-o
int PipeServer::InitServerPipe(const char* pipeName, HANDLE& pipeHandle, bool blocking)
{
    char* baseName = "\\\\.\\pipe\\";
    char* fullName = new char[strlen(baseName) + strlen(pipeName)];
    strcpy(fullName, baseName);
    strcat(fullName, pipeName);

    DWORD openMode = PIPE_ACCESS_DUPLEX;
    DWORD mode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT;

    if (blocking == false)
    {
        openMode |= FILE_FLAG_OVERLAPPED;
    }

    pipeHandle = CreateNamedPipe(
        TEXT(fullName),
        openMode,
        mode,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
        PIPE_UNLIMITED_INSTANCES,
        DATA_SIZE,
        DATA_SIZE,
        5,
        NULL);

    // delete fullName; // deleting fullName causes exception

    if (pipeHandle == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    OVERLAPPED ol;

    return 0;
}

int PipeServer::CreateOverlappedStruct(LPOVERLAPPED overlapped)
{
    overlapped->Offset = 0;
    overlapped->OffsetHigh = 0;
    overlapped->hEvent = CreateEventA(nullptr, true, true, nullptr);

    if (overlapped->hEvent == nullptr)
    {
        return GetLastError();
    }

    return 0;
}

int PipeServer::AcceptConnection(HANDLE& pipeHandle, LPOVERLAPPED overlapped)
{
    if (ConnectNamedPipe(pipeHandle, overlapped) == false)
    {
        DWORD error = GetLastError();

        // https://learn.microsoft.com/en-us/windows/win32/api/namedpipeapi/nf-namedpipeapi-connectnamedpipe#return-value
        if (error == ERROR_PIPE_CONNECTED)
        {
            if (overlapped != nullptr)
            {
                SetEvent(overlapped);
            }

            return 0;
        }

        return error;
    }

    return 0;
}

int PipeServer::PeekPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead)
{
    if (PeekNamedPipe(pipeHandle, buffer, bufferSize, &bytesRead, NULL, NULL) == false)
    {
        return GetLastError();
    }

    return 0;
}

int PipeServer::ReadPipe(HANDLE& pipeHandle, char* buffer, const int bufferSize, DWORD& bytesRead, LPOVERLAPPED overlapped)
{
    if (ReadFile(pipeHandle, buffer, bufferSize, &bytesRead, overlapped) == false)
    {
        return GetLastError();
    }

    return 0;
}

int PipeServer::DisconnectPipe(HANDLE& pipeHandle)
{
    if (DisconnectNamedPipe(pipeHandle) == false)
    {
        return GetLastError();
    }

    return 0;
}

void PipeServer::CloseServerPipe(HANDLE& pipeHandle)
{
    CloseHandle(pipeHandle);
}

int PipeServer::CheckOperationFinished(HANDLE& pipeHandle, LPOVERLAPPED overlapped, int waitTimeInMS)
{
    int result = 0;

    WaitForSingleObject(overlapped->hEvent, waitTimeInMS);

    DWORD btr = 0;
    bool ovlpResult = GetOverlappedResult(pipeHandle, overlapped, &btr, false);

    if (ovlpResult == false)
    {
        result = GetLastError();
    }

    return result;
}






int PipeClient::InitClientPipe(const char* pipeName, HANDLE& pipeHandle)
{
    char* baseName = "\\\\.\\pipe\\";
    char* fullName = new char[strlen(baseName) + strlen(pipeName)];
    strcpy(fullName, baseName);
    strcat(fullName, pipeName);

    pipeHandle = CreateFile(TEXT(fullName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    // delete fullName; // deleting fullName causes exception

    if (pipeHandle == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    return 0;
}

int PipeClient::WritePipe(HANDLE& pipeHandle, const char* buffer, const int bufferSize, DWORD& bytesWritten)
{
    if (WriteFile(pipeHandle, buffer, bufferSize, &bytesWritten, NULL) == false)
    {
        return GetLastError();
    }

    return 0;
}

void PipeClient::CloseClientPipe(HANDLE& pipeHandle)
{
    CloseHandle(pipeHandle);
}

int PipeUtility::PipeExistsByName(const char* pipeName)
{
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFileA("\\\\.\\pipe\\*", &fd);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }
    else
    {
        do
        {
            // printf("%s - %s\n", pipeName, fd.cFileName);

            if (strcmp(pipeName, fd.cFileName) == 0)
            {
                FindClose(hFind);
                return 0;
            }
        }
        while (FindNextFileA(hFind, &fd));

        FindClose(hFind);
    }

    return -1;
}
