#include <cstdlib>
#include <string>
#include <sstream>
#include <filesystem>
#include <Windows.h>

DWORD WINAPI runServer(LPVOID lpvParam);
DWORD WINAPI runClient(LPVOID lpvParam);

int main()
{
	// PROJECT_CONFIGURATION;

	DWORD dwThreadId = 0;

	HANDLE serverThread = CreateThread(
		NULL,
		0,
		runServer,
		NULL,
		0,
		&dwThreadId);

	Sleep(500);

	HANDLE clientThread = CreateThread(
		NULL,
		0,
		runClient,
		NULL,
		0,
		&dwThreadId);

	while (true)
	{

	}

	return 0;
}

DWORD WINAPI runServer(LPVOID lpvParam)
{
	std::filesystem::path workingDir = std::filesystem::current_path();
	std::string foo = workingDir.string();

	std::stringstream serverPath;
	serverPath << foo << "/server/" << PROJECT_CONFIGURATION << "/TestServer.exe";

	system(serverPath.str().c_str());

	return 0;
}

DWORD WINAPI runClient(LPVOID lpvParam)
{
	std::filesystem::path workingDir = std::filesystem::current_path();
	std::string foo = workingDir.string();

	std::stringstream serverPath;
	serverPath << foo << "/client/" << PROJECT_CONFIGURATION << "/TestClient.exe";

	system(serverPath.str().c_str());

	return 0;
}
