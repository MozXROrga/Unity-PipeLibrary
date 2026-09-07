# MozXR Pipe Library for Unity Framework

This library is used in the [MozXR Unity Framework](https://github.com/MozXROrga/Unity-Framework).

This library was written for Windows x64.

## Overview

This project contains a library that wraps [Windows Named Pipes](https://learn.microsoft.com/en-us/windows/win32/ipc/named-pipes) and some demo and test setups.

- **CSWrapper:** contains a c# file to import functions from IPCLib.dll (the next project in the list), and a small test program in c#.
- **IPCLib:** wraps Windows Named Pipes in a .dll file.
- **TestClient: ** uses IPCLib.dll to connect to a server pipe and send a test message.
- **TestRunner:** launches TestServer.exe and TestClient.exe in sequence to verify functionality of IPCLib.dll
- **TestServer:** uses IPCLib.dll to open a pipe server.

## Setup

This project was written for Windows x64, no further dependencies.

Use CMake (3.22 or later).

## License

mozXR Attribution License (mozXR-AL) v1.0
Based on the MIT License

Copyright (c) Mozarteum University Salzburg – X-Reality Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

2. Attribution Requirement:
   Any project, product, or documentation that uses the Software or substantial
   portions of it must include the following credit in a reasonable manner:
   "Based on mozXR by Mozarteum University Salzburg – X-Reality Lab and 
    Ars Electronica Futurelab"
   This credit must appear in:
   - Project documentation (e.g., README, manuals)
   - Public-facing credits (e.g., About page, project credits)

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

SPDX-License-Identifier: mozXR-AL-1.0

