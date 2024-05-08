#pragma once

#ifdef PHANLOI_EXPORTS
#define PHANLOI_DLL_API __declspec(dllexport)
#else
#define PHANLOI_DLL_API __declspec(dllimport)
#endif


#include <iostream>
#include <vector>
#include <atomic>
#include<cstdlib>
#include <atomic>
#include <memory>

using namespace std;
// Các tham số cho zigzag
struct CauHinhZigZag
{
	int do_sau;
	double do_lech;
	int buoc_lui;
	int dodainen;
};

// Struct or class cũng được chứa các tham số khởi tạo.
#ifndef KHOITAO_CLASS_STATIC
#define KHOITAO_CLASS_STATIC
 class KHOI_TAO {
 public:
	static int mode; // chế độ hoạt động thời gian thực , phát lại , lịch sử
	static int so_chart; // số loại chart đang chạy = cấn tính toán update = size() của  tatca_nen;
	 // cấn khai báo lại .cpp ko báo lỗi unresolved external symbol
};

#endif // !1


std::atomic_bool khoi_tao(false);
int huy = 0;
//void KhoiTao();

vector<CauHinhZigZag> CauHinh; // Tính cho nhiều loại nến , đọc từ vector này có bao nhiêu phần tử cần tính toán từng đó

enum CHE_DO {
	THOIGIANTHUC, LICHSU, PHATLAI
};


enum KIEUNEN
{
	TIME, VOL, DELTA, RANGE, BOX // 1 2 3 4 5
};
//                      | ->  KHUNG NEN -> ( NEN + PROFILE_NEN )
//                      | 
//           soloainen  | -> KHUNG NEN -> ( NEN + PROFILE_NEN )
//                      |  ..
//                      |  ..
//                      |  .....
//                      |-> KHUNG NEN -> ( NEN + PROFILE_NEN )
struct PHANLOAINEN {
	KIEUNEN en;
	double giatri_nen;
};

#ifndef CLASS_PROFILE
#define CLASS_PROFILE
class PROFILE {

};
#endif


#ifndef NEN_CLASS
#define NEN_CLASS
class  NEN {
private:
	//KIEUNEN kieu;
	long long int ticks; // số ticks của thời gian
	double giacao, giathap, giamo, giadong;
	//double poc, vol, delta;
	//double dodainen; // M5 m3  60' ...delta 200... Độ lớn của nến theo một kiểu nào đó 
public:
	//inline void CapNhatNen(NEN & nhap);  // thực hiện cv so sánh thời gian để update nến
};
#endif NHAP_DATA // ! Nhập các tham số trong chế độ thời gian thực or tương tự  retick ( bao gồm bid ask giá vol time )
#ifndef NHAP_DATA 

class NHAP_DATA : NEN {  // kế thừa class nến cơ bản chỉ gồm các giá

};
#endif // !1



#ifndef KHUNGNEN_CLASS
#define KHUNGNEN_CLASS
 class KHUNGNEN
 {
 public:
	 
	 KIEUNEN kieu;
	 double dodainen;
	 
	 // Tại sao lại phải dùng con trỏ ở đây ? Khi muốn thay thế làm lại , fix , một mảng nến mới. cần tạo một contro vector mới rồi std::move
	 std::unique_ptr < std::vector<NEN>> mang_nen;         
	 KHUNGNEN();
	 inline void CapNhatNen(NEN& nhap);  // thực hiện cv so sánh thời gian để update nến
 private:
	 int sophantu; // số nến trong vector mang_nen : xây dựng biến đếm thủ công tránh gọi hàm size() liên tục 
 };

#endif // !1


// extern std::unique_ptr<std::vector<KHUNGNEN>> tatca_nen;  // sao ko tạo luôn 1 vector cần gì tạo con trỏ chỗ này ? vì dung lượng ko nhiều
 //extern std::vector<KHUNGNEN > *tatca_nen;
 extern std::vector <KHUNGNEN> tatca_nen;
// Nhập dữ liệu mỗi lần có giá ( cao thấp or open close  tùy theo chế độ tính zigzag )
extern "C" PHANLOI_DLL_API int KhoiTao(CHE_DO md);
extern "C" PHANLOI_DLL_API void CAPNHAT(double cao, double thap, double mo, double dong, long long int time);


extern "C" PHANLOI_DLL_API int TimDiemXoay();

#pragma once

//#include <memory>
extern std::atomic_bool sansang_doc = false;  // Cờ báo vector_nen sẵn sàng để đọc.
