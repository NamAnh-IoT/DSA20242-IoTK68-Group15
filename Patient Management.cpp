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
void nhapThongTinBenhNhan(BenhNhan &bn, Node* head, bool kiemTraTrungLap = true, long long idCu = -1) {
    bool trungTen, trungID, trungMa;
    string input;
    do {
        cout << "ID: ";
        getline(cin, input);
        if (!isPositiveInteger(input)) {
            cout << "ID phải là số nguyên dương!\n";
            continue;
        }
        bn.id = stoll(input);
        if (kiemTraTrungLap && bn.id != idCu && kiemTraTrung(head, "", bn.id, "", trungTen, trungID, trungMa) && trungID) {
            cout << "ID bị trùng!\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Ho ten: ";
        getline(cin, bn.hoTen);
        if (!isAlphaSpace(bn.hoTen)) {
            cout << "Tên chỉ được phép chứa chữ cái và dấu cách!\n";
            continue;
        }
        if (kiemTraTrungLap && kiemTraTrung(head, bn.hoTen, -1, "", trungTen, trungID, trungMa) && trungTen) {
            cout << "Tên bị trùng!\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Ma benh nhan: ";
        getline(cin, bn.maBenhNhan);
        if (!isAlnumString(bn.maBenhNhan)) {
            cout << "Mã bệnh nhân chỉ bao gồm chữ cái và số, không có dấu cách hoặc ký tự đặc biệt!\n";
            continue;
        }
        if (kiemTraTrungLap && kiemTraTrung(head, "", -1, bn.maBenhNhan, trungTen, trungID, trungMa) && trungMa) {
            cout << "Mã bệnh nhân bị trùng!\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Tuoi: ";
        getline(cin, input);
        if (!isPositiveInteger(input)) {
            cout << "Tuổi phải là số nguyên dương!\n";
            continue;
        }
        bn.tuoi = stoi(input);
        break;
    } while (true);
    do {
        cout << "Dia chi: ";
        getline(cin, bn.diaChi);
        if (!isAlphaSpace(bn.diaChi)) {
            cout << "Địa chỉ chỉ được phép chứa chữ cái và dấu cách!\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Gioi tinh (Nam/Nu): ";
        getline(cin, bn.GioiTinh);
        for (auto& c : bn.GioiTinh) c = tolower(c);
        if (!isAlphaSpace(bn.GioiTinh) || (bn.GioiTinh != "nam" && bn.GioiTinh != "nu")) {
            cout << "Giới tính chỉ được phép nhập 'Nam' hoặc 'Nu', không chứa ký tự đặc biệt.\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Tien su benh an: ";
        getline(cin, bn.TienSuBenhAn);
        if (!isAlphaSpace(bn.TienSuBenhAn)) {
            cout << "Tiền sử bệnh án chỉ được phép chứa chữ cái và dấu cách!\n";
            continue;
        }
        break;
    } while (true);
    do {
        cout << "Luu tru (1: true, 0: false): ";
        getline(cin, input);
        if (input != "1" && input != "0") {
            cout << "Chỉ được nhập 1 hoặc 0!\n";
            continue;
        }
        bn.luuTru = (input == "1");
        break;
    } while (true);
}
void xuatThongTinBenhNhan(const BenhNhan &bn, int idx = -1) {
    if (idx > 0) cout << "Benh nhan " << idx << ":\n";
    cout << "ID: " << bn.id << endl;
    cout << "Ho ten: " << bn.hoTen << endl;
    cout << "Tuoi: " << bn.tuoi << endl;
    cout << "Dia chi: " << bn.diaChi << endl;
    cout << "Gioi tinh: " << bn.GioiTinh << endl;
    cout << "Ma benh nhan: " << bn.maBenhNhan << endl;
    cout << "Tien su benh an: " << bn.TienSuBenhAn << endl;
    cout << "Luu tru: " << (bn.luuTru ? "true" : "false") << endl;
    cout << "----------------------\n";
}
void inDanhSach(Node* head) {
    int idx = 1;
    if (!head) {
        cout << "Danh sách rỗng!" << endl;
        return;
    }
    while (head) {
        xuatThongTinBenhNhan(head->data, idx++);
        head = head->next;
    }
}
void addPatientAtPosition(Node*& head, Node*& tail, int position) {
    BenhNhan bn;
    nhapThongTinBenhNhan(bn, head, true); 
    Node* node = taoNode(bn);
    if (position <= 0 || head == nullptr) {
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = head;
        cout << "\nDanh sach sau khi them:\n";
        inDanhSach(head);
        return;
    }
    Node* temp = head;
    int idx = 0;
    while (temp->next && idx < position - 1) {
        temp = temp->next; idx++;
    }
    if (!temp->next) {
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
struct DieuKienXoa {
    long long id = -1;
    string ten = "";
    string gioiTinh = "";
    string tienSu = "";
};
void nhapDieuKienXoa(int luaChon, DieuKienXoa &dk) {
    string input;
    if (luaChon == 1 || luaChon == 5) {
        do {
            cout << "Nhập ID: ";
            getline(cin, input);
            if (!isPositiveInteger(input))
                cout << "ID phải là số nguyên dương. Vui lòng nhập lại!\n";
        } while (!isPositiveInteger(input));
        dk.id = stoll(input);
    }
    if (luaChon == 2 || luaChon == 5) {
        do {
            cout << "Nhập họ tên: ";
            getline(cin, dk.ten);
            if (!isAlphaSpace(dk.ten))
                cout << "Tên chỉ được phép chứa chữ cái và dấu cách, không chứa ký tự đặc biệt. Vui lòng nhập lại!\n";
        } while (!isAlphaSpace(dk.ten));
    }
    if (luaChon == 3 || luaChon == 5) {
        do {
            cout << "Nhập giới tính (Nam/Nu): ";
            getline(cin, dk.gioiTinh);
            for (auto& c : dk.gioiTinh) c = tolower(c);
            if (!isAlphaSpace(dk.gioiTinh) || (dk.gioiTinh != "nam" && dk.gioiTinh != "nu"))
                cout << "Giới tính không hợp lệ. Vui lòng nhập lại (Nam/Nu, không có ký tự đặc biệt).\n";
        } while (!isAlphaSpace(dk.gioiTinh) || (dk.gioiTinh != "nam" && dk.gioiTinh != "nu"));
    }
    if (luaChon == 4 || luaChon == 5) {
        do {
            cout << "Nhập tiền sử bệnh án: ";
            getline(cin, dk.tienSu);
            if (!isAlphaSpace(dk.tienSu))
                cout << "Tiền sử bệnh án chỉ được phép chứa chữ cái và dấu cách. Vui lòng nhập lại!\n";
        } while (!isAlphaSpace(dk.tienSu));
    }
}
bool kiemTraNodeCanXoa(const BenhNhan& bn, int luaChon, const DieuKienXoa& dk) {
    if ((luaChon == 1 || luaChon == 5) && bn.id != dk.id) return false;
    if ((luaChon == 2 || luaChon == 5) && bn.hoTen != dk.ten) return false;
    if ((luaChon == 3 || luaChon == 5) && bn.GioiTinh != dk.gioiTinh) return false;
    if ((luaChon == 4 || luaChon == 5) && bn.TienSuBenhAn != dk.tienSu) return false;
    return true;
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
    cin >> luaChon; cin.ignore();
    DieuKienXoa dk;
    nhapDieuKienXoa(luaChon, dk);
    Node* current = head;
    bool found = false;
    while (current) {
        if (kiemTraNodeCanXoa(current->data, luaChon, dk)) {
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
    if (!found)
        cout << "Không tìm thấy bệnh nhân phù hợp!\n";
    else {
        cout << "Danh sách sau khi xóa:\n";
        inDanhSach(head);
    }
}
struct DieuKienTimKiem {
    string ten = "";
    int tuoi = -1;
    string gioiTinh = "";
    string diaChi = "";
};
void nhapDieuKienTimKiem(int luaChon, DieuKienTimKiem& dk) {
    string input;
    if (luaChon == 1 || luaChon == 5) {
        do {
            cout << "Nhập họ tên: ";
            getline(cin, dk.ten);
            if (!isAlphaSpace(dk.ten))
                cout << "Tên chỉ được chứa chữ cái và dấu cách.\n";
        } while (!isAlphaSpace(dk.ten));
    }
    if (luaChon == 2 || luaChon == 5) {
        do {
            cout << "Nhập tuổi: ";
            getline(cin, input);
            if (!isPositiveInteger(input))
                cout << "Tuổi phải là số nguyên dương!\n";
        } while (!isPositiveInteger(input));
        dk.tuoi = stoi(input);
    }
    if (luaChon == 3 || luaChon == 5) {
        do {
            cout << "Nhập giới tính (Nam/Nu): ";
            getline(cin, dk.gioiTinh);
            for (auto& c : dk.gioiTinh) c = tolower(c);
            if (!isAlphaSpace(dk.gioiTinh) || (dk.gioiTinh != "nam" && dk.gioiTinh != "nu"))
                cout << "Giới tính chỉ được phép nhập 'Nam' hoặc 'Nu', không chứa ký tự đặc biệt.\n";
        } while (!isAlphaSpace(dk.gioiTinh) || (dk.gioiTinh != "nam" && dk.gioiTinh != "nu"));
    }
    if (luaChon == 4 || luaChon == 5) {
        do {
            cout << "Nhập địa chỉ: ";
            getline(cin, dk.diaChi);
            if (!isAlphaSpace(dk.diaChi))
                cout << "Địa chỉ chỉ được phép chứa chữ cái và dấu cách!\n";
        } while (!isAlphaSpace(dk.diaChi));
    }
}
bool kiemTraNodeTimKiem(const BenhNhan& bn, int luaChon, const DieuKienTimKiem& dk) {
    if ((luaChon == 1 || luaChon == 5) && bn.hoTen != dk.ten) return false;
    if ((luaChon == 2 || luaChon == 5) && bn.tuoi != dk.tuoi) return false;
    if ((luaChon == 3 || luaChon == 5) && bn.GioiTinh != dk.gioiTinh) return false;
    if ((luaChon == 4 || luaChon == 5) && bn.diaChi != dk.diaChi) return false;
    return true;
}
void searchPatient(Node* head) {
    if (!head) {
        cout << "Danh sách bệnh nhân trống!\n";
        return;
    }
    int luaChon;
    cout << "Chọn tiêu chí tìm kiếm:\n";
    cout << "1. Theo họ tên\n";
    cout << "2. Theo tuổi\n";
    cout << "3. Theo giới tính\n";
    cout << "4. Theo địa chỉ\n";
    cout << "5. Kết hợp nhiều tiêu chí\n";
    cout << "Lựa chọn: ";
    cin >> luaChon; cin.ignore();
    DieuKienTimKiem dk;
    nhapDieuKienTimKiem(luaChon, dk);
    Node *resultHead = nullptr, *resultTail = nullptr;
    for (Node* cur = head; cur; cur = cur->next) {
        if (kiemTraNodeTimKiem(cur->data, luaChon, dk)) {
            Node* foundNode = taoNode(cur->data);
            if (!resultHead) resultHead = resultTail = foundNode;
            else {
                resultTail->next = foundNode;
                foundNode->prev = resultTail;
                resultTail = foundNode;
            }
        }
    }
    if (!resultHead) cout << "Bệnh nhân không tồn tại!\n";
    else {
        cout << "KẾT QUẢ TÌM KIẾM:\n";
        inDanhSach(resultHead);
    }
    while (resultHead) {
        Node* temp = resultHead;
        resultHead = resultHead->next;
        delete temp;
    }
}
void capNhatThongTinBenhNhan(BenhNhan &bn, Node* head) {
    string input;
    bool trungTen, trungID, trungMa;
    cout << "Họ tên mới: ";
    getline(cin, input);
    if (!input.empty() && isAlphaSpace(input) && !(kiemTraTrung(head, input, -1, "", trungTen, trungID, trungMa) && trungTen)) {
        bn.hoTen = input;
    }
    cout << "Mã bệnh nhân mới: ";
    getline(cin, input);
    if (!input.empty() && isAlnumString(input) && !(kiemTraTrung(head, "", -1, input, trungTen, trungID, trungMa) && trungMa)) {
        bn.maBenhNhan = input;
    }
    cout << "Tuổi mới: ";
    getline(cin, input);
    if (!input.empty() && isPositiveInteger(input)) {
        bn.tuoi = stoi(input);
    }
    cout << "Địa chỉ mới: ";
    getline(cin, input);
    if (!input.empty() && isAlphaSpace(input)) {
        bn.diaChi = input;
    }
    cout << "Giới tính mới (Nam/Nu): ";
    getline(cin, input);
    if (!input.empty()) {
        string temp = input;
        for (auto& c : temp) c = tolower(c);
        if (isAlphaSpace(input) && (temp == "nam" || temp == "nu")) {
            bn.GioiTinh = input;
        }
    }
    cout << "Tiền sử bệnh án mới: ";
    getline(cin, input);
    if (!input.empty() && isAlphaSpace(input)) {
        bn.TienSuBenhAn = input;
    }
    cout << "Lưu trữ mới (1: true, 0: false): ";
    getline(cin, input);
    if (!input.empty()) {
        if (input == "1") bn.luuTru = true;
        else if (input == "0") bn.luuTru = false;
    }
}
void UpdatePatient(Node* head) {
    if (!head) {
        cout << "Danh sách bệnh nhân trống!\n";
        return;
    }
    string input;
    long long id;
    Node* current = head;
    do {
        cout << "Nhập ID bệnh nhân cần cập nhật: ";
        getline(cin, input);
        if (!isPositiveInteger(input)) {
            cout << "ID phải là số nguyên dương!\n";
            continue;
        }
        id = stoll(input);
        break;
    } while (true);

    while (current) {
        if (current->data.id == id) break;
        current = current->next;
    }
    if (!current) {
        cout << "Không tìm thấy bệnh nhân có ID này!\n";
        return;
    }
    cout << "\n--- Thông tin hiện tại của bệnh nhân ---\n";
    xuatThongTinBenhNhan(current->data);
    cout << "\n--- Nhập thông tin mới (Enter để giữ nguyên) ---\n";
    capNhatThongTinBenhNhan(current->data, head);
    cout << "\n--- Cập nhật thành công! Thông tin mới của bệnh nhân ---\n";
    xuatThongTinBenhNhan(current->data);
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
