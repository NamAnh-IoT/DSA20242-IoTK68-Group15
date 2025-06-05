#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

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
//Hàm kiểm tra ký tự có phải là số nguyên dương không
bool isPositiveInteger(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        //char c:str là ký tự trong chuỗi str
        if (!isdigit(c)) return false;
        //isdigit(c) chỉ trả về true nếu c là ký tự số từ '0' đến '9'
    }
    if (str.length() > 1 && str[0] == '0') return false;
    return stoll(str) > 0;
    //stoll(str) chuyển đổi chuỗi str thành số nguyên dài long long
}
//Hàm kiểm tra chuỗi có phải là chữ cái và dấu cách không
bool isAlphaSpace(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!(isalpha(c) || c == ' ' || (unsigned char)c >= 128)) return false;
        //isalpha(c) kiểm tra xem c có phải là chữ cái không
    }
    return true;
}
//Hàm kiểm tra chuỗi có phải là chuỗi chữ và số không
bool isAlnumString(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalnum(c)) return false;
        //isalnum(c) kiểm tra xem c có phải là chữ cái hoặc số không
    }
    return true;
}
//Hàm kiểm tra chuỗi có phải là chuỗi chữ và số không (không có dấu cách hoặc ký tự đặc biệt)
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
//Hàm nhập thông tin bệnh nhân
void nhapThongTinBenhNhan(BenhNhan &bn, Node* head, bool kiemTraTrungLap = true, long long idCu = -1) {
    bool trungTen, trungID, trungMa;
    string input;
    do {
        cout << "ID: ";
        cin.ignore();
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
//Hàm xuất thông tin bệnh nhân
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
//Hàm in danh sách bệnh nhân
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
//Hàm thêm bệnh nhân
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
//Filler cho điều kiện xóa bệnh nhân
struct DieuKienXoa {
    long long id = -1;
    string ten = "";
    string gioiTinh = "";
    string tienSu = "";
};
// Hàm nhập điều kiện xóa bệnh nhân
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
//đối chiếu điều kiện xóa bệnh nhân với từng node trong danh sách
bool kiemTraNodeCanXoa(const BenhNhan& bn, int luaChon, const DieuKienXoa& dk) {
    if ((luaChon == 1 || luaChon == 5) && bn.id != dk.id) return false;
    if ((luaChon == 2 || luaChon == 5) && bn.hoTen != dk.ten) return false;
    if ((luaChon == 3 || luaChon == 5) && bn.GioiTinh != dk.gioiTinh) return false;
    if ((luaChon == 4 || luaChon == 5) && bn.TienSuBenhAn != dk.tienSu) return false;
    return true;
}
// Hàm xóa bệnh nhân theo điều kiện
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
//Filler cho điều kiện tìm kiếm bệnh nhân
struct DieuKienTimKiem {
    string ten = "";
    int tuoi = -1;
    string gioiTinh = "";
    string diaChi = "";
};
// Hàm nhập điều kiện tìm kiếm bệnh nhân
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
// Hàm kiểm tra điều kiện tìm kiếm bệnh nhân với từng node trong danh sách
bool kiemTraNodeTimKiem(const BenhNhan& bn, int luaChon, const DieuKienTimKiem& dk) {
    if ((luaChon == 1 || luaChon == 5) && bn.hoTen != dk.ten) return false;
    if ((luaChon == 2 || luaChon == 5) && bn.tuoi != dk.tuoi) return false;
    if ((luaChon == 3 || luaChon == 5) && bn.GioiTinh != dk.gioiTinh) return false;
    if ((luaChon == 4 || luaChon == 5) && bn.diaChi != dk.diaChi) return false;
    return true;
}
// Hàm tìm kiếm bệnh nhân theo điều kiện
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
// Hàm cập nhật thông tin bệnh nhân, điều kiện không trùng thông tin cũ và kiểm tra điều kiện trùng lặp
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
// Hàm cập nhật thông tin bệnh nhân theo ID
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

// Hospital Management System - Optimized with patient and nurse BST + room classification

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100
#define TOTAL_ROOMS 52
#define MAX_NURSES_PER_ROOM 2
#define TYPE_COUNT 5

// ======================= Structs =========================
typedef struct {
    int id;
    char cccd[20];
    char name[100];
    int age;
    char state[200];
    char history[50];
    int priority;
} Patient;

typedef struct PatientNode {
    Patient data;
    struct PatientNode* left;
    struct PatientNode* right;
} PatientNode;

typedef struct {
    char name[100];
    char shift[50];
} Nurse;

typedef struct NurseNode {
    Nurse data;
    struct NurseNode* left;
    struct NurseNode* right;
} NurseNode;

typedef struct {
    PatientNode* patientRoot;
    int patientCount;

    NurseNode* nurseRoot;
    int nurseCount;

    char type[2];
    int tier;
} Room;

// ======================= Globals =========================
int patientIDCounter = 1;
Room* roomsByType[TYPE_COUNT][30];
int roomCountByType[TYPE_COUNT];

// ======================= Utility =========================
int getTypeIndex(const char* type) {
    switch (type[0]) {
    case 'S': return 0;
    case 'A': return 1;
    case 'F': return 2;
    case 'E': return 3;
    case 'O': return 4;
    }
    return -1;
}

int getMaxPatientsPerRoom(const char* type) {
    if (strcmp(type, "S") == 0) return 2;
    if (strcmp(type, "A") == 0) return 6;
    if (strcmp(type, "F") == 0) return 12;
    if (strcmp(type, "E") == 0) return 30;
    if (strcmp(type, "O") == 0) return 1;
    return MAX;
}

int isValidString(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != ' ') return 0;
    }
    return 1;
}

void readLine(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

// ======================= BST Patient Functions =========================
PatientNode* insertPatient(PatientNode* root, Patient p) {
    if (!root) {
        PatientNode* node = (PatientNode*)malloc(sizeof(PatientNode));
        node->data = p;
        node->left = node->right = NULL;
        return node;
    }
    if (p.id < root->data.id)
        root->left = insertPatient(root->left, p);
    else
        root->right = insertPatient(root->right, p);
    return root;
}

PatientNode* findPatient(PatientNode* root, int id) {
    if (!root) return NULL;
    if (id == root->data.id) return root;
    if (id < root->data.id) return findPatient(root->left, id);
    return findPatient(root->right, id);
}

void printPatients(PatientNode* root) {
    if (!root) return;
    printPatients(root->left);
    Patient p = root->data;
    printf("ID: %d - %s - CCCD: %s - Tuoi: %d - Trang thai: %s - Uu tien: %d\n",
        p.id, p.name, p.cccd, p.age, p.state, p.priority);
    printPatients(root->right);
}

int countPatients(PatientNode* root) {
    if (!root) return 0;
    return 1 + countPatients(root->left) + countPatients(root->right);
}

// ======================= BST Nurse Functions =========================
NurseNode* insertNurse(NurseNode* root, Nurse n) {
    if (!root) {
        NurseNode* node = (NurseNode*)malloc(sizeof(NurseNode));
        node->data = n;
        node->left = node->right = NULL;
        return node;
    }
    if (strcmp(n.name, root->data.name) < 0)
        root->left = insertNurse(root->left, n);
    else
        root->right = insertNurse(root->right, n);
    return root;
}

void printNurses(NurseNode* root) {
    if (!root) return;
    printNurses(root->left);
    printf("%s - Ca truc: %s\n", root->data.name, root->data.shift);
    printNurses(root->right);
}

NurseNode* findNurse(NurseNode* root, const char* name) {
    if (!root) return NULL;
    int cmp = strcmp(name, root->data.name);
    if (cmp == 0) return root;
    if (cmp < 0) return findNurse(root->left, name);
    return findNurse(root->right, name);
}

// ======================= Room Management =========================
void initRoom(Room* room, const char* type, int tier) {
    strcpy(room->type, type);
    room->tier = tier;
    room->nurseCount = 0;
    room->patientCount = 0;
    room->patientRoot = NULL;
    room->nurseRoot = NULL;
}

void setupHospital(Room hospital[]) {
    int index = 0;
    for (int i = 0; i < 6; i++) {
        initRoom(&hospital[index], "S", 5000000);
        roomsByType[0][roomCountByType[0]++] = &hospital[index++];
    }
    for (int i = 0; i < 12; i++) {
        initRoom(&hospital[index], "A", 3000000);
        roomsByType[1][roomCountByType[1]++] = &hospital[index++];
    }
    for (int i = 0; i < 30; i++) {
        initRoom(&hospital[index], "F", 1000000);
        roomsByType[2][roomCountByType[2]++] = &hospital[index++];
    }
    for (int i = 0; i < 2; i++) {
        initRoom(&hospital[index], "E", 0);
        roomsByType[3][roomCountByType[3]++] = &hospital[index++];
    }
    for (int i = 0; i < 2; i++) {
        initRoom(&hospital[index], "O", 0);
        roomsByType[4][roomCountByType[4]++] = &hospital[index++];
    }
}

Room* findAvailableRoom(const char* type) {
    int t = getTypeIndex(type);
    if (t == -1) return NULL;
    for (int i = 0; i < roomCountByType[t]; i++) {
        Room* r = roomsByType[t][i];
        if (countPatients(r->patientRoot) < getMaxPatientsPerRoom(type)) return r;
    }
    return NULL;
}


//================================================== Tuấn ==================================================
#define MAX_THUOC 100
#define MAX_TEN 50
#define MAX_DONVI 20
#define MAX_ID 10
#define MAX_HANSUDUNG 20

using namespace std;
// ========================== CAU TRUC THUOC ==========================
typedef struct {
    char id[MAX_ID];
    char ten[MAX_TEN];
    char donVi[MAX_DONVI];
    int soLuong;
    double gia;
    // char hanSuDung[MAX_HANSUDUNG];
    unsigned int ngay, thang, nam; //Hạn sử dụng
} Thuoc;

// ========================== HI?N TH? DANH SÁCH ==========================
void hienThiDanhSach(Thuoc danhSachThuoc[], int soLuongThuoc) {
    if (soLuongThuoc == 0) {
        printf(">> Danh sach thuoc rong.\n");
        return;
    }

    printf("\n%-10s %-20s %-10s %-10s %-10s %-15s\n", "Ma thuoc", "Ten thuoc", "Don vi", "So luong", "Gia", "Han su dung");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < soLuongThuoc; i++) {
        printf("%-10s %-20s %-10s %-10d %-10.2lf %02d/%02d/%04d\n",
               danhSachThuoc[i].id,
               danhSachThuoc[i].ten,
               danhSachThuoc[i].donVi,
               danhSachThuoc[i].soLuong,
               danhSachThuoc[i].gia,
               danhSachThuoc[i].ngay,
               danhSachThuoc[i].thang,
               danhSachThuoc[i].nam);
    }
}


// ========================== HAM THEM THUOC ==========================
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
    
    printf("Nhap han su dung (vi du: dd/mm/yyyy): ");
    
    scanf("%d/%d/%d", &danhSachThuoc[*soLuongThuoc].ngay, &danhSachThuoc[*soLuongThuoc].thang, &danhSachThuoc[*soLuongThuoc].nam);
    (*soLuongThuoc)++;
    printf("Da them thuoc thanh cong!\n");
}

// ========================== HAM TIM VI TRI THEO ID ==========================
int timViTriTheoID(Thuoc danhSachThuoc[], int soLuongThuoc, const char* id) {
    for (int i = 0; i < soLuongThuoc; i++) {
        if (strcmp(danhSachThuoc[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// ========================== HAM XOA THUOC THEO ID ==========================
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

// ========================== HAM CHINH SUA THUOC ==========================
void chinhSuaThuocTheoID(Thuoc danhSachThuoc[], int soLuongThuoc, char ID[MAX_ID]) {
 
    int viTri = timViTriTheoID(danhSachThuoc, soLuongThuoc, ID);
    if (viTri == -1) {
        printf("Khong tim thay thuoc co ID \"%s\".\n", ID);
        return;
    }else{
        printf("ID: %s | Ten: %s | Don vi: %s | So luong: %d | Gia: %.2f| Han Su Dung: %d/%d/%d\n",
                    danhSachThuoc[viTri].id, danhSachThuoc[viTri].ten, danhSachThuoc[viTri].donVi,
                    danhSachThuoc[viTri].soLuong, danhSachThuoc[viTri].gia,danhSachThuoc[viTri].ngay, danhSachThuoc[viTri].thang, danhSachThuoc[viTri].nam);
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
    
    printf("Nhap han su dung moi (dd/mm/yyyy): ");
  
    scanf("%d/%d/%d", &danhSachThuoc[viTri].ngay, &danhSachThuoc[viTri].thang, &danhSachThuoc[viTri].nam);

    printf("Da cap nhat thong tin thuoc.\n");
}


//================================================== Nam Anh ==================================================

void chinhSuaThuocTheoTen(Thuoc danhSachThuoc[], int soLuongThuoc) {
    char tenCanSua[MAX_TEN];
    printf("Nhap ten thuoc can chinh sua: ");
    fgets(tenCanSua, MAX_TEN, stdin);
    tenCanSua[strcspn(tenCanSua, "\n")] = 0;

    int timThay = 0;
    for (int i = 0; i < soLuongThuoc; i++) {
        if (strcmp(danhSachThuoc[i].ten, tenCanSua) == 0) {
           chinhSuaThuocTheoID(danhSachThuoc, soLuongThuoc, danhSachThuoc[i].id);
           timThay = 1;
           break;
        }
    }

    if (!timThay) {
        printf("Khong tim thay thuoc voi ten \"%s\".\n", tenCanSua);
    }
}

void sapXepTheoTen(Thuoc danhSachThuoc[], int soLuongThuoc) {
    for (int i = 0; i < soLuongThuoc - 1; i++) {
        for (int j = i + 1; j < soLuongThuoc; j++) {
            if (strcmp(danhSachThuoc[i].ten, danhSachThuoc[j].ten) > 0) {
                Thuoc temp = danhSachThuoc[i];
                danhSachThuoc[i] = danhSachThuoc[j];
                danhSachThuoc[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach thuoc theo ten.\n");
}

int soSanhHanSuDung(Thuoc a, Thuoc b) {
    if (a.nam != b.nam) return a.nam - b.nam;
    if (a.thang != b.thang) return a.thang - b.thang;
    return a.ngay - b.ngay;
}

void sapXepTheoHanSuDung(Thuoc danhSachThuoc[], int soLuongThuoc) {
    for (int i = 0; i < soLuongThuoc - 1; i++) {
        for (int j = i + 1; j < soLuongThuoc; j++) {
            if (soSanhHanSuDung(danhSachThuoc[i], danhSachThuoc[j]) > 0) {
                Thuoc temp = danhSachThuoc[i];
                danhSachThuoc[i] = danhSachThuoc[j];
                danhSachThuoc[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach thuoc theo han su dung.\n");
}

// Thao tác với file =======================

void docThuocTuFile(Thuoc danhSachThuoc[], int &soLuongThuoc) {
    ifstream file("thuoc_new.txt");
    if (!file) {
        file.open("thuoc_old.txt");
        if (!file) {
            cout << "Khong tim thay file thuoc.\n";
            return;
        }
    }

    soLuongThuoc = 0;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string soLuongStr, giaStr, ngayStr, thangStr, namStr;

        getline(ss, line, ',');
        strncpy(danhSachThuoc[soLuongThuoc].id, line.c_str(), MAX_ID);
        danhSachThuoc[soLuongThuoc].id[MAX_ID - 1] = '\0';

        getline(ss, line, ',');
        strncpy(danhSachThuoc[soLuongThuoc].ten, line.c_str(), MAX_TEN);
        danhSachThuoc[soLuongThuoc].ten[MAX_TEN - 1] = '\0';

        getline(ss, line, ',');
        strncpy(danhSachThuoc[soLuongThuoc].donVi, line.c_str(), MAX_DONVI);
        danhSachThuoc[soLuongThuoc].donVi[MAX_DONVI - 1] = '\0';

        getline(ss, soLuongStr, ',');
        getline(ss, giaStr, ',');
        getline(ss, ngayStr, ',');
        getline(ss, thangStr, ',');
        getline(ss, namStr, '\n');

        danhSachThuoc[soLuongThuoc].soLuong = stoi(soLuongStr);
        danhSachThuoc[soLuongThuoc].gia = stod(giaStr);
        danhSachThuoc[soLuongThuoc].ngay = stoi(ngayStr);
        danhSachThuoc[soLuongThuoc].thang = stoi(thangStr);
        danhSachThuoc[soLuongThuoc].nam = stoi(namStr);

        soLuongThuoc++;
        if (soLuongThuoc >= MAX_THUOC) break;
    }
    file.close();
    cout << "Da nap " << soLuongThuoc << " thuoc tu file.\n";
}

void ghiThuocVaoFile(Thuoc danhSachThuoc[], int soLuongThuoc) {
    ofstream file("thuoc_new.txt");
    if (!file) {
        cout << "Khong mo duoc file de ghi.\n";
        return;
    }

    for (int i = 0; i < soLuongThuoc; i++) {
        file << danhSachThuoc[i].id << ","
             << danhSachThuoc[i].ten << ","
             << danhSachThuoc[i].donVi << ","
             << danhSachThuoc[i].soLuong << ","
             << danhSachThuoc[i].gia << ","
             << danhSachThuoc[i].ngay << ","
             << danhSachThuoc[i].thang << ","
             << danhSachThuoc[i].nam << "\n";
    }

    file.close();
    cout << "Da luu danh sach thuoc vao file.\n";
}


// Hàm phụ đệ quy để ghi từng y tá
void ghiNurseNode(ofstream& file, NurseNode* root) {
    if (!root) return;
    ghiNurseNode(file, root->left);
    file << "NurseName:" << root->data.name << "\n";
    file << "Shift:" << root->data.shift << "\n";
    ghiNurseNode(file, root->right);
}

void docYTaTuFile(Room hospital[]) {
    ifstream file("nurse_data.txt");
    if (!file) {
        cout << "Khong tim thay file nurse_data.txt\n";
        return;
    }

    string line, roomType = "";
    while (getline(file, line)) {
        if (line.rfind("RoomType:", 0) == 0) {
            roomType = line.substr(9); // Lấy phần sau "RoomType:"
        } else if (line.rfind("NurseName:", 0) == 0) {
            Nurse n;
            strcpy(n.name, line.substr(10).c_str());

            if (getline(file, line) && line.rfind("Shift:", 0) == 0) {
                strcpy(n.shift, line.substr(6).c_str());
            } else continue;

            Room* r = findAvailableRoom(roomType.c_str());
            if (r) {
                r->nurseRoot = insertNurse(r->nurseRoot, n);
                r->nurseCount++;
            }
        }
    }

    file.close();
    cout << "Da nap du lieu y ta tu file nurse_data.txt\n";
}


void ghiYTaRaFile(Room hospital[]) {
    ofstream file("nurse_data.txt");
    if (!file) {
        cout << "Khong the mo file nurse_data.txt de ghi.\n";
        return;
    }

    for (int i = 0; i < TOTAL_ROOMS; i++) {
        Room& r = hospital[i];
        if (r.nurseRoot) {
            file << "RoomType:" << r.type << "\n";
            ghiNurseNode(file, r.nurseRoot);  // Ghi y tá của phòng đó
        }
    }

    file.close();
    cout << "Da luu du lieu y ta vao file nurse_data.txt\n";
}



void docDuLieuTuFile(Node*& head, Node*& tail) {
    ifstream file("benhnhan_new.txt");
    if (!file) {
        file.open("benhnhan_old.txt");
        if (!file) {
            cout << "Không tìm thấy file dữ liệu.\n";
            return;
        }
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, tuoiStr, luuTruStr;
        BenhNhan bn;

        getline(ss, idStr, ',');
        getline(ss, bn.hoTen, ',');
        getline(ss, tuoiStr, ',');
        getline(ss, bn.diaChi, ',');
        getline(ss, bn.GioiTinh, ',');
        getline(ss, bn.maBenhNhan, ',');
        getline(ss, bn.TienSuBenhAn, ',');
        getline(ss, luuTruStr, '\n');

        bn.id = stoll(idStr);
        bn.tuoi = stoi(tuoiStr);
        bn.luuTru = (luuTruStr == "1");

        addLast(head, tail, bn);
    }

    file.close();
    cout << "Đã nạp dữ liệu bệnh nhân vào hàng đợi từ file.\n";
}


void ghiDuLieuRaFile(Node* head) {
    ofstream file("benhnhan_new.txt");
    if (!file) {
        cout << "Không thể mở file để ghi.\n";
        return;
    }

    Node* current = head;
    while (current) {
        const BenhNhan& bn = current->data;
        file << bn.id << ","
             << bn.hoTen << ","
             << bn.tuoi << ","
             << bn.diaChi << ","
             << bn.GioiTinh << ","
             << bn.maBenhNhan << ","
             << bn.TienSuBenhAn << ","
             << (bn.luuTru ? "1" : "0") << "\n";
        current = current->next;
    }

    file.close();
    cout << "Đã lưu danh sách bệnh nhân từ hàng đợi vào file benhnhan_new.txt\n";
}


// ========================== CODE VAT TU Y TE ==========================

#define MAX_VATTU 100
#define MAX_LOAI 50
#define MAX_DONVI 20
#define MAX_TINHTRANG 50
#define MAX_PHONG 50
#define MAX_GHICHU 200


typedef enum {
    MOI,
    TOT,
    BAO_TRI,
    HONG
} TinhTrang;

const char* tinhTrangToString(TinhTrang t) {
    switch(t) {
        case MOI: return "Moi";
        case TOT: return "Tot";
        case BAO_TRI: return "Bao tri";
        case HONG: return "Hong";
        default: return "Khong ro";
    }
}


// ========================== STRUCT VATTU ==========================
typedef struct VatTuYTe {
    char id[MAX_ID];              // Mã vật tư
    char ten[MAX_TEN];            // Tên vật tư
    char loai[MAX_LOAI];          // Loại vật tư
    char donVi[MAX_DONVI];        // Đơn vị tính
    int soLuong;                  // Số lượng tồn kho
    double gia;                   // Giá mỗi đơn vị
    unsigned int ngayNhap, thangNhap, namNhap;
    unsigned int ngayHetHan, thangHetHan, namHetHan;
    TinhTrang tinhTrang; // Tình trạng (dùng enum)
    char phongSuDung[MAX_PHONG];   // Phòng ban sử dụng
    char ghiChu[MAX_GHICHU];       // Ghi chú khác
    struct VatTuYTe* next;         // Con trỏ tới phần tử tiếp theo
} VatTuYTe;

VatTuYTe* danhSachVT = NULL; // Danh sách liên kết đơn
int soLuongVT = 0;

// ========================== HAM THEM ==========================
void themVatTu() {
    VatTuYTe* vt = (VatTuYTe*)malloc(sizeof(VatTuYTe));
    if (!vt) {
        printf("Khong du bo nho!\n");
        return;
    }
    vt->next = NULL;
    printf("Ma vat tu: "); fgets(vt->id, MAX_ID, stdin); vt->id[strcspn(vt->id, "\n")] = 0;
    printf("Ten vat tu: "); fgets(vt->ten, MAX_TEN, stdin); vt->ten[strcspn(vt->ten, "\n")] = 0;
    printf("Loai: "); fgets(vt->loai, MAX_LOAI, stdin); vt->loai[strcspn(vt->loai, "\n")] = 0;
    printf("Don vi: "); fgets(vt->donVi, MAX_DONVI, stdin); vt->donVi[strcspn(vt->donVi, "\n")] = 0;
    printf("So luong: "); scanf("%d", &vt->soLuong);
    printf("Gia: "); scanf("%lf", &vt->gia); getchar();
    printf("Ngay nhap (dd/mm/yyyy): "); scanf("%u/%u/%u", &vt->ngayNhap, &vt->thangNhap, &vt->namNhap);
    printf("Han su dung (dd/mm/yyyy): "); scanf("%u/%u/%u", &vt->ngayHetHan, &vt->thangHetHan, &vt->namHetHan); getchar();
    int luaChon;
    printf("Tinh trang (0: Moi, 1: Tot, 2: Can bao tri, 3: Hong): ");
    scanf("%d", &luaChon); getchar();
    if (luaChon >= 0 && luaChon <= 3) {
        vt->tinhTrang = (TinhTrang)luaChon;
    } else {
        vt->tinhTrang = MOI; // mặc định
    }
    printf("Phong su dung: "); fgets(vt->phongSuDung, MAX_PHONG, stdin); vt->phongSuDung[strcspn(vt->phongSuDung, "\n")] = 0;
    printf("Ghi chu: "); fgets(vt->ghiChu, MAX_GHICHU, stdin); vt->ghiChu[strcspn(vt->ghiChu, "\n")] = 0;
    // Thêm vào đầu danh sách
    vt->next = danhSachVT;
    danhSachVT = vt;
    soLuongVT++;
    printf("Da them vat tu thanh cong!\n");
}

// ========================== HAM HIEN THI ==========================
void hienThiDanhSachVatTu() {
    if (soLuongVT == 0 || danhSachVT == NULL) {
        printf("Danh sach vat tu trong!\n");
        return;
    }
    printf("\n%-10s %-20s %-10s %-10s %-8s %-10s %-12s %-12s %-12s %-12s %-15s\n",
           "ID", "Ten", "Loai", "Don Vi", "SL", "Gia", "Nhap", "Het Han", "Tinh Trang", "Phong", "Ghi Chu");
    VatTuYTe* p = danhSachVT;
    while (p) {
        printf("%-10s %-20s %-10s %-10s %-8d %-10.2f %02u/%02u/%04u   %02u/%02u/%04u   %-12s %-12s %-15s\n",
               p->id, p->ten, p->loai, p->donVi,
               p->soLuong, p->gia,
               p->ngayNhap, p->thangNhap, p->namNhap,
               p->ngayHetHan, p->thangHetHan, p->namHetHan,
               tinhTrangToString(p->tinhTrang), p->phongSuDung, p->ghiChu);
        p = p->next;
    }
}

// ========================== HAM XOA ==========================
void xoaVatTuTheoID(const char* id) {
    VatTuYTe *p = danhSachVT, *prev = NULL;
    while (p) {
        if (strcmp(p->id, id) == 0) {
            if (prev) prev->next = p->next;
            else danhSachVT = p->next;
            free(p);
            soLuongVT--;
            printf("Da xoa vat tu.\n");
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("Khong tim thay vat tu voi ID do.\n");
}

// ========================== HAM CAP NHAT ==========================
void capNhatVatTuTheoID(const char* id) {
    VatTuYTe* p = danhSachVT;
    while (p) {
        if (strcmp(p->id, id) == 0) {
            printf("%-10s %-20s %-10s %-10s %-8d %-10.2f %02u/%02u/%04u   %02u/%02u/%04u   %-12s %-12s %-15s\n",
               p->id, p->ten, p->loai, p->donVi,
               p->soLuong, p->gia,
               p->ngayNhap, p->thangNhap, p->namNhap,
               p->ngayHetHan, p->thangHetHan, p->namHetHan,
               tinhTrangToString(p->tinhTrang), p->phongSuDung, p->ghiChu);
            printf("Cap nhat ten moi: "); fgets(p->ten, MAX_TEN, stdin); p->ten[strcspn(p->ten, "\n")] = 0;
            // cap nhat cac truong khac neu can...
            return;
        }
        p = p->next;
    }
    printf("Khong tim thay vat tu.\n");
}

// ========================== TIM KIEM ==========================
void timTheoTen(const char* ten) {
    VatTuYTe* p = danhSachVT;
    int found = 0;
    while (p) {
        if (strcmp(p->ten, ten) == 0) {
            printf("Tim thay vat tu: %s\n", p->id);
            found = 1;
        }
        p = p->next;
    }
    if (!found) printf("Khong tim thay vat tu voi ten do.\n");
}

void timTheoID(const char* id) {
    VatTuYTe* p = danhSachVT;
    while (p) {
        if (strcmp(p->id, id) == 0) {
            printf("Tim thay: %s - %s\n", p->id, p->ten);
            return;
        }
        p = p->next;
    }
    printf("Khong tim thay ID.\n");
}

// ========================== SAP XEP ==========================

void swapVatTu(VatTuYTe* a, VatTuYTe* b) {
    VatTuYTe tmp = *a;
    *a = *b;
    *b = tmp;
    // Giữ nguyên con trỏ next
    VatTuYTe* t = a->next;
    a->next = b->next;
    b->next = t;
}

int doiThanhNgay(VatTuYTe* a) {
    return a->ngayHetHan + a->thangHetHan*31 + (a->namHetHan-2025) * 365;
}

void sapXepTheoHanDung(int chieu) {
    if (!danhSachVT) return;
    for (VatTuYTe* i = danhSachVT; i != NULL; i = i->next) {
        for (VatTuYTe* j = i->next; j != NULL; j = j->next) {
            if (doiThanhNgay(i)*chieu > doiThanhNgay(j)*chieu) {
                swapVatTu(i, j);
            }
        }
    }
    printf("Da sap xep theo han su dung.\n");
}

// ========================== QUICK SORT CHO LINKED LIST (GIÁ) ==========================
VatTuYTe* partitionGia(VatTuYTe* head, VatTuYTe* end, VatTuYTe** newHead, VatTuYTe** newEnd, int chieu) {
    VatTuYTe* pivot = end;
    VatTuYTe* prev = NULL, *cur = head, *tail = pivot;
    *newHead = NULL;
    while (cur != pivot) {
        if ((cur->gia * chieu) < (pivot->gia * chieu)) {
            if (!*newHead) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            VatTuYTe* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if (!*newHead) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

VatTuYTe* quickSortGiaRecur(VatTuYTe* head, VatTuYTe* end, int chieu) {
    if (!head || head == end) return head;
    VatTuYTe *newHead = NULL, *newEnd = NULL;
    VatTuYTe* pivot = partitionGia(head, end, &newHead, &newEnd, chieu);
    if (newHead != pivot) {
        VatTuYTe* tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortGiaRecur(newHead, tmp, chieu);
        tmp = newHead;
        while (tmp->next) tmp = tmp->next;
        tmp->next = pivot;
    }
    pivot->next = quickSortGiaRecur(pivot->next, newEnd, chieu);
    return newHead;
}

void sapXepTheoGia(int chieu) {
    if (!danhSachVT) return;
    VatTuYTe* end = danhSachVT;
    while (end->next) end = end->next;
    danhSachVT = quickSortGiaRecur(danhSachVT, end, chieu);
    printf("Da sap xep theo Gia (QuickSort).\n");
}

void sapXepTheoTinhTrang(int chieu) {
    if (!danhSachVT) return;
    for (VatTuYTe* i = danhSachVT; i != NULL; i = i->next) {
        for (VatTuYTe* j = i->next; j != NULL; j = j->next) {
            if (i->tinhTrang*chieu > j->tinhTrang*chieu) {
                swapVatTu(i, j);
            }
        }
    }
    printf("Da sap xep theo Tinh Trang.\n");
}

// ========================== MERGE SORT CHO LINKED LIST (SỐ LƯỢNG) ==========================
static VatTuYTe* mergeSoLuong(VatTuYTe* a, VatTuYTe* b, int chieu) {
    if (!a) return b;
    if (!b) return a;
    if ((a->soLuong * chieu) <= (b->soLuong * chieu)) {
        a->next = mergeSoLuong(a->next, b, chieu);
        return a;
    } else {
        b->next = mergeSoLuong(a, b->next, chieu);
        return b;
    }
}

static void splitList(VatTuYTe* source, VatTuYTe** front, VatTuYTe** back) {
    VatTuYTe* slow = source;
    VatTuYTe* fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

static void mergeSortSoLuong(VatTuYTe** headRef, int chieu) {
    VatTuYTe* head = *headRef;
    if (!head || !head->next) return;
    VatTuYTe *a, *b;
    splitList(head, &a, &b);
    mergeSortSoLuong(&a, chieu);
    mergeSortSoLuong(&b, chieu);
    *headRef = mergeSoLuong(a, b, chieu);
}

void sapXepTheoSoLuong(int chieu) {
    if (!danhSachVT) return;
    mergeSortSoLuong(&danhSachVT, chieu);
    printf("Da sap xep theo So Luong (MergeSort).\n");
}

// ========================== DOC / GHI FILE ==========================
void ghiFile() {
    FILE* f = fopen("vattu.txt", "w");
    if (!f) { printf("Loi ghi file.\n"); return; }
    VatTuYTe* p = danhSachVT;
    while (p) {
        fprintf(f, "%s,%s,%s,%s,%d,%.2f,%u,%u,%u,%u,%u,%u,%d,%s,%s\n",
                p->id, p->ten, p->loai, p->donVi,
                p->soLuong, p->gia,
                p->ngayNhap, p->thangNhap, p->namNhap,
                p->ngayHetHan, p->thangHetHan, p->namHetHan,
                p->tinhTrang, p->phongSuDung, p->ghiChu);
        p = p->next;
    }
    fclose(f);
    printf("Da ghi file vattu.txt\n");
}

void docFile() {
    FILE* f = fopen("vattu.txt", "r");
    if (!f) { printf("Khong tim thay file.\n"); return; }
    // Giải phóng danh sách cũ
    while (danhSachVT) {
        VatTuYTe* tmp = danhSachVT;
        danhSachVT = danhSachVT->next;
        free(tmp);
    }
    soLuongVT = 0;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        VatTuYTe* vt = (VatTuYTe*)malloc(sizeof(VatTuYTe));
        if (!vt) break;
        vt->next = NULL;
        // Đọc hết phần còn lại của dòng cho ghi chú (ghiChu)
        int result = sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%lf,%u,%u,%u,%u,%u,%u,%d,%[^,],%[^\n]",
            vt->id, vt->ten, vt->loai, vt->donVi, &vt->soLuong, &vt->gia,
            &vt->ngayNhap, &vt->thangNhap, &vt->namNhap,
            &vt->ngayHetHan, &vt->thangHetHan, &vt->namHetHan,
            (int*)&vt->tinhTrang, vt->phongSuDung, vt->ghiChu);
        if (result == 15) {
            vt->next = danhSachVT;
            danhSachVT = vt;
            soLuongVT++;
        } else {
            free(vt);
        }
    }
    fclose(f);
    printf("Da doc %d vat tu tu file.\n", soLuongVT);
}

void menuSapXep() {
    int choice;
    do {
        printf("\n===== MENU QUAN LY SAP XEP =====\n");
        printf("1. Theo HSD (tang dan)\n");
        printf("2. Theo HSD (giam dan)\n");
        printf("3. Theo Gia (tang dan)\n");
        printf("4. Theo Gia (giam dan)\n");
        printf("5. Theo So Luong (tang dan)\n");
        printf("6. Theo So Luong (giam dan)\n");
        printf("7. Theo Tinh Trang (Tot -> Hong)\n");
        printf("8. Theo Tinh Trang (Hong -> Tot)\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice); getchar();
        printf("\n---------------------\n");


        switch (choice) {
            case 1:
                sapXepTheoHanDung(1); break;
            case 2:
                sapXepTheoHanDung(-1); break;
            case 3:
                sapXepTheoGia(1); break;
            case 4:
                sapXepTheoGia(-1); break;
            case 5:
                sapXepTheoSoLuong(1); break;
            case 6:
                sapXepTheoSoLuong(-1); break;
            case 7:
                sapXepTheoTinhTrang(1); break;
            case 8:
                sapXepTheoTinhTrang(-1); break;
            case 0:
                printf("Quay lai menu chinh.\n"); break;
            default:
                printf("Lua chon khong hop le!\n"); 
        }
        hienThiDanhSachVatTu();
    } while (choice != 0);
}

// ========================== MENU ==========================
void menuVatTuYTe() {
    docFile();
    int choice;
    char buffer[100];
    do {
        printf("\n===== MENU QUAN LY VAT TU Y TE =====\n");
        printf("1. Hien thi vat tu y te\n");
        printf("2. Them vat tu\n");
        printf("3. Xoa vat tu theo ID\n");
        printf("4. Cap nhat vat tu theo ID\n");
        printf("5. Tim theo ten\n");
        printf("6. Tim theo ID\n");
        printf("7. Sap xep\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice); getchar();
        printf("\n---------------------\n");

        switch (choice) {
            case 1:
                hienThiDanhSachVatTu(); break;
            case 2:
                themVatTu(); break;
            case 3:
                printf("Nhap ID can xoa: "); fgets(buffer, 100, stdin); buffer[strcspn(buffer, "\n")] = 0;
                xoaVatTuTheoID(buffer); break;
            case 4:
                printf("Nhap ID can cap nhat: "); fgets(buffer, 100, stdin); buffer[strcspn(buffer, "\n")] = 0;
                capNhatVatTuTheoID(buffer); break;
            case 5:
                printf("Nhap ten can tim: "); fgets(buffer, 100, stdin); buffer[strcspn(buffer, "\n")] = 0;
                timTheoTen(buffer); break;
            case 6:
                printf("Nhap ID can tim: "); fgets(buffer, 100, stdin); buffer[strcspn(buffer, "\n")] = 0;
                timTheoID(buffer); break;
            case 7:
                menuSapXep();
            case 0:
                printf("Ket thuc chuong trinh.\n"); break;
            default:
                printf("Lua chon khong hop le!\n"); 
        }
    } while (choice != 0);
    ghiFile();
}


//------------------------------------------------------------------


void runPatientManagement(){
    Node* head = nullptr;
    Node* tail = nullptr;
    docDuLieuTuFile(head, tail);

    int choice;
    do {

     printf("\n===== MENU QUẢN LÍ BỆNH NHÂN =====\n");
        printf("1. Thêm bệnh nhân vào đầu danh sách\n");
        printf("2. Thêm bệnh nhân vào cuối danh sách\n");
        printf("3. Thêm bệnh nhân vào vị trí bất kỳ\n");
        printf("4. Xóa bệnh nhân\n");
        printf("5. Tìm kiếm bệnh nhân\n");
        printf("6. Cập nhật thông tin bệnh nhân\n");
        printf("7. Hiển thị thông tin bệnh nhân\n");
        printf("0. Thoát\n");
        printf("Hãy đưa ra lựa chọn: ");
        scanf("%d", &choice);
         switch (choice) {
            case 1: {
                BenhNhan bn;
                nhapThongTinBenhNhan(bn, head, true);
                addFirst(head, tail, bn);
                 printf("Đã thêm vào danh sách !.\n");   
                break;
            }
            case 2: {
                BenhNhan bn;
                nhapThongTinBenhNhan(bn, head, true);
                addLast(head, tail, bn);
                 printf("Đã thêm vào danh sách !.\n");   
                break;
            }
            case 3: {
                int position;
                 printf("Nhập vị trí cần thêm (bắt đầu từ 0): ");
                scanf("%d", &position);
                addPatientAtPosition(head, tail, position);
                break;
            }
            case 4:
                removePatient(head, tail);
                break;
            case 5:
                searchPatient(head);
                break;
            case 6:
                UpdatePatient(head);
                break;
            case 7:
                inDanhSach(head);
                break;
            case 0:
                 printf("Thoát chương trình quản lí bệnh nhân.\n");
                break;
            default:
                 printf("Lựa chọn không hợp lệ !\n");
        }
} while (choice != 0);

ghiDuLieuRaFile(head);

}

void runHospitalMenu(Room hospital[]) {
    setupHospital(hospital);
    docYTaTuFile(hospital);      // <-- Nạp y tá
    int choice;
    char buffer[10];
    do {
        printf("\n========= MENU =========\n");
        printf("1. Them benh nhan\n");
        printf("2. Xem danh sach benh nhan\n");
        printf("3. Them y ta\n");
        printf("4. Xem danh sach y ta\n");
        printf("0. Thoat\n");
        printf("Chon: ");

        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
           
            // char type[2];
            // printf("Loai phong (S/A/F/E/O): ");
            // readLine(type, sizeof(type));
            // Room* r = findAvailableRoom(type);
            // if (!r) { printf("Khong co phong trong.\n"); continue; }
            // Patient p;
            // p.id = patientIDCounter++;
            // printf("Ten: "); readLine(p.name, sizeof(p.name)); getchar();cin.ignore();
            // printf("CCCD: "); readLine(p.cccd, sizeof(p.cccd)); getchar();cin.ignore();
            // printf("Tuoi: "); scanf("%d", &p.age);cin.ignore();
            // printf("Trang thai: "); readLine(p.state, sizeof(p.state)); getchar();cin.ignore();
            // printf("Lich su: "); readLine(p.history, sizeof(p.history)); getchar();cin.ignore();
            // printf("Uu tien: "); scanf("%d", &p.priority);cin.ignore();

            // r->patientRoot = insertPatient(r->patientRoot, p);
            // r->patientCount++;
            // printf("Da them benh nhan ID %d\n", p.id);

            if (choice == 1) {
    char type[2];
    printf("Loai phong (S/A/F/E/O): ");
    readLine(type, sizeof(type));
    Room* r = findAvailableRoom(type);
    if (!r) { printf("Khong co phong trong.\n"); continue; }
    Patient p;
    p.id = patientIDCounter++;
    cin.ignore();   
    printf("Ten: "); readLine(p.name, sizeof(p.name));
    printf("CCCD: "); readLine(p.cccd, sizeof(p.cccd));
    printf("Tuoi: "); char buf[16]; readLine(buf, sizeof(buf)); p.age = atoi(buf);
    printf("Trang thai: "); readLine(p.state, sizeof(p.state));
    printf("Lich su: "); readLine(p.history, sizeof(p.history));
    printf("Uu tien: "); readLine(buf, sizeof(buf)); p.priority = atoi(buf);
    r->patientRoot = insertPatient(r->patientRoot, p);
    r->patientCount++;
    printf("Da them benh nhan ID %d\n", p.id);
}
        }
        else if (choice == 2) {
            for (int i = 0; i < TOTAL_ROOMS; i++) {
                if (hospital[i].patientRoot) {
                    printf("\n-- Phong %s-tier --\n", hospital[i].type);
                    printPatients(hospital[i].patientRoot);
                }
            }
        }
        else if (choice == 3) {
            char type[2];
            printf("Loai phong de them y ta (S/A/F/E/O): ");
            readLine(type, sizeof(type));
            Room* r = findAvailableRoom(type);
            if (!r) { printf("Khong tim thay phong loai nay.\n"); continue; }
            Nurse n;
            printf("Ten y ta: "); readLine(n.name, sizeof(n.name));
            printf("Ca truc: "); readLine(n.shift, sizeof(n.shift));
            r->nurseRoot = insertNurse(r->nurseRoot, n);
            r->nurseCount++;
            printf("Da them y ta %s\n", n.name);
        }
        else if (choice == 4) {
            bool coYTa = false;
            for (int i = 0; i < TOTAL_ROOMS; i++) {
                if (hospital[i].nurseRoot) {
                    coYTa = true;
                    printf("\n-- Y ta o phong %s-tier --\n", hospital[i].type);
                    printNurses(hospital[i].nurseRoot);
                }
            }
            if (!coYTa) {
                printf("Khong co y ta nao!\n");
            }
        }
    } while (choice != 0);
    ghiYTaRaFile(hospital); 
}

// ========================== CAP NHAT MENU ==========================
void menuThuoc() {
    printf("\n===== MENU =====\n");
    printf("1. Hien thi danh sach thuoc\n");
    printf("2. Them thuoc moi\n");
    printf("3. Tim thuoc theo ten\n");
    printf("4. Xoa thuoc theo ma\n");
    printf("5. Chinh sua thong tin thuoc\n");
    printf("6. Chinh sua thuoc theo ten\n");
    printf("7. Sap xep thuoc theo ten\n");
    printf("8. Sap xep thuoc theo han su dung\n");

    printf("0. Thoat\n");
    printf("===============\n");
    printf("Chon: ");
}

// void runQuanLyThuoc() {
//     Thuoc danhSachThuoc[MAX_THUOC];
//     int soLuongThuoc = 0;
//     int choice;
//     do {
//         printf("\n===== QUAN LY THUOC =====\n");
//         printf("1. Them thuoc\n");
//         printf("2. Xoa thuoc theo ID\n");
//         printf("3. Chinh sua thuoc theo ID\n");
//         printf("4. Xem danh sach thuoc\n");
//         printf("0. Thoat\n");
//         printf("Chon chuc nang: ");
//         scanf("%d", &choice);
//         getchar();

//         switch (choice) {
//             case 1:
//                 themThuoc(danhSachThuoc, &soLuongThuoc);
//                 break;
//             case 2:
//                 xoaThuocTheoID(danhSachThuoc, &soLuongThuoc);
//                 break;
//             case 3:
//                 chinhSuaThuocTheoID(danhSachThuoc, soLuongThuoc);
//                 break;
//             case 4:
//                 printf("\n%-10s %-20s %-10s %-10s %-10s %-15s\n", "ID", "Ten", "Don Vi", "So Luong", "Gia", "Han SD");
//                 for (int i = 0; i < soLuongThuoc; i++) {
//                     printf("%-10s %-20s %-10s %-10d %-10.2lf %-15s\n",
//                         danhSachThuoc[i].id,
//                         danhSachThuoc[i].ten,
//                         danhSachThuoc[i].donVi,
//                         danhSachThuoc[i].soLuong,
//                         danhSachThuoc[i].gia,
//                         danhSachThuoc[i].hanSuDung
//                     );
//                 }
//                 break;
//             case 0:
//                 printf("Thoat chuong trinh quan ly thuoc.\n");
//                 break;
//             default:
//                 printf("Lua chon khong hop le!\n");
//         }
//     } while (choice != 0);
// }

void runQuanLyThuoc() {
    Thuoc danhSachThuoc[MAX_THUOC];
    int soLuongThuoc = 0;

    docThuocTuFile(danhSachThuoc, soLuongThuoc);

    int luaChon;
    do {
        menuThuoc();
        scanf("%d", &luaChon);
        getchar();

        switch (luaChon) {
            case 1:
                for (int i = 0; i < soLuongThuoc; i++) {
                    printf("ID: %s | Ten: %s | Don vi: %s | So luong: %d | Gia: %.2f| Han Su Dung: %d/%d/%d\n",
                               danhSachThuoc[i].id, danhSachThuoc[i].ten, danhSachThuoc[i].donVi,
                               danhSachThuoc[i].soLuong, danhSachThuoc[i].gia,danhSachThuoc[i].ngay, danhSachThuoc[i].thang, danhSachThuoc[i].nam);
                    }
                break;
            case 2:
                themThuoc(danhSachThuoc, &soLuongThuoc);
                break;
            case 3: {
                char tenCanTim[MAX_TEN];
                printf("Nhap ten thuoc can tim: ");
                fgets(tenCanTim, MAX_TEN, stdin);
                tenCanTim[strcspn(tenCanTim, "\n")] = 0;
                int timThay = 0;
                for (int i = 0; i < soLuongThuoc; i++) {
                    if (strcmp(danhSachThuoc[i].ten, tenCanTim) == 0) {
                        printf("ID: %s | Ten: %s | Don vi: %s | So luong: %d | Gia: %.2f| Han Su Dung: %d/%d/%d\n",
                               danhSachThuoc[i].id, danhSachThuoc[i].ten, danhSachThuoc[i].donVi,
                               danhSachThuoc[i].soLuong, danhSachThuoc[i].gia,danhSachThuoc[i].ngay, danhSachThuoc[i].thang, danhSachThuoc[i].nam);
                        timThay = 1;
                    }
                }
                if (!timThay) printf("Khong tim thay thuoc.\n");
                break;
            }
            case 4:
                xoaThuocTheoID(danhSachThuoc, &soLuongThuoc);
                break;
            case 5:
                char id[MAX_ID];
                printf("Nhap ma thuoc can chinh sua: ");
                fgets(id, MAX_ID, stdin);
                id[strcspn(id, "\n")] = 0;
                chinhSuaThuocTheoID(danhSachThuoc, soLuongThuoc, id);
                break;
            case 6:
                chinhSuaThuocTheoTen(danhSachThuoc, soLuongThuoc);
                break;
            case 7:
                sapXepTheoTen(danhSachThuoc, soLuongThuoc);
                break;
            case 8:
                sapXepTheoHanSuDung(danhSachThuoc, soLuongThuoc);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);

    ghiThuocVaoFile(danhSachThuoc, soLuongThuoc);

}

// ========================== HÀM MAIN ==========================

int main() {
    // docDuLieuTuFile(); // Đọc dữ liệu khi bắt đầu


    Room hospital[TOTAL_ROOMS];
     int mainChoice;
    do {
        printf("\n===== MENU CHUONG TRINH CHINH =====\n");
        printf("1. Quan ly benh nhan\n");
        printf("2. Quan ly bac si\n");
        printf("3. Quan ly thuoc\n");
        printf("4. Quan ly vat tu y te\n");
        printf("0. Thoat chuong trinh\n");
        printf("Hay Dua Ra Lua Chon: ");
        scanf("%d", &mainChoice);
        getchar(); // Đọc ký tự newline còn lại trong bộ đệm
        switch (mainChoice) {
            case 1: 
                runPatientManagement(); 
                break;
            case 2: 
                runHospitalMenu(hospital);
                break;
            case 3:     
                runQuanLyThuoc(); 
                break;
            case 4:
                menuVatTuYTe(); // Quản lý vật tư y tế
                break;
            case 0:
                // ghiDuLieuRaFile(); // Ghi dữ liệu khi thoát
                printf("Ket thuc chuong trinh.\n");
                break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (mainChoice != 0);

    return 0;
}
