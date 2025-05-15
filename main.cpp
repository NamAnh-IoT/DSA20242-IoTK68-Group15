#include <stdio.h>
using namespace std;

struct BenhNhan{
    string hoTen;
    int tuoi;
    string diaChi;
    string GioiTinh;
    string maBenhNhan;
    string TienSuBenhAn;

};
struct PhuongThucKham {
    string tenPhuongThuc;
    string moTa;
};

struct Kham2 {
    float heartRate;
    float pWave;
    float qrsComplex;
    float tWave;
};

struct Kham1 {
    string testType;
    int score;
    string interpretation;
};

struct Thuoc {
    string tenThuoc;
    int soLuong;
    string hanDung;
};

struct DungCuYTe {
    string tenDungCu;
    int soLuong;
};

struct PhongKham {
    string ngayNhapVien;
    string tenPhong;
    int soPhong;
    stirn chuyenKhoa
};

struct NhanSu {
    string hoTen;
    string chucVu;
    int Tuoi;    
};
struct BenhAn {
BenhNhan *bn;
    int MaSoBenhAn;
    string maBenhAn;
    string chuanDoan;
    string luuYQuanTrong;
};






BenhNhan* addPatient(BenhNhan* head, string hoTen, int tuoi, string diaChi, string maBenhNhan) {
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
}










int main() {
    
}
