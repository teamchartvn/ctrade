#include <iostream>
#include <vector>

using namespace std;
// khai báo một contro tới một mảng Bar được update mỗi lần truyền vào high low
vector<pair<double, double>> *bars;



// Struct để lưu trữ một điểm trên biểu đồ giá
struct PricePoint {
    int index; // Chỉ số của điểm trong dãy giá
    double price; // Giá của điểm
};


// Hàm tính chỉ báo Zig Zag
vector<PricePoint> calculateZigZag(const vector<pair<double, double>>& candles, int depth, double deviation, int backstep) {
    vector<PricePoint> zigzagPoints; // Danh sách các điểm Zig Zag

    double lastHigh = candles[0].first; // Giá cao nhất hiện tại BD
    double lastLow = candles[0].second; // Giá thấp nhất hiện tại BAN ĐẦU
    int lastHighIndex = 0; // Chỉ số của điểm cao nhất hiện tại BĐ
    int lastLowIndex = 0; // Chỉ số của điểm thấp nhất hiện tại BĐ

    for (int i = 0; i < candles.size(); ++i) {
    cout << "i = " << i <<endl;
        double currentHigh = candles[i].first;
        double currentLow = candles[i].second;

        // Kiểm tra điểm cao mới
        if (currentHigh > lastHigh) {
            lastHigh = currentHigh;
            lastHighIndex = i;
        }

        // Kiểm tra điểm thấp mới
        if (currentLow < lastLow) {
            lastLow = currentLow;
            lastLowIndex = i;
        }

        // Kiểm tra xem có đạt đủ độ sâu không + độ lệch
        // 
        // Kiếm tra down tren ( xu hướng xuống tạo đáy ; đỉnh = lasthigh ). Nến hiện tại vs nến cao cuối cùng.
        // check độ lệch
        /*
        if (lastHigh >= lastLow * (1 + deviation)) {

            if (i - lastHighIndex >= depth && i- lastLowIndex > backstep) {
                cout << "Xuất hiện đáy \n";
                // đặt lại : lap trong i - backstep tim max = lasthigh
            }
            if (i - lastLowIndex >= depth && i-lastHighIndex>backstep) {
                cout << "Xuất hiện đỉnh \n";
                //đặt lại lsstlow  lap trong i - backstep tim min = lastlow

            }
        }
        */

        cout << lastHigh << " : " << lastLow << endl;

        if (i - lastHighIndex >= depth || i - lastLowIndex >= depth) {
            cout << "khong thoa man Depth " << endl;
            continue;
        }
        
        cout << "Dieu kien thoa man" << endl;
        // tren up thoa man lastHigh -lastLow > devition * lastlow
        if (lastHighIndex > lastLowIndex && lastLow*(1+deviation) <=lastHigh ) { 
            if (i - lastHighIndex > backstep) {
                // Xac nhan dinh 
              // thiet lap gia tri lastlow ke tu dinh
                lastLow = candles[i - backstep].second;
                // thiết lập giá trị lastHigh từ những nến đáy tới nến backstep
                for (int j = i - backstep; j < i; j++) {
                    lastLow = min(lastLow, candles[j].second);
                }
            }
        }
        else {// lastHighIndex <= lastLowIndex tren giam di xuong tu dinh lastHighIndex
            // xác nhận tạo đáy đủ điều kiện backstep +devition
            if (lastHigh * (1 - deviation) > lastLow && i-lastLowIndex > backstep) {
                // thiết lập giá trị lastHigh từ những nến đáy tới nến backstep
                lastHigh = candles[i - backstep].first;
                for (int j = i - backstep; j < i; j++) {
                    lastHigh = max(lastHigh, candles[j].second);
                }
            }
        }

        /*
        if (lastHigh >= lastLow * (1 + deviation)) {
            // khong lap trong backstep
            if (i - lastHighIndex >= depth && lastHighIndex < lastLowIndex) {
                cout << "Xuất hiện đáy \n";
                // luc nay tinh tmp_lasthigh 
                tmp_lasthigh = max(tmp_lasthigh,candles[i].first);
                if (i - lastLowIndex > backstep) // thoa man backstep dat lasthigh = tmp_lasthigh, dat lai tmp_lasthigh
                {
                    lastHigh = tmp_lasthigh;
                    tmp_lasthigh = 0.0;
                }
            }
            else { cout << "chua du Depth tao day \n"; }


            if (i - lastLowIndex >= depth && lastLowIndex < lastHighIndex) {
                cout << "Xuất hiện đỉnh \n";
                // tinh tam gia tri tmp_lastlow
                tmp_lasthigh = min(tmp_lastlow, candles[i].second);
                if (i - lastHighIndex > backstep) // thoa man backstep dat lasthigh = tmp_lastlow, dat lai tmp_lastlow
                {
                    lastLow = tmp_lastlow;
                    tmp_lastlow = 0.0;
                }
            }
            else { cout << "chua du Depth tao dinh \n"; }

        }
        else {
        cout << "Devition ko dat\n";
        }

        */
        

        
      
    }

    return zigzagPoints;
}




class ZigZag
{
public:
    ZigZag(int,int,double);
    ~ZigZag();
  void  Capnhat(double,double);

private:
    int backstep;
    double devition,last_high,last_low;
    int depth;
    //vector<pair<double, double>>Bars;

};

ZigZag::ZigZag(int depth, int btep, double devition) {
    this->backstep = btep;
    this->depth  = depth;
    this->devition = devition;
}


ZigZag::~ZigZag()
{
}

void ZigZag::Capnhat(double high,double low) {

}

int main() {
    // Dữ liệu giá
    vector<pair<double, double>> candles = {
        {100, 90}, {105, 100}, {115, 95}, {115, 86}, {120, 110},
        {115, 105}, {105, 82}, {95, 85}, {100, 90}, {105, 95}
    };

    // Tham số của chỉ báo Zig Zag
    int depth = 65;
    double deviation = 0.2;
    int backstep = 2;

    // Tính toán Zig Zag
    vector<PricePoint> zigzagPoints = calculateZigZag(candles, depth, deviation, backstep);



    return 0;
}
