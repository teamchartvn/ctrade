#include <iostream>
#include <atomic>
#include <vector>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

class Dulieu
{
public:
	Dulieu();
	~Dulieu();

private:
	float dulieu_tho;
};

Dulieu::Dulieu()
{
}

Dulieu::~Dulieu()
{
}


// (1) Data thô cho từng phút or từng ngày của dữ liệu gốc bao gồm chỉ bid ask contract. 1 Phần tử ứng với lần market data thông báo có contract mới
// Cấu trúc      [kiểu =(bid or ask ) , volume = int , time =Datetime , Giá [ đóng mở cao thấp] ]
// 
// 
//  (2) Một Mảng chứa các index có chức năng map cho từng ( phút 5 15 30.. từng giờ , từng ngày ). Được tổ chức  = [kiểuThời gian = (Đóng , mở), index(đầu, cuối)  ] 
//       + kiểu =  (giay phút giờ ngày ....volume delta ...) . 
//       + Thời gian = thời gian bắt đầu , thời gian kết thúc
//       + Index của phần tử đầu tiên và  phần tử cuối cùng nến (index trong data thô mảng 1 )
//   vd : [ phút ,11h50,11h55, 1000321,1000600]  ( kiểu phút , mở lúc 11h50,đóng 11h55, phần tử đầu tiên 1000321,1000600) .
// Mục đích để load dữ liệu thô theo từng đoạn ko cần load hết
// File chứa các index 
