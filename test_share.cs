using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO.MemoryMappedFiles;
using System.Threading;


namespace TestCalldll
{
    class Program
    {   /// <summary>
    /// 
    /// </summary>
    /// <param name="Dll chia sẻ file"></param>
    /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr OpenFileMapping(uint dwDesiredAccess, bool bInheritHandle, string lpName);

        // Khai báo hàm ánh xạ bộ nhớ chia sẻ vào không gian bộ nhớ của tiến trình
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr MapViewOfFile(IntPtr hFileMappingObject, uint dwDesiredAccess, uint dwFileOffsetHigh, uint dwFileOffsetLow, uint dwNumberOfBytesToMap);
        const uint FILE_MAP_ALL_ACCESS = 0x000F001F;
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool UnmapViewOfFile(IntPtr lpBaseAddress);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool CloseHandle(IntPtr hObject);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="Call C++"></param>
        /// <param name="gia_thap"></param>
        /// <returns></returns>



        [DllImport(@"C:\Users\FX\source\repos\ZigZag\x64\Debug\ZigZag.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int NhapDuLieu(double gia_cao, double gia_thap);


        [DllImport(@"C:\Users\FX\source\repos\ZigZag\x64\Debug\ZigZag.dll", CharSet = CharSet.Ansi)]
        public static extern int TimDiemXoay();
        [DllImport(@"C:\Users\FX\source\repos\ZigZag\x64\Debug\ZigZag.dll", CharSet = CharSet.Ansi)]
        public static extern int KhoiTao();

       


        static void Main(string[] args)
        {
            // KhoiTao();
            Console.Write(KhoiTao().ToString());
            //Console.Write(TimDiemXoay().ToString());

            Console.Write(DateTime.UtcNow.Ticks);



         

                // Phần đọc bộ nhớ 


                // Mở bộ nhớ chia sẻ được tạo bởi tiến trình C++
                IntPtr hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, "MySharedMemory");
                if (hMapFile == IntPtr.Zero)
                {
                    Console.WriteLine(" Không thể mở bộ nhớ chia sẻ " + Marshal.GetLastWin32Error());
                    return;
                }

                // Ánh xạ bộ nhớ chia sẻ vào không gian bộ nhớ của tiến trình
                IntPtr pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
                if (pBuf == IntPtr.Zero)
                {
                    Console.WriteLine(" Không thể ánh xạ ...  " + Marshal.GetLastWin32Error());
                    return;
                }

            // Khai báo biến flag để thực hiện đồng bộ giữa các tiến trình
            // thực hiện đọc ghi ở đây
            unsafe
            {
                byte* ptr = (byte*)pBuf.ToPointer();
                byte* flag = ptr + 128 - 1;

                while (true)
                {
                    if (*flag == 1)
                    {
                        // Do something...

                        *flag = 0;
                    }

                    Thread.Sleep(100);
                }
            }

            UnmapViewOfFile(pBuf);
            CloseHandle(hMapFile);













            Console.WriteLine("Data written to memory mapped file. Press any key to exit.");
                Console.ReadKey();
            }


        
    }
}
