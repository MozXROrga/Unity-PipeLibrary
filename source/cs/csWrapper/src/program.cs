using System;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

class LibWrapperTest
{
    static void Main(string[] args)
    {
        if (args.Length > 0)
        {
            if (args[0] == "server")
            {
                ServerTest();
            }
            else if (args[0] == "client")
            {
                ClientTest();
            }
            else if (args[0] == "master")
            {
                TestMaster();
            }
        }
    }

    static void ServerTest()
    {
        Console.WriteLine("CS Test Server");

        int h = 0;
        IntPtr handle = new IntPtr(h);
        byte[] pipeName = Encoding.ASCII.GetBytes("csTestPipe");
        // StringBuilder pipeName = new StringBuilder("csTestPipe");

        NativeOverlapped overlapped = new NativeOverlapped();

        int result = LibIPC.InitServerPipe(pipeName, ref handle, false);

        if (result == 0)
        {
            Console.WriteLine("Server pipe initialized");

            result = LibIPC.CreateOverlappedStruct(ref overlapped);

            if(result != 0)
            {
                Console.WriteLine("Failed to initialize OVERLAPPED struct");
            }

            result = LibIPC.AcceptConnection(ref handle, ref overlapped);

            while(result != 0)
            {
                System.Threading.Thread.Sleep(10);  // in non-blocking mode it's a good idea to do a short sleep, had system performance issues without

                Console.WriteLine("No client: " + result.ToString());

                result = LibIPC.AcceptConnection(ref handle, ref overlapped);
            }

            if(result == 0)
            {
                Console.WriteLine("Server connection accepted");

                // StringBuilder readBuffer = new StringBuilder(1024);

                byte[] readBuffer = new byte[1024];

                int br = 0;
                IntPtr brPtr = new IntPtr(br);
                result = LibIPC.ReadPipe(ref handle, readBuffer, 1024, ref brPtr, ref overlapped);

                string text = Encoding.ASCII.GetString(readBuffer);

                if(result == 0)
                {
                    Console.WriteLine(brPtr.ToInt64() + " bytes read: " + text);
                }
            }
        }
        
        LibIPC.CloseServerPipe(ref handle);

        Console.WriteLine("Press any key...");
        Console.ReadKey();
    }

    static void ClientTest()
    {
        Console.WriteLine("CS Test Client");

        int h = 0;
        IntPtr handle = new IntPtr(h);
        // StringBuilder pipeName = new StringBuilder("csTestPipe");

        byte[] pipeName = Encoding.ASCII.GetBytes("csTestPipe");

        int result = LibIPC.InitClientPipe(pipeName, ref handle);

        if(result == 0)
        {
            Console.WriteLine("Client pipe initialized");

            // StringBuilder readBuffer = new StringBuilder("Ceci n'est pas une pipe");

            string foo = "Ceci n'est pas une pipe";
            byte[] data = Encoding.ASCII.GetBytes(foo);

            int bw = 0;
            IntPtr bwPtr = new IntPtr(bw);

            result = LibIPC.WritePipe(ref handle, data, foo.Length, ref bwPtr);

            Thread.Sleep(100);

            LibIPC.CloseClientPipe(ref handle);
        }
        else
        {
            Console.WriteLine("Failed to init client pipe: " + result);
        }

        Console.WriteLine("Press any key...");
        Console.ReadKey();
    }

    static void TestMaster()
    {
        string dir = System.IO.Directory.GetCurrentDirectory();

        Process.Start(dir + "\\CSWrapper.exe", "server");

        Process.Start(dir + "\\CSWrapper.exe", "client");
    }
}
