#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


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

//================================================== Tùng béo ==================================================
#define MAX 100
#define TOTAL_ROOMS 52
#define MAX_NURSES_PER_ROOM 2


typedef struct {
    char name[100];
    char shift[50];
} Nurse;

typedef struct {
    BenhNhan patients[MAX];
    int patientCount;

    Nurse nurses[MAX_NURSES_PER_ROOM];
    int nurseCount;

    char type[2];
    int tier;
} Room;

int patientIDCounter = 1;

//return giá trị luôn rồi thì return MAX là như thế nào?
int getMaxPatientsPerRoom(const char* type) {
    if (strcmp(type, "S") == 0) return 2;
    if (strcmp(type, "A") == 0) return 6;
    if (strcmp(type, "F") == 0) return 12;
    if (strcmp(type, "E") == 0) return 30;
    if (strcmp(type, "O") == 0) return 1;
    return MAX;
}

//kiểm tra string có phải string chữ không à?
int isValidString(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}


//----------------------Hàm liên quan đến Nurse-----------------------------

void addNurse(Room* room, Nurse newNurse) {
    if (room->nurseCount >= MAX_NURSES_PER_ROOM) {
        printf("Phòng đã đủ %d y tá, không thể thêm.\n", MAX_NURSES_PER_ROOM);
        return;
    }
    room->nurses[room->nurseCount++] = newNurse;
    printf("Đã thêm y tá: %s\n", newNurse.name);
}

void deleteNurse(Room* room, const char* name) {
    for (int i = 0; i < room->nurseCount; i++) {
        if (strcmp(room->nurses[i].name, name) == 0) {
            for (int j = i; j < room->nurseCount - 1; j++) {
                room->nurses[j] = room->nurses[j + 1];
            }
            room->nurseCount--;
            printf("Đã xóa y tá: %s\n", name);
            return;
        }
    }
    printf("Không tìm thấy y tá tên: %s\n", name);
}

void printNurses(const Room* room) {
    printf("\nDanh sách y tá:\n");
    for (int i = 0; i < room->nurseCount; i++) {
        Nurse n = room->nurses[i];
        printf("%d. %s - Ca trực: %s\n", i + 1, n.name, n.shift);
    }
}


//----------------------Hàm liên quan đến Room-----------------------------
void initRoom(Room* room, const char* type, int tier) {
    strcpy(room->type, type);
    room->tier = tier;
    room->patientCount = 0;
    room->nurseCount = 0;
}

void setupHospital(Room hospital[]) {
    int index = 0;
    for (int i = 0; i < 6; i++) initRoom(&hospital[index++], "S", 5000000);
    for (int i = 0; i < 12; i++) initRoom(&hospital[index++], "A", 3000000);
    for (int i = 0; i < 30; i++) initRoom(&hospital[index++], "F", 1000000);
    for (int i = 0; i < 2; i++) initRoom(&hospital[index++], "E", 0);
    for (int i = 0; i < 2; i++) initRoom(&hospital[index++], "O", 0);
}

void printRoomInfo(const Room* room) {
    printf("\n== Thông tin phòng ==\n");
    printf("Loại phòng: %s-tier\n", room->type);
    printf("Giá tiền dịch vụ: %d\n", room->tier);
    printf("Số bệnh nhân: %d/%d\n", room->patientCount, getMaxPatientsPerRoom(room->type));
    printf("Số y tá: %d/%d\n", room->nurseCount, MAX_NURSES_PER_ROOM);
}

Room* findAvailableRoom(Room hospital[], const char* type) {
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        if (strcmp(hospital[i].type, type) == 0 &&
            hospital[i].patientCount < getMaxPatientsPerRoom(type)) {
            return &hospital[i];
        }
    }
    return NULL;
}

void printHospitalReport(Room hospital[]) {
    int totalPatients = 0;
    long totalRevenue = 0;
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        totalPatients += hospital[i].patientCount;
        totalRevenue += hospital[i].patientCount * hospital[i].tier;
    }
    printf("\n===== BÁO CÁO BỆNH VIỆN =====\n");
    printf("Tổng số bệnh nhân: %d\n", totalPatients);
    printf("Tổng tiền viện phí (ước tính): %ld VND\n", totalRevenue);
}

//================================================== Tuấn ==================================================
#define MAX_THUOC 100
#define MAX_TEN 50
#define MAX_DONVI 20
#define MAX_ID 10
#define MAX_HANSUDUNG 20

//-------------------------- CAU TRUC THUOC --------------------------
typedef struct {
    char id[MAX_ID];
    char ten[MAX_TEN];
    char donVi[MAX_DONVI];
    int soLuong;
    double gia;
    char hanSuDung[MAX_HANSUDUNG];
} Thuoc;

//-------------------------- HAM THEM THUOC --------------------------
void themThuoc(Thuoc danhSachThuoc[], int* soLuongThuoc) {
    if (*soLuongThuoc >= MAX_THUOC) {
        printf("Danh sach thuoc da day!\n");
        return;
    }

    printf("Nhap ma thuoc: ");
    fgets(danhSachThuoc[*soLuongThuoc].id, MAX_ID, stdin);
    danhSachThuoc[*soLuongThuoc].id[strcspn(danhSachThuoc[*soLuongThuoc].id, "\n")] = 0;

    printf("Nhap ten thuoc: ");
    fgets(danhSachThuoc[*soLuongThuoc].ten, MAX_TEN, stdin);
    danhSachThuoc[*soLuongThuoc].ten[strcspn(danhSachThuoc[*soLuongThuoc].ten, "\n")] = 0;

    printf("Nhap don vi (vi du: vien, lo): ");
    fgets(danhSachThuoc[*soLuongThuoc].donVi, MAX_DONVI, stdin);
    danhSachThuoc[*soLuongThuoc].donVi[strcspn(danhSachThuoc[*soLuongThuoc].donVi, "\n")] = 0;

    printf("Nhap so luong: ");
    scanf("%d", &danhSachThuoc[*soLuongThuoc].soLuong);

    printf("Nhap gia: ");
    scanf("%lf", &danhSachThuoc[*soLuongThuoc].gia);
    getchar();
    
    printf("Nhap han su dung (vi du: 12/2025): ");
    fgets(danhSachThuoc[*soLuongThuoc].hanSuDung, MAX_HANSUDUNG, stdin);
    danhSachThuoc[*soLuongThuoc].hanSuDung[strcspn(danhSachThuoc[*soLuongThuoc].hanSuDung, "\n")] = 0;


    (*soLuongThuoc)++;
    printf("Da them thuoc thanh cong!\n");
}

//-------------------------- HAM TIM VI TRI THEO ID --------------------------
int timViTriTheoID(Thuoc danhSachThuoc[], int soLuongThuoc, const char* id) {
    for (int i = 0; i < soLuongThuoc; i++) {
        if (strcmp(danhSachThuoc[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

//-------------------------- HAM XOA THUOC THEO ID --------------------------
void xoaThuocTheoID(Thuoc danhSachThuoc[], int* soLuongThuoc) {
    char id[MAX_ID];
    printf("Nhap ma thuoc can xoa: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    int viTri = timViTriTheoID(danhSachThuoc, *soLuongThuoc, id);
    if (viTri == -1) {
        printf("Khong tim thay thuoc co ID \"%s\".\n", id);
        return;
    }

    for (int i = viTri; i < *soLuongThuoc - 1; i++) {
        danhSachThuoc[i] = danhSachThuoc[i + 1];
    }
    (*soLuongThuoc)--;
    printf("Da xoa thuoc thanh cong.\n");
}

//-------------------------- HAM CHINH SUA THUOC --------------------------
void chinhSuaThuocTheoID(Thuoc danhSachThuoc[], int soLuongThuoc) {
    char id[MAX_ID];
    printf("Nhap ma thuoc can chinh sua: ");
    fgets(id, MAX_ID, stdin);
    id[strcspn(id, "\n")] = 0;

    int viTri = timViTriTheoID(danhSachThuoc, soLuongThuoc, id);
    if (viTri == -1) {
        printf("Khong tim thay thuoc co ID \"%s\".\n", id);
        return;
    }

    printf("Nhap ten moi: ");
    fgets(danhSachThuoc[viTri].ten, MAX_TEN, stdin);
    danhSachThuoc[viTri].ten[strcspn(danhSachThuoc[viTri].ten, "\n")] = 0;

    printf("Nhap don vi moi: ");
    fgets(danhSachThuoc[viTri].donVi, MAX_DONVI, stdin);
    danhSachThuoc[viTri].donVi[strcspn(danhSachThuoc[viTri].donVi, "\n")] = 0;

    printf("Nhap so luong moi: ");
    scanf("%d", &danhSachThuoc[viTri].soLuong);
    printf("Nhap gia moi: ");
    scanf("%lf", &danhSachThuoc[viTri].gia);
    getchar();
    
    printf("Nhap han su dung moi: ");
    fgets(danhSachThuoc[viTri].hanSuDung, MAX_HANSUDUNG, stdin);
    danhSachThuoc[viTri].hanSuDung[strcspn(danhSachThuoc[viTri].hanSuDung, "\n")] = 0;

    printf("Da cap nhat thong tin thuoc.\n");
}


//================================================== Nam Anh ==================================================

//-------------------------- ĐỌC/GHI FILE --------------------------
BenhNhan danhSach[MAX];
int soLuong = 0;

#include <fstream>
#include <sstream>

void docDuLieuTuFile() {
    ifstream file("benhnhan_new.txt");
    if (!file) {
        file.open("benhnhan_old.txt");
        if (!file) {
            cout << "Khong tim thay file du lieu.\n";
            return;
        }
    }

    soLuong = 0;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, tuoiStr, luuTruStr;

        getline(ss, idStr, ',');
        getline(ss, danhSach[soLuong].hoTen, ',');
        getline(ss, tuoiStr, ',');
        getline(ss, danhSach[soLuong].diaChi, ',');
        getline(ss, danhSach[soLuong].GioiTinh, ',');
        getline(ss, danhSach[soLuong].maBenhNhan, ',');
        getline(ss, danhSach[soLuong].TienSuBenhAn, ',');
        getline(ss, luuTruStr, '\n');

        danhSach[soLuong].id = stoll(idStr);
        danhSach[soLuong].tuoi = stoi(tuoiStr);
        danhSach[soLuong].luuTru = (luuTruStr == "1");

        soLuong++;
        if (soLuong >= MAX) break;
    }

    file.close();
    cout << "Da nap " << soLuong << " benh nhan tu file.\n";
}



void ghiDuLieuRaFile() {
    ofstream file("benhnhan_new.txt");
    if (!file) {
        cout << "Khong the mo file de ghi.\n";
        return;
    }

    for (int i = 0; i < soLuong; i++) {
        file << danhSach[i].id << ","
             << danhSach[i].hoTen << ","
             << danhSach[i].tuoi << ","
             << danhSach[i].diaChi << ","
             << danhSach[i].GioiTinh << ","
             << danhSach[i].maBenhNhan << ","
             << danhSach[i].TienSuBenhAn << ","
             << danhSach[i].luuTru << "\n";
    }

    file.close();
    cout << "Da luu danh sach vao file benhnhan_new.txt\n";
}

//------------------------------------------------------------------



void timKiemBenhNhan() {
    int chon;
    do {
        printf("\n--- Tim kiem benh nhan ---\n");
        printf("1. Theo ID\n2. Theo ten\n3. Theo phong benh\n0. Quay lai menu chinh\nChon: ");
        scanf("%d", &chon); getchar();

        if (chon == 1) {
            int id;
            printf("Nhap ID: "); scanf("%d", &id);
            for (int i = 0; i < soLuong; i++) {
                if (danhSach[i].id == id) {
                    printf("Tim thay: %s | Tuoi: %d | Dia chi: %s | Gioi Tinh: %s | Ma benh nhan: %s | Tien su benh an: %s | Luu Tru: %d\n",
                        danhSach[i].hoTen.c_str(),
                        danhSach[i].tuoi,
                        danhSach[i].diaChi.c_str(),
                        danhSach[i].GioiTinh.c_str(),
                        danhSach[i].maBenhNhan.c_str(),
                        danhSach[i].TienSuBenhAn.c_str(),
                        danhSach[i].luuTru);
                    break;
                }
                if(i+1 == soLuong) {
                    printf("Khong tim thay!\n");
                    break;
                }
            }
        } else if (chon == 2) {
            string hoTen;
            printf("Nhap ten: "); getline(cin, hoTen);
            if (!hoTen.empty() && hoTen.back() == '\n') {
                hoTen.pop_back(); // Xoá ký tự cuối nếu là '\n'
            }
            for (int i = 0; i < soLuong; i++) {
                if (danhSach[i].hoTen == hoTen) {
                    printf("Tim thay: %s | Tuoi: %d | Dia chi: %s | Gioi Tinh: %s | Ma benh nhan: %s | Tien su benh an: %s | Luu Tru: %d\n",
                        danhSach[i].hoTen.c_str(),
                        danhSach[i].tuoi,
                        danhSach[i].diaChi.c_str(),
                        danhSach[i].GioiTinh.c_str(),
                        danhSach[i].maBenhNhan.c_str(),
                        danhSach[i].TienSuBenhAn.c_str(),
                        danhSach[i].luuTru);
                    break;
                }
                if(i+1 == soLuong) {
                    printf("Khong tim thay!\n");
                    break;
                }
            }
        } 
        // else if (chon == 3) {
        //     char phong[20];
        //     printf("Nhap phong benh: "); fgets(phong, sizeof(phong), stdin);
        //     phong[strcspn(phong, "\n")] = '\0';
        //     for (int i = 0; i < soLuong; i++) {
        //         if (strcmp(danhSach[i].phong, phong) == 0) {
        //             printf("Tim thay: ID %d | Ten: %s | Tuoi: %d | Dia chi: %s | Uu tien: %d\n",
        //                 danhSach[i].id, danhSach[i].hoTen, danhSach[i].tuoi,
        //                 danhSach[i].diaChi, danhSach[i].mucDoUuTien);
        //             break;
        //         }
        //         if(i+1 == soLuong) {
        //             printf("Khong tim thay!\n");
        //             break;
        //         }
        //     }
        // }
    } while (chon != 0);
}

// char layChuCuoiCuaTen(char *hoTen) {
//     int len = strlen(hoTen);
//     while (len > 0 && hoTen[len - 1] == ' ') len--; // Bỏ khoảng trắng cuối
//     return (len > 0) ? hoTen[len - 1] : '\0';
// }

void sapXepTheoTen(int tangDan) {
    for (int i = 0; i < soLuong - 1; i++) {
        for (int j = i + 1; j < soLuong; j++) {
            char cuoi1 = danhSach[i].hoTen.back();
            char cuoi2 = danhSach[j].hoTen.back();;
            if ((tangDan && cuoi1 > cuoi2) || (!tangDan && cuoi1 < cuoi2)) {
                BenhNhan temp = danhSach[i];
                danhSach[i] = danhSach[j];
                danhSach[j] = temp;
            }
        }
    }
}


void sapXepTheoTuoi(int tangDan) {
    for (int i = 0; i < soLuong - 1; i++) {
        for (int j = i + 1; j < soLuong; j++) {
            if ((tangDan && danhSach[i].tuoi > danhSach[j].tuoi) ||
                (!tangDan && danhSach[i].tuoi < danhSach[j].tuoi)) {
                BenhNhan temp = danhSach[i];
                danhSach[i] = danhSach[j];
                danhSach[j] = temp;
            }
        }
    }
}

// void sapXepTheoUuTien(int tangDan) {
//     for (int i = 0; i < soLuong - 1; i++) {
//         for (int j = i + 1; j < soLuong; j++) {
//             if ((tangDan && danhSach[i].mucDoUuTien > danhSach[j].mucDoUuTien) ||
//                 (!tangDan && danhSach[i].mucDoUuTien < danhSach[j].mucDoUuTien)) {
//                 BenhNhan temp = danhSach[i];
//                 danhSach[i] = danhSach[j];
//                 danhSach[j] = temp;
//             }
//         }
//     }
// }

void hienThiDanhSach() {
    printf("\n--- Danh sach benh nhan ---\n");
    for (int i = 0; i < soLuong; i++) {
        printf("ID: %lld | Ma benh nhan: %s | Ho Ten: %s | Tuoi: %d | Dia chi: %s | Gioi Tinh: %s | Tien su benh an: %s | Luu Tru: %d\n",
            danhSach[i].id,
            danhSach[i].maBenhNhan.c_str(),
            danhSach[i].hoTen.c_str(),
            danhSach[i].tuoi,
            danhSach[i].diaChi.c_str(),
            danhSach[i].GioiTinh.c_str(),
            danhSach[i].TienSuBenhAn.c_str(),
            danhSach[i].luuTru
        );
    }
}

void sapXepBenhNhan() {
    int chon, tangDan;
    do {
        printf("\n--- Sap xep danh sach benh nhan ---\n");
        printf("1. Theo ten\n2. Theo tuoi\n3. Theo muc do uu tien\n0. Quay lai\nChon: ");
        scanf("%d", &chon); getchar();

        if (chon >= 1 && chon <= 3) {
            printf("Chon kieu sap xep (1. Tang dan | 0. Giam dan): ");
            scanf("%d", &tangDan); getchar();
        }

        switch (chon) {
            case 1: sapXepTheoTen(tangDan); hienThiDanhSach(); break;
            case 2: sapXepTheoTuoi(tangDan); hienThiDanhSach(); break;
            // case 3: sapXepTheoUuTien(tangDan); hienThiDanhSach(); break;
        }
    } while (chon != 0);
}

huoc danhSachThuoc[MAX_THUOC];
    int soLuongThuoc = 0;
    int luaChon;
    do {
        printf("\n===== QUAN LY THUOC =====\n");
        printf("1. Them thuoc\n");
        printf("2. Xoa thuoc theo ID\n");
        printf("3. Chinh sua thuoc theo ID\n");
        printf("4. Xem danh sach thuoc\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                themThuoc(danhSachThuoc, &soLuongThuoc);
                break;
            case 2:
                xoaThuocTheoID(danhSachThuoc, &soLuongThuoc);
                break;
            case 3:
                chinhSuaThuocTheoID(danhSachThuoc, soLuongThuoc);
                break;
            case 4:
                printf("\n%-10s %-20s %-10s %-10s %-10s %-15s\n", "ID", "Ten", "Don Vi", "So Luong", "Gia", "Han SD");
                for (int i = 0; i < soLuongThuoc; i++) {
                    printf("%-10s %-20s %-10s %-10d %-10.2lf %-15s\n",
                        danhSachThuoc[i].id,
                        danhSachThuoc[i].ten,
                        danhSachThuoc[i].donVi,
                        danhSachThuoc[i].soLuong,
                        danhSachThuoc[i].gia,
                        danhSachThuoc[i].hanSuDung
                    );
                }
                break;
            case 0:
                printf("Thoat chuong trinh quan ly thuoc.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 0);

    return 0;
}
// ========================== HÀM MAIN ==========================

int main() {
    docDuLieuTuFile(); // Đọc dữ liệu khi bắt đầu

    int chon;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Hien thi danh sach benh nhan\n");
        printf("2. Them benh nhan\n");
        printf("3. Sua thong tin benh nhan\n");
        printf("4. Xoa thong tin benh nhan\n");
        printf("5. Tim kiem benh nhan\n");
        printf("6. Sap xep danh sach benh nhan\n");
        printf("0. Thoat chuong trinh\n");
        printf("Chon: ");
        scanf("%d", &chon);
        switch (chon) {
            case 1: hienThiDanhSach(); break;
            // case 2: themBenhNhan(); break;
            // case 3: suaBenhNhan(); break;
            // case 4: xoaBenhNhan(); break;
            case 5: timKiemBenhNhan(); break;
            case 6: sapXepBenhNhan(); break;
            case 0:
                ghiDuLieuRaFile(); // Ghi dữ liệu khi thoát
                printf("Ket thuc chuong trinh.\n");
                break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (chon != 0);

    return 0;
}
