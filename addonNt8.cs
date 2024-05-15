#region Using declarations
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Xml.Serialization;
using System.IO.MemoryMappedFiles;

using NinjaTrader.Cbi;
using NinjaTrader.Gui;
using NinjaTrader.Gui.Chart;
using NinjaTrader.Gui.SuperDom;
using NinjaTrader.Gui.Tools;
using NinjaTrader.Data;
using NinjaTrader.NinjaScript;
using NinjaTrader.Core.FloatingPoint;
using NinjaTrader.Gui.Tools;
#endregion

//This namespace holds Add ons in this folder and is required. Do not change it. 
namespace NinjaTrader.NinjaScript.AddOns
{
	public class SHAREMEM : NinjaTrader.NinjaScript.AddOnBase
	{
		
		/// <summary>
///   File .Net
/// </summary>
	public string memoryMappedFileName = "Buf";
    private MemoryMappedViewAccessor doc_ghi;
	private  const int MemorySize =128;
        // Hàm đọc ghi chia sẻ bộ nhớ theo .Net
        public  SHAREMEM(){
		
		using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting("Buf"))
        using (MemoryMappedViewAccessor accessor = mmf.CreateViewAccessor())
        {
          // Đọc dữ liệu từ vùng nhớ chia sẻ
          doc_ghi = accessor;
        }
		
	}
	
		
public void  DocGhi(double cao , double thap, double dong , double mo){
	  // đọc dữ liệu byte 127
	  byte flag = doc_ghi.ReadByte(MemorySize - 1);
	  byte[] data = new byte[MemorySize - 1];
      doc_ghi.ReadArray<byte>(0, data, 0, data.Length);
	  ChuyenDoiByte(ref data,cao);
	  ChuyenDoiByte(ref data,thap);
	  ChuyenDoiByte(ref data,dong);
	  ChuyenDoiByte(ref data,mo);
	  
	
	
}





private void ChuyenDoiByte(ref byte [] data , double gia){
	         
	          byte[] bytes = BitConverter.GetBytes(gia);

              // Sao chép mảng byte vào mảng data
              for (int i = 0; i < bytes.Length; i++)
              {
               data[currentIndex + i] = bytes[i];
              }
}






		
		protected override void OnStateChange()
		{
			if (State == State.SetDefaults)
			{
				Description									= @"Enter the description for your new custom Add on here.";
				Name										= "MyCustomAddOn2";
			}
			else if (State == State.Configure)
			{
				
			}
		}
	}
}
