using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace TestCalldll
{
    class Program
    {
        [DllImport(@"C:\Users\FX Unify\source\repos\ZigZag\x64\Debug\ZigZag.dll", CallingConvention = CallingConvention.Cdecl)]
        public  static extern int NhapDuLieu(double gia_cao, double gia_thap);


        [DllImport(@"C:\Users\FX Unify\source\repos\ZigZag\x64\Debug\ZigZag.dll", CharSet = CharSet.Ansi)]
        public  static extern int TimDiemXoay();
        static void Main(string[] args)
        {

            Console.Write(TimDiemXoay().ToString());
            Console.Read();
        }
    }
}
