#include <stdio.h>
#include <string.h>

#define MAX 100
#define TOTAL_ROOMS 52
#define MAX_NURSES_PER_ROOM 2  // Giới hạn y tá/phòng

// ----------------- STRUCT -----------------

typedef struct {
    int id;
    char cccd[20];
    char name[100];
    int age;
    char state[200];
    char history[50];
    int priority;
} Patient;

typedef struct {
    char name[100];
    char shift[50];
} Nurse;

typedef struct {
    Patient patients[MAX];
    int patientCount;

    Nurse nurses[MAX_NURSES_PER_ROOM];
    int nurseCount;

    char type[2];   // "S", "A", "F", "E", "O"
    int tier;
} Room;

// ----------------- Biến toàn cục -----------------

int patientIDCounter = 1;

// ----------------- HÀM HỖ TRỢ -----------------

int getMaxPatientsPerRoom(const char* type) {
    if (strcmp(type, "S") == 0) return 2;
    if (strcmp(type, "A") == 0) return 6;
    if (strcmp(type, "F") == 0) return 12;
    if (strcmp(type, "E") == 0) return 30;
    if (strcmp(type, "O") == 0) return 1;
    return MAX;
}

// ----------------- HÀM VỚI PATIENT -----------------

void addPatient(Room* room, Patient newPatient) {
    if (room->patientCount >= getMaxPatientsPerRoom(room->type)) {
        printf("Phòng đã đầy (%d bệnh nhân).\n", getMaxPatientsPerRoom(room->type));
        return;
    }

    newPatient.id = patientIDCounter++;
    room->patients[room->patientCount++] = newPatient;

    printf("Đã thêm bệnh nhân: %s (ID: %d)\n", newPatient.name, newPatient.id);
}

void deletePatientByID(Room* room, int id) {
    for (int i = 0; i < room->patientCount; i++) {
        if (room->patients[i].id == id) {
            for (int j = i; j < room->patientCount - 1; j++) {
                room->patients[j] = room->patients[j + 1];
            }
            room->patientCount--;
            printf("Đã xóa bệnh nhân có ID: %d\n", id);
            return;
        }
    }
    printf("Không tìm thấy bệnh nhân có ID: %d\n", id);
}

void printPatients(const Room* room) {
    printf("\nDanh sách bệnh nhân:\n");
    for (int i = 0; i < room->patientCount; i++) {
        Patient p = room->patients[i];
        printf("%d. ID: %d - %s - CCCD: %s - Tuổi: %d - Trạng thái: %s - Ưu tiên: %d\n",
            i + 1, p.id, p.name, p.cccd, p.age, p.state, p.priority);
    }
}

// ----------------- HÀM VỚI NURSE -----------------

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

// ----------------- PHÒNG -----------------

void initRoom(Room* room, const char* type, int tier) {
    strcpy(room->type, type);
    room->tier = tier;
    room->patientCount = 0;
    room->nurseCount = 0;
    printf("Khởi tạo phòng loại %s với giá tiền: %d\n", type, tier);
}

void setupHospital(Room hospital[]) {
    int index = 0;

    for (int i = 0; i < 6; i++)
        initRoom(&hospital[index++], "S", 5000000);

    for (int i = 0; i < 12; i++)
        initRoom(&hospital[index++], "A", 3000000);

    for (int i = 0; i < 30; i++)
        initRoom(&hospital[index++], "F", 1000000);

    for (int i = 0; i < 2; i++)
        initRoom(&hospital[index++], "E", 0);

    for (int i = 0; i < 2; i++)
        initRoom(&hospital[index++], "O", 0);
}

void printRoomInfo(const Room* room) {
    printf("\n== Thông tin phòng ==\n");
    printf("Loại phòng: %s-tier\n", room->type);
    printf("Giá tiền dịch vụ: %d\n", room->tier);
    printf("Số bệnh nhân: %d/%d\n", room->patientCount, getMaxPatientsPerRoom(room->type));
    printf("Số y tá: %d/%d\n", room->nurseCount, MAX_NURSES_PER_ROOM);
}

// ----------------- TÌM PHÒNG TRỐNG -----------------

Room* findAvailableRoom(Room hospital[], const char* type) {
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        if (strcmp(hospital[i].type, type) == 0 &&
            hospital[i].patientCount < getMaxPatientsPerRoom(type)) {
            return &hospital[i];
        }
    }
    return NULL;
}

// ----------------- BÁO CÁO -----------------

void printHospitalReport(Room hospital[]) {
    int totalPatients = 0;
    long totalRevenue = 0;

    int available_S = 0, available_A = 0, available_F = 0;
    int available_E = 0, available_O = 0;

    for (int i = 0; i < TOTAL_ROOMS; i++) {
        totalPatients += hospital[i].patientCount;
        totalRevenue += hospital[i].patientCount * hospital[i].tier;

        if (hospital[i].patientCount < getMaxPatientsPerRoom(hospital[i].type)) {
            if (strcmp(hospital[i].type, "S") == 0) available_S++;
            else if (strcmp(hospital[i].type, "A") == 0) available_A++;
            else if (strcmp(hospital[i].type, "F") == 0) available_F++;
            else if (strcmp(hospital[i].type, "E") == 0) available_E++;
            else if (strcmp(hospital[i].type, "O") == 0) available_O++;
        }
    }

    printf("\n===== BÁO CÁO BỆNH VIỆN =====\n");
    printf("Tổng số bệnh nhân: %d\n", totalPatients);
    printf("Tổng tiền viện phí (ước tính): %ld VND\n", totalRevenue);

    printf("Phòng còn trống:\n");
    printf(" - Phòng S: %d\n", available_S);
    printf(" - Phòng A: %d\n", available_A);
    printf(" - Phòng F: %d\n", available_F);
    printf(" - Cấp cứu: %d\n", available_E);
    printf(" - Phẫu thuật: %d\n", available_O);
}

// ----------------- MAIN -----------------

int main() {
    Room hospital[TOTAL_ROOMS];
    setupHospital(hospital);

    // Tạo bệnh nhân
    Patient p1 = { .cccd = "0123456789", .name = "Nguyen Van A", .age = 35,
                  .state = "Sốt cao", .history = "2025-05-14", .priority = 1 };

    Room* roomS = findAvailableRoom(hospital, "S");
    if (roomS) {
        addPatient(roomS, p1);
    }

    // Thêm y tá
    Nurse n1 = { "Le Thi B", "Sáng" };
    Nurse n2 = { "Tran Van C", "Chiều" };
    Nurse n3 = { "Nguyen Van D", "Tối" };

    addNurse(&hospital[6], n1);
    addNurse(&hospital[6], n2);
    addNurse(&hospital[6], n3); // Bị từ chối

    // In thông tin
    printRoomInfo(roomS);
    printPatients(roomS);
    printNurses(&hospital[6]);

    // Báo cáo
    printHospitalReport(hospital);

    return 0;
}
