#include <stdio.h>
#include <iostream>
#include <string>
#include "Patient Management.cpp"

using namespace std;

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
    string ghiChu;
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
bool kiemTraThongTinMedicalRecord(const MedicalRecord& mr, NodeRecord* head) {
    if (!isPositiveInteger(to_string(mr.recordID)) || kiemTraTrungRecord(head, mr.recordID)) return false;
    if (!isPositiveInteger(to_string(mr.patientID))) return false;
    if (mr.ngayKham.empty()) return false;
    if (mr.chanDoan.empty()) return false;
    if (mr.phuongPhapDieuTri.empty()) return false;
    if (mr.trangThai.empty()) return false;
    if (!mr.bacSiPhuTrach.empty() && !isAlphaSpace(mr.bacSiPhuTrach)) return false;
    if (!mr.loaiBenhAn.empty() && !isAlnumString(mr.loaiBenhAn)) return false;
    return true;
}
void nhapThongTin(MedicalRecord& mr, NodeRecord* head) {
    string input;
    do {
        cout << "Nhập mã bệnh án: "; getline(cin, input);
    } while (!isPositiveInteger(input) || kiemTraTrungRecord(head, stoll(input)));
    mr.recordID = stoll(input);

    do { cout << "Nhập ID bệnh nhân: "; getline(cin, input); }
    while (!isPositiveInteger(input));
    mr.patientID = stoll(input);

    do { cout << "Ngày khám: "; getline(cin, mr.ngayKham); }
    while (mr.ngayKham.empty());
    cout << "Loại bệnh án: "; getline(cin, mr.loaiBenhAn);
    cout << "Bác sĩ phụ trách: "; getline(cin, mr.bacSiPhuTrach);
    do { cout << "Chẩn đoán: "; getline(cin, mr.chanDoan); }
    while (mr.chanDoan.empty());
    do { cout << "Phương pháp điều trị: "; getline(cin, mr.phuongPhapDieuTri); }
    while (mr.phuongPhapDieuTri.empty());
    cout << "Kết quả xét nghiệm: "; getline(cin, mr.ketQuaXetNghiem);
    cout << "Hình ảnh chẩn đoán: "; getline(cin, mr.hinhAnhChanDoan);
    do { cout << "Trạng thái: "; getline(cin, mr.trangThai); }
    while (mr.trangThai.empty());
    cout << "Ghi chú: "; getline(cin, mr.ghiChu);
}
NodeRecord* timRecordTheoID(NodeRecord* head, long long recordID) {
    while (head) {
        if (head->data.recordID == recordID) return head;
        head = head->next;
    }
    return nullptr;
}
void themBenhAn(NodeRecord*& head, NodeRecord*& tail) {
    MedicalRecord mr;
    nhapThongTin(mr, head);
    if (!kiemTraThongTinMedicalRecord(mr, head)) {
        cout << "Không thể thêm bệnh án do dữ liệu không hợp lệ!\n";
        return;
    }
    addLast(head, tail, mr);
    cout << "Đã thêm bệnh án thành công!\n";
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
<< "Bác sĩ phụ trách [" << mr.bacSiPhuTrach << "]: ";
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
    if (!kiemTraThongTinMedicalRecord(mr, head)) {
        cout << "Dữ liệu cập nhật không hợp lệ. Không lưu thay đổi!\n";
        return;
    }

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
