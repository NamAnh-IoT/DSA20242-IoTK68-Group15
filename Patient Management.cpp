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
        // Nếu nhưu danh sách mới
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
       // Nếu nhưu danh sách mới
        head = node;
    }
    tail = node;
}
void addPatientAtPosition(Node*& head, Node*& tail, int position) {
    BenhNhan bn;
    cout << "Nhap thong tin benh nhan moi:\n";
    cout << "ID: "; cin >> bn.id;
    cin.ignore();
    cout << "Ho ten: "; getline(cin, bn.hoTen);
    cout << "Tuoi: "; cin >> bn.tuoi;
    cin.ignore();
    cout << "Dia chi: "; getline(cin, bn.diaChi);
    cout << "Gioi tinh: "; getline(cin, bn.GioiTinh);
    cout << "Ma benh nhan: "; getline(cin, bn.maBenhNhan);
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
        temp = temp->next;
        idx++;
    }


    if (temp->next == nullptr) {
        temp->next = node;
        node->prev = temp;
        tail = node;
    }

    else {
        node->next = temp->next;
        node->prev = temp;
        temp->next->prev = node;
        temp->next = node;
    }
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

//Bị SegmentFault thì gỡ hàm dưới

/*Node* node = new (std::nothrow) Node;
if (!node) {
    cerr << "Lỗi cấp phát bộ nhớ!" << endl;
    return;
}*/

