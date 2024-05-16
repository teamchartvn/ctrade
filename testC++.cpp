
#include "Header.h"
#include <windows.h>
#define BUF_SIZE 128

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
std::vector <KHUNGNEN> tatca_nen;

int KhoiTao() {
	if (khoi_tao.load(std::memory_order_relaxed) == true) {
		return -1;
	}

	KHUNGNEN M1;
	M1.dodainen = 60;
	M1.kieu = TIME;
	M1.mang_nen = std::make_unique<std::vector<NEN>>();
	
	tatca_nen.push_back(std::move(M1)); // M1 không còn sở hữu mang_nen
}




int TimDiemXoay() {
	//return (*tatca_nen)[0].dodainen;
	return huy;
}

// có thể viết theo template cho kiểu tickrelay or kiểu on close : chỉnh sau
//int CAPNHATDATA(double gia_cao, double gia_thap) {
//
//	// viết cập nhật nến như nào ? mỗi lần có sự kiện call hàm update nến trong class nến hay tự tính bên ngoài này ? và cập nhật sau ?
//	return 999;
//}



//NEN::NEN() {
//	
//	
//}
//
//NEN::~NEN() {
//	giamo = giacao = giathap = giamo = 0;
//}



BYTE* TaoVungNho() {
	HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // Sử dụng bộ nhớ hệ thống
		NULL,                    // Bảo mật mặc định
		PAGE_READWRITE,          // Truy cập đọc / ghi
		0,                       // Kích thước tối đa của tệp phần trên
		BUF_SIZE,                // Kích thước tối đa của tệp phần dưới
		L"Buf");                  // Tên của vùng nhớ chia sẻ

	if (hMapFile == NULL) {
		std::cout << "Không tạo được vùng nhớ chia sẻ \n" << std::endl;
		return nullptr;
	}

	BYTE* pBuf = (BYTE*)MapViewOfFile(
		hMapFile,               // Handle tới vùng nhớ chia sẻ
		FILE_MAP_ALL_ACCESS,    // Quyền truy cập đọc / ghi
		0,
		0,
		BUF_SIZE);
	if (pBuf == NULL) {
		std::cout << " Không tạo được con trỏ tới vùng nhớ \n" << std::endl;
		CloseHandle(hMapFile);
		return  nullptr;
	}

	std::atomic<int>* flag = new (pBuf + BUF_SIZE - 1) std::atomic<int>;

	std::cout << "trong hàm : " << pBuf << std::endl;
	return pBuf;

}

int main() {

	std::cout << " bat dau chay" << std::endl;
	////KhoiTao();
	//void* ctr = TaoVungNho();
	//if (ctr = nullptr) {
	//	std::cout << " Vung nhớ này null " << std::endl;
	//}
	//std::cout << "địa chỉ của vùng nhớ chia sẻ : " << ctr << std::endl;
	//std::cout << "địa chỉ của ctr : " << &ctr << std::endl;
	//delete ctr;
	const DWORD SHARED_MEMORY_SIZE = 128;
	 // Tạo vùng nhớ chia sẻ
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEMORY_SIZE, L"Buf");
	if (hMapFile == NULL)
	{
		std::cout << "CreateFileMapping failed with error: " << GetLastError() << std::endl;
		return 1;
	}

	// Ánh xạ vùng nhớ chia sẻ vào không gian địa chỉ của tiến trình
	char* pBuf = static_cast<char*>(MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHARED_MEMORY_SIZE));
	if (pBuf == nullptr)
	{
		std::cout << "MapViewOfFile failed with error: " << GetLastError() << std::endl;
		CloseHandle(hMapFile);
		return 1;
	}
	std::cout << " bat dau vong lap" << std::endl;
	// Đọc dữ liệu từ vùng nhớ chia sẻ
	while (true)
	{
		if (pBuf[SHARED_MEMORY_SIZE - 1] == 1)
		{
			std::cout << "Data in shared memory: ";
			for (DWORD i = 0; i < SHARED_MEMORY_SIZE - 1; i++)
			{
				std::cout << pBuf[i];
			}
			

			// Thiết lập cờ Flag về 0 sau khi đọc xong
			pBuf[SHARED_MEMORY_SIZE - 1] = 0;
		}

		// Thực hiện công việc khác hoặc đợi
		// ...
		std::cout << "khong co gi" << std::endl;
		Sleep(200);
	}

	// Hủy ánh xạ và đóng vùng nhớ chia sẻ
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);

	return 0;

        // Thực hiện công việc khác hoặc đợi
        // ...
    
}
