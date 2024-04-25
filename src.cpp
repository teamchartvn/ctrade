// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#pragma once
#include "zigzag.h"
#include <iostream>

using namespace std;

// memory_order_release
// Khi một hoạt động atomic được thực hiện với cờ memory_order_release, nó đảm bảo rằng tất cả các hoạt động (bao gồm cả non-atomic) đã được thực hiện trước hoạt động atomic này trong cùng một thread
//SẼ KHÔNG ĐƯỢC HOÃN LẠI (sắp xếp lại thứ tự)  SAU hoạt động atomic. Điều này có nghĩa là, nó ngăn chặn việc “đẩy” các hoạt động ra sau hoạt động atomic.
//
// memory_order_acquire
//Khi một hoạt động atomic được thực hiện với cờ memory_order_acquire, nó đảm bảo rằng tất cả các hoạt động (bao gồm cả non-atomic) sau hoạt động atomic này trong cùng một thread
// SẼ KHÔNG ĐƯỢC thay đổi thứ tự thực hiện trước hoạt động atomic. Điều này có nghĩa là, nó ngăn chặn việc “kéo” các hoạt động ra trước hoạt động atomic.
//


void KhoiTao() {
	vector_nen = std::make_shared<vector<NEN>>();
		khoi_tao = true;      // Bộ nhớ đã được cấp phát cho mảng nến
}



	int TimDiemXoay() {

		return 9991;
	}


	int  NhapDuLieu(double gia_cao, double gia_thap) {



		return 10000;
	}
