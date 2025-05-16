#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

struct BenhNhan{
    long long id;
    string hoTen;
    int tuoi;
    string diaChi;
    string GioiTinh;
    string maBenhNhan;
    string TienSuBenhAn;
    bool luuTru;
};
struct Node {
    BenhNhan data;
    Node* next;
    Node* prev;
};
Node* taoNode(BenhNhan bn) {
    Node* node = new Node;
    node->data = bn;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

void addFirst(Node*& head, Node*& tail, BenhNhan& bn) {
    Node* node = new Node;
    node->data = bn;
    node->prev = nullptr;
    node->next = head;
    if (head != nullptr) {
        head->prev = node;
    } else {
        tail = node;
    }
    head = node;
}

void addLast(Node*& head, Node*& tail, BenhNhan& bn) {
    Node* node = new Node;
    node->data = bn;
    node->next = nullptr;
    node->prev = tail;
    if (tail != nullptr) {
        tail->next = node;
    } else {
        head = node;
    }
    tail = node;
}

void inDanhSach(Node* head) {
    int idx = 1;
    if (head == nullptr) {
    cout << "Danh sách rỗng!" << endl;
    return;
}
    while (head != nullptr) {
        cout << "Benh nhan " << idx++ << ":\n";
        cout << "ID: " << head->data.id << endl;
        cout << "Ho ten: " << head->data.hoTen << endl;
        cout << "Tuoi: " << head->data.tuoi << endl;
        cout << "Dia chi: " << head->data.diaChi << endl;
        cout << "Gioi tinh: " << head->data.GioiTinh << endl;
        cout << "Ma benh nhan: " << head->data.maBenhNhan << endl;
        cout << "Tien su benh an: " << head->data.TienSuBenhAn << endl;
        cout << "Luu tru: " << (head->data.luuTru ? "true" : "false") << endl;
        cout << "----------------------\n";
        head = head->next;
    }
}


bool kiemTraTrung(Node* head, const string& ten, long long id, const string& maBN, bool& trungTen, bool& trungID, bool& trungMa) {
    trungTen = trungID = trungMa = false;
    Node* current = head;
    while(current) {
        if(current->data.hoTen == ten) trungTen = true;
        if(current->data.id == id) trungID = true;
        if(current->data.maBenhNhan == maBN) trungMa = true;
        current = current->next;
    }
    return trungTen || trungID || trungMa;
}

void addPatientAtPosition(Node*& head, Node*& tail, int position) {
    BenhNhan bn;
    bool trungTen, trungID, trungMa;
    do {
        do {
            cout << "ID: "; cin >> bn.id;
            if(bn.id <= 0) cout << "ID phải là số dương!\n";
        } while(bn.id <= 0);
        cin.ignore();
        cout << "Ho ten: ";
        getline(cin, bn.hoTen);
        cout << "Ma benh nhan: ";
        getline(cin, bn.maBenhNhan);
        if (kiemTraTrung(head, bn.hoTen, bn.id, bn.maBenhNhan, trungTen, trungID, trungMa)) {
            cout << "Lỗi: ";
            if (trungID) cout << "ID ";
            if (trungMa) cout << "Mã bệnh nhân ";
            if (trungTen) cout << "Tên ";
            cout << "bạn nhập bị trùng với thông tin bệnh nhân có sẵn, vui lòng nhập lại các trường bị trùng!\n";
        }
    } while (kiemTraTrung(head, bn.hoTen, bn.id, bn.maBenhNhan, trungTen, trungID, trungMa));
    do {
        cout << "Tuoi: "; cin >> bn.tuoi;
        if (bn.tuoi <= 0) cout << "Tuổi phải là số nguyên dương!\n";
    } while (bn.tuoi <= 0);
    cin.ignore();

    cout << "Dia chi: "; getline(cin, bn.diaChi);
    do {
        cout << "Gioi tinh (Nam/Nu): "; getline(cin, bn.GioiTinh);
        for (auto& c : bn.GioiTinh) c = tolower(c);
        if (bn.GioiTinh != "nam" && bn.GioiTinh != "nu") {
            cout << "Giới tính chỉ được nhập Nam hoặc Nu!\n";
        }
    } while (bn.GioiTinh != "nam" && bn.GioiTinh != "nu");

    cout << "Tien su benh an: "; getline(cin, bn.TienSuBenhAn);
    cout << "Luu tru (1: true, 0: false): "; cin >> bn.luuTru;
    cin.ignore();
    
    Node* node = new Node;
    node->data = bn;
    node->next = nullptr;
    node->prev = nullptr;

    if (position <= 0 || head == nullptr) {
        node->next = head;
        if (head != nullptr) head->prev = node;
        head = node;
        if (tail == nullptr) tail = head;
        return;
    }
    Node* temp = head;
    int idx = 0;
    while (temp->next != nullptr && idx < position - 1) {
        temp = temp->next; idx++;
    }
    if (temp->next == nullptr) {
        temp->next = node;
        node->prev = temp;
        tail = node;
    } else {
        node->next = temp->next;
        node->prev = temp;
        temp->next->prev = node;
        temp->next = node;
    }
    cout << "\nDanh sach sau khi them:\n";
    inDanhSach(head);
}

void removePatient(Node*& head, Node*& tail) {
    if (!head) {
        cout << "Danh sách bệnh nhân trống! Thao tác vô hiệu!\n";
        return;
    }
    int luaChon;
    cout << "Chọn cách xóa:\n";
    cout << "1. Theo ID\n";
    cout << "2. Theo họ tên\n";
    cout << "3. Theo giới tính\n";
    cout << "4. Theo tiền sử bệnh án\n";
    cout << "5. Kết hợp nhiều điều kiện\n";
    cout << "Lựa chọn: ";
    cin >> luaChon;
    cin.ignore();
    long long id = -1;
    string ten = "", gioiTinh = "", tienSu = "";

    if (luaChon == 1 || luaChon == 5) {
        cout << "Nhập ID: ";
        cin >> id;
        cin.ignore();
    }
    if (luaChon == 2 || luaChon == 5) {
        cout << "Nhập họ tên: ";
        getline(cin, ten);
    }
    if (luaChon == 3 || luaChon == 5) {
        do {
            cout << "Nhập giới tính (Nam/Nu): ";
            getline(cin, gioiTinh);
            for (auto& c : gioiTinh) c = tolower(c);
            if (gioiTinh != "nam" && gioiTinh != "nu")
               cout << "Giới tính không hợp lệ. Vui lòng nhập lại (Nam/Nu).\n";
        } while (gioiTinh != "nam" && gioiTinh != "nu");
    }
    if (luaChon == 4 || luaChon == 5) {
        cout << "Nhập tiền sử bệnh án: ";
        getline(cin, tienSu);
    }

    Node* current = head;
    bool found = false;
    while (current) {
        bool match = true;
        if (luaChon == 1 || luaChon == 5) if (current->data.id != id) match = false;
        if (luaChon == 2 || luaChon == 5) if (current->data.hoTen != ten) match = false;
        if (luaChon == 3 || luaChon == 5) if (current->data.GioiTinh != gioiTinh) match = false;
        if (luaChon == 4 || luaChon == 5) if (current->data.TienSuBenhAn != tienSu) match = false;

        if (match) {
            found = true;
            
            string xacNhan;
            cout << "Bạn có chắc chắn muốn xóa bệnh nhân ";
            if (luaChon == 1 || luaChon == 5) cout << "có ID: " << current->data.id << " ";
            if (luaChon == 2 || luaChon == 5) cout << "tên: " << current->data.hoTen << " ";
            if (luaChon == 3 || luaChon == 5) cout << "giới tính: " << current->data.GioiTinh << " ";
            if (luaChon == 4 || luaChon == 5) cout << "bệnh án: " << current->data.TienSuBenhAn << " ";
            cout << "không? (y/n): ";
            getline(cin, xacNhan);

            if (xacNhan == "y" || xacNhan == "Y") {

                Node* toDelete = current;
                if (toDelete == head && toDelete == tail) { 
                    head = tail = nullptr;
                } else if (toDelete == head) {
                    head = head->next;
                    if (head) head->prev = nullptr;
                } else if (toDelete == tail) {
                    tail = tail->prev;
                    if (tail) tail->next = nullptr;
                } else {
                    toDelete->prev->next = toDelete->next;
                    toDelete->next->prev = toDelete->prev;
                }
                current = current->next;
                delete toDelete;
                continue; 
            }
        }
        current = current->next;
    }

    if (!found) cout << "Không tìm thấy bệnh nhân phù hợp!\n";
    else {
        cout << "Danh sách sau khi xóa:\n";
        inDanhSach(head);
    }
}

Node* node = new (nothrow) Node;
if (!node) {
    cerr << "Lỗi cấp phát bộ nhớ!" << endl;
    return;
}


/*
void luuDanhSachVaoFile(Node* head, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }
    Node* current = head;
    while (current) {
        fout << current->data.id << '\t'
             << current->data.hoTen << '\t'
             << current->data.tuoi << '\t'
             << current->data.diaChi << '\t'
             << current->data.GioiTinh << '\t'
             << current->data.maBenhNhan << '\t'
             << current->data.TienSuBenhAn << '\t'
             << current->data.luuTru << '\n';
        current = current->next;
    }
    fout.close();
    cout << "Da luu danh sach vao " << filename << endl;
}*/  //TEMPORARY OFFLINE


/*int nhapSoNguyen(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Vui lòng nhập số nguyên hợp lệ!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

int nhapSoNguyenDuong(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Vui lòng nhập số nguyên dương hợp lệ!\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}*/ //TEMPORARY OFFLINE
