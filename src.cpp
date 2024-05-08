#include "pch.h"
#include "zz.h"



// memory_order_release
// Khi một hoạt động atomic được thực hiện với cờ memory_order_release, nó đảm bảo rằng tất cả các hoạt động (bao gồm cả non-atomic) đã được thực hiện trước hoạt động atomic này trong cùng một thread
//SẼ KHÔNG ĐƯỢC HOÃN LẠI (sắp xếp lại thứ tự)  SAU hoạt động atomic. Điều này có nghĩa là, nó ngăn chặn việc “đẩy” các hoạt động ra sau hoạt động atomic.
//
// memory_order_acquire
//Khi một hoạt động atomic được thực hiện với cờ memory_order_acquire, nó đảm bảo rằng tất cả các hoạt động (bao gồm cả non-atomic) sau hoạt động atomic này trong cùng một thread
// SẼ KHÔNG ĐƯỢC thay đổi thứ tự thực hiện trước hoạt động atomic. Điều này có nghĩa là, nó ngăn chặn việc “kéo” các hoạt động ra trước hoạt động atomic.
//


std::unique_ptr<std::vector<NEN>> vector_nen;
//std::unique_ptr<std::vector<KHUNGNEN>> tatca_nen;
std::vector <KHUNGNEN>  tatca_nen;
int KHOI_TAO::mode = 0; 
int KHOI_TAO::so_chart = 0;


inline void KHUNGNEN::CapNhatNen(NEN & nhap) {
	// kiểm tra time 
}


KHUNGNEN::KHUNGNEN() {
	mang_nen = std::make_unique<std::vector<NEN>>();
	sophantu = 0; // ko có phần tử ban đâu  mang_nen->size();
}




int KhoiTao(CHE_DO md) {
	if (khoi_tao.load(std::memory_order_relaxed) == true) {
		return -1;
	}

	//vector_nen = std::make_unique<std::vector<NEN>>(1000);
	//khoi_tao.store(true, memory_order_release);
	//tatca_nen = std::make_unique<std::vector<KHUNGNEN>>(soloainen.size());  // Cấp phát vector tatcanen có số phần tử = số loại nến cần chạy
	
		khoi_tao.store(true, memory_order_release);

		KHUNGNEN M1, M3, D100;
			
			M1.kieu = TIME;
			M1.dodainen = 60;
			
			tatca_nen.push_back(std::move(M1));

			M3.kieu = TIME;
			M3.dodainen = 3;
			tatca_nen.push_back(std::move(M3));

			D100.kieu = DELTA;
			D100.dodainen = 100;
			
			tatca_nen.push_back(std::move(D100));

		// Thiết lập thông số cấu hình  cho khởi tạo 
			KHOI_TAO::so_chart = tatca_nen.size();
			KHOI_TAO::mode = md;
		//reset lại giá trị đã khởi tạo ở hàm tiêu thụ
		khoi_tao.store(std::memory_order_relaxed);
		
		// delete tatca_nen;
		// khỏi tạo M1

		return tatca_nen.size();
	
	

	
}  




int TimDiemXoay() {
	//return (*tatca_nen)[0].dodainen;
	return tatca_nen[0].mang_nen->size();
}


void CAPNHAT( NEN nhap) {
	for (int i = 0; i < KHOI_TAO::so_chart; i++) {
		// NEN(j).CapNhatNen()
		//(*(tatca_nen[i].mang_nen))[tatca_nen[i].mang_nen->size()].CapNhatNen(nhap); // có cần thiết không ?>>> chức năng của hàm này đâu cần gọi tới chính xác từng phần tử ?
	/*   |------vector NEN------ |--- phần tử nến cuối cùng ---------|   */
		tatca_nen[0].CapNhatNen(nhap);
	}
}
