#include <iostream>
#include <vector>
#include <atomic>
#include<cstdlib>
#include <atomic>
#include <memory>

using namespace std;



#pragma once
#ifdef ZIGZAGDLL_EXPORTS
#define ZIGZAGDLL_API __declspec(dllexport)
#else
#define ZIGZAGDLL_API __declspec(dllimport)
#endif

// Các tham số cho zigzag
struct CauHinhZigZag
{   
	int do_sau;
	double do_lech;
	int buoc_lui;
	int dodainen;
};


bool khoi_tao = false;

//void KhoiTao();

vector<CauHinhZigZag> CauHinh; // Tính cho nhiều loại nến , đọc từ vector này có bao nhiêu phần tử cần tính toán từng đó


enum KIEUNEN
{
	TIME, VOL, DELTA, RANGE, BOX // 1 2 3 4 5
};

class  NEN {
	KIEUNEN kieu;
	double giacao, giathap, giamo, giadong;
	double poc, vol, delta;
	int dodainen; // M5 m3  60' ...delta 200... Độ lớn của nến theo một kiểu nào đó 
};

// Nhập dữ liệu mỗi lần có giá ( cao thấp or open close  tùy theo chế độ tính zigzag )
extern "C" ZIGZAGDLL_API void KhoiTao();
extern "C" ZIGZAGDLL_API int NhapDuLieu(double gia_cao, double gia_thap);


extern "C" ZIGZAGDLL_API int TimDiemXoay();

#pragma once

//#include <memory>
std::shared_ptr<std::vector<NEN>> vector_nen;
std::atomic_bool sansang_doc = false;  // Cờ báo vector_nen sẵn sàng để đọc.
