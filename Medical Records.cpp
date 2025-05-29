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
void nhapThongTin(MedicalRecord& mr, NodeRecord* head) {
    string input;
    do {
        cout << "Nhập mã bệnh án: ";
        getline(cin, input);
        if (!isPositiveInteger(input)) {
            cout << "Mã bệnh án phải là số nguyên dương!\n";
            continue;
        }
        mr.recordID = stoll(input);
        if (kiemTraTrungRecord(head, mr.recordID)) {
            cout << "Mã bệnh án bị trùng!\n";
            continue;
        }
        break;
    } while (true);
    cout << "Nhập ID bệnh nhân: ";
    getline(cin, input);
    if (isPositiveInteger(input)) mr.patientID = stoll(input); else mr.patientID = -1;
    cout << "Ngày khám: ";
    getline(cin, mr.ngayKham);
    cout << "Loại bệnh án: ";
    getline(cin, mr.loaiBenhAn);
    cout << "Bác sĩ phụ trách: ";
    getline(cin, mr.bacSiPhuTrach);
    cout << "Chẩn đoán: ";
    getline(cin, mr.chanDoan);
    cout << "Phương pháp điều trị: ";
    getline(cin, mr.phuongPhapDieuTri);
    cout << "Kết quả xét nghiệm: ";
    getline(cin, mr.ketQuaXetNghiem);
    cout << "Hình ảnh chẩn đoán: ";
    getline(cin, mr.hinhAnhChanDoan);
    cout << "Trạng thái: ";
    getline(cin, mr.trangThai);
    cout << "Ghi chú: ";
    getline(cin, mr.ghiChu);
}
NodeRecord* timRecordTheoID(NodeRecord* head, long long recordID) {
    while (head) {
        if (head->data.recordID == recordID) return head;
        head = head->next;
    }
    return nullptr;
}
void capNhatRecord(NodeRecord* head) {
    string input;
    cout << "Nhập mã bệnh án cần cập nhật: ";
    getline(cin, input);
    if (!isPositiveInteger(input)) {
        cout << "Mã bệnh án không hợp lệ!\n";
        return;
    }
    long long recordID = stoll(input);
    NodeRecord* node = timRecordTheoID(head, recordID);
    if (!node) {
        cout << "Không tìm thấy bệnh án này!\n";
        return;
    }
    MedicalRecord& mr = node->data;
    cout << "Nhập thông tin mới (nhấn Enter để giữ nguyên):\n";
    cout << "Ngày khám [" << mr.ngayKham << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.ngayKham = input;
    cout << "Loại bệnh án [" << mr.loaiBenhAn << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.loaiBenhAn = input;
    cout << "Bác sĩ phụ trách [" << mr.bacSiPhuTrach << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.bacSiPhuTrach = input;
    cout << "Chẩn đoán [" << mr.chanDoan << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.chanDoan = input;
    cout << "Phương pháp điều trị [" << mr.phuongPhapDieuTri << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.phuongPhapDieuTri = input;
    cout << "Kết quả xét nghiệm [" << mr.ketQuaXetNghiem << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.ketQuaXetNghiem = input;
    cout << "Hình ảnh chẩn đoán [" << mr.hinhAnhChanDoan << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.hinhAnhChanDoan = input;
    cout << "Trạng thái [" << mr.trangThai << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.trangThai = input;
    cout << "Ghi chú [" << mr.ghiChu << "]: ";
    getline(cin, input);
    if (!input.empty()) mr.ghiChu = input;
    cout << "Đã cập nhật bệnh án!\n";
}
void xoaRecordTheoID(NodeRecord*& head, NodeRecord*& tail, long long recordID) {
    NodeRecord* node = head;
    while (node) {
        if (node->data.recordID == recordID) {
            if (node == head) head = node->next;
            if (node == tail) tail = node->prev;
            if (node->prev) node->prev->next = node->next;
            if (node->next) node->next->prev = node->prev;
            delete node;
            cout << "Đã xóa bệnh án " << recordID << endl;
            return;
        }
        node = node->next;
    }
    cout << "Không tìm thấy bệnh án có mã này!\n";
}
