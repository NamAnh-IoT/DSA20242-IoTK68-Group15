#include <stdio.h>
#include <iostream>
#include <string>
#include <Patient Management.cpp>

using namespace std;


/*Các chức năng bạn nêu ra đã hợp lý và sát với thực tế quản lý bệnh án:
Ghi nhận lịch sử khám bệnh, điều trị: Mỗi bệnh nhân sẽ có một hoặc nhiều lần khám, mỗi lần là một bản ghi riêng (date, chẩn đoán, điều trị...).
Lưu kết quả xét nghiệm, hình ảnh chẩn đoán: Cần lưu đường dẫn file/hình ảnh (hoặc mã hóa mô tả) và ngày thực hiện, loại xét nghiệm/hình ảnh.
Tra cứu bệnh lý theo thời gian: Cho phép tìm kiếm, lọc các bệnh án của bệnh nhân theo mốc thời gian.
2. Các điểm cần bổ sung/chỉnh sửa để hoàn thiện ý tưởng:
Quan hệ dữ liệu: Với cấu trúc hiện tại, mỗi bệnh nhân có thể có nhiều bệnh án (1-n). Cần struct MedicalRecord và liên kết nó với BenhNhan qua danh sách liên kết đơn hoặc đôi (tận dụng Node từ Patient Management.cpp).
Thông tin cần có trong 1 bệnh án:
Mã bệnh án (unique, có thể tự động tăng hoặc nhập)
Ngày khám/chữa bệnh (string hoặc struct Date)
Chẩn đoán, phương pháp điều trị
Danh sách kết quả xét nghiệm/hình ảnh (có thể là mảng tĩnh nhỏ struct hoặc danh sách liên kết nếu muốn mở rộng)
Ghi chú thêm (nếu có)
Chức năng CRUD cho MedicalRecord: Thêm, xóa, sửa, xem bệnh án gắn với từng bệnh nhân.
Tìm kiếm và lọc: Theo thời gian, loại bệnh, từ khóa...
Không sử dụng vector: Dùng danh sách liên kết hoặc mảng tĩnh nhỏ.
Tái sử dụng hàm kiểm tra nhập liệu, xuất thông tin: Có thể dùng lại các hàm kiểm tra tính hợp lệ từ Patient Management.cpp.
3. Các lưu ý thêm:
Nếu muốn đơn giản, có thể chỉ lưu đường dẫn file hình ảnh thay vì nội dung ảnh thật.
Cân nhắc thêm chức năng xuất toàn bộ lịch sử bệnh án một bệnh nhân (xuất báo cáo).
Nếu muốn mở rộng: có thể cho phép liên kết nhanh giữa bệnh nhân và bệnh án qua ID.*/
struct MedicalRecord {
    long long recordID;
    long long patientID;
    string ngayKham;
    string loaiBenhAn;
    string bacSiPhuTrach;
    string chanDoan;
    string phuongPhapDieuTri;
    string ketQuaXetNghiem;
    string hinhAnhChanDoan;
    string trangThai;
    tring ghiChu;
};
struct NodeRecord {
    MedicalRecord data;
    NodeRecord* next;
    NodeRecord* prev;
};


NodeRecord* taoNode(const MedicalRecord& mr) {
    NodeRecord* node = new NodeRecord;
    node->data = mr;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}


void addFirst(NodeRecord*& head, NodeRecord*& tail, const MedicalRecord& mr) {
    NodeRecord* node = taoNode(mr);
    node->prev = nullptr;
    node->next = head;
    if (head != nullptr) {
        head->prev = node;
    } else {
        tail = node;
    }
    head = node;
}

void addLast(NodeRecord*& head, NodeRecord*& tail, const MedicalRecord& mr) {
    NodeRecord* node = taoNode(mr);
    node->next = nullptr;
    node->prev = tail;
    if (tail != nullptr) {
        tail->next = node;
    } else {
        head = node;
    }
    tail = node;
}

void xuatThongTin(const MedicalRecord& mr, int idx = -1) {
    if (idx > 0) std::cout << "Bệnh án " << idx << ":\n";
    cout << "Mã bệnh án: " << mr.recordID << endl;
    cout << "Ngày khám: " << mr.ngayKham << endl;
    cout << "Chẩn đoán: " << mr.chanDoan << endl;
    cout << "Phương pháp điều trị: " << mr.phuongPhapDieuTri << endl;
    cout << "Kết quả xét nghiệm: " << mr.ketQuaXetNghiem << endl;
    cout << "Hình ảnh chẩn đoán: " << mr.hinhAnhChanDoan << endl;
    cout << "Ghi chú: " << mr.ghiChu << std::endl;
    cout << "----------------------\n";
}

void inDanhSach(NodeRecord* head) {
    int idx = 1;
    if (!head) {
        cout << "Danh sách bệnh án rỗng!" << endl;
        return;
    }
    while (head) {
        xuatThongTin(head->data, idx++);
        head = head->next;
    }
}
bool isPositiveInteger(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    if (str.length() > 1 && str[0] == '0') return false;
    return stoll(str) > 0;
}
bool isAlphaSpace(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!(isalpha(c) || c == ' ' || (unsigned char)c >= 128)) return false;
    }
    return true;
}
bool isAlnumString(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalnum(c)) return false;
    }
    return true;
}
bool kiemTraTrungRecord(NodeRecord* head, long long recordID) {
    NodeRecord* current = head;
    while (current) {
        if (current->data.recordID == recordID) return true;
        current = current->next;
    }
    return false;
}
