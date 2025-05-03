#include <stdio.h>
using namespace std;

struct PhuongThucKham {
    string tenPhuongThuc;
    string moTa;
};

struct Thuoc {
    string tenThuoc;
    int soLuong;
};

struct DungCuYTe {
    string tenDungCu;
    int soLuong;
};

struct PhongKham {
    string ngayNhapVien;
    string tenPhong;
    vector<Thuoc> danhSachThuoc;
    vector<DungCuYTe> danhSachDungCu;
};

struct NhanSu {
    string hoTen;
    string chucVu;
};

struct BenhAn{
    string maBenhAn;
    string chuanDoan;
    string luuYQuanTrong;
    
    BenhAn* next;
};

struct BenhNhan{
    string hoTen;
    int tuoi;
    string diaChi;
    string maBenhNhan;
    BenhAn* danhSachBenhAn;
    BenhAn* next;
};




/*BenhNhan* addPatient(BenhNhan* head, string hoTen, int tuoi, string diaChi, string maBenhNhan) {
    BenhNhan* newBn = new BenhNhan{hoTen, tuoi, diaChi, maBenhNhan, nullptr};
    if (!head) {
        return newBn;
    } else { 
        BenhNhan* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newBn;
        return head; 
    }
}

void display(BenhNhan *head){
BenhNhan *temp = head;
while(head){
cout<<"Bệnh nhân: "<<temp->hoTen<<", Tuổi: "<<temp->tuoi<<", Địa chỉ: "<<temp->diaChi<< " Mã Bệnh Nhân"<<temp->maBenhNhan << endl;
temp=temp->next;
}
}*/ //-TEMPORARY OFFLINE










int main() {
    
}
