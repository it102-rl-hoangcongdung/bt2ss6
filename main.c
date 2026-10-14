#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char maPhieu[MAX][15];
    char tenSach[MAX][50];
    int soNgayMuon[MAX];
    int tienPhat[MAX];
    int soLuong = 0;
    int choice;

    do {
        printf("\n================ HỆ THỐNG QUẢN LÝ MƯỢN TRẢ SÁCH (LIBRARY_WMS) ================\n");
        printf("1. Thêm lượt mượn sách mới\n");
        printf("2. Hiển thị danh sách mượn sách\n");
        printf("3. Cập nhật số ngày mượn theo Mã phiếu\n");
        printf("4. Xóa lượt mượn sách theo Mã phiếu\n");
        printf("5. Thống kê danh sách phiếu mượn bị phạt (Quá hạn > 14 ngày)\n");
        printf("6. Thoát chương trình\n");
        printf("==============================================================================\n");
        printf("Lựa chọn của bạn: ");

        if (scanf("%d", &choice) != 1) {
            printf("Lựa chọn không hợp lệ. Vui lòng thử lại!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                if (soLuong >= MAX) {
                    printf("Hệ thống đầy, không thể thêm phiếu mượn mới!\n");
                    break;
                }
                char tempMa[15];
                printf("Nhập mã phiếu mượn: ");
                fgets(tempMa, sizeof(tempMa), stdin);
                tempMa[strcspn(tempMa, "\n")] = '\0';

                int trung = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMa) == 0) {
                        trung = 1;
                        break;
                    }
                }

                if (trung) {
                    printf("Mã phiếu đã tồn tại trong hệ thống! Hủy thêm mới.\n");
                    break;
                }

                strcpy(maPhieu[soLuong], tempMa);

                printf("Nhập tên sách: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                tenSach[soLuong][strcspn(tenSach[soLuong], "\n")] = '\0';

                do {
                    printf("Nhập số ngày mượn thực tế: ");
                    if (scanf("%d", &soNgayMuon[soLuong]) != 1 || soNgayMuon[soLuong] <= 0) {
                        printf("Số ngày mượn không hợp lệ. Vui lòng nhập lại số nguyên > 0.\n");
                        while (getchar() != '\n');
                        soNgayMuon[soLuong] = 0;
                    }
                } while (soNgayMuon[soLuong] <= 0);
                while (getchar() != '\n');

                if (soNgayMuon[soLuong] > 14) {
                    tienPhat[soLuong] = (soNgayMuon[soLuong] - 14) * 5000;
                } else {
                    tienPhat[soLuong] = 0;
                }

                soLuong++;
                printf("Thêm lượt mượn sách thành công!\n");
                break;
            }
            case 2: {
                if (soLuong == 0) {
                    printf("Danh sách mượn sách hiện đang rỗng!\n");
                    break;
                }
                printf("================================ DANH SÁCH MƯỢN SÁCH ================================\n");
                printf("%-5s | %-12s | %-30s | %-10s | %-15s\n", "STT", "Mã Phiếu", "Tên Sách", "Số Ngày", "Tiền Phạt (VNĐ)");
                printf("-------------------------------------------------------------------------------------\n");
                int tongTien = 0;
                for (int i = 0; i < soLuong; i++) {
                    printf("%-5d | %-12s | %-30s | %-10d | %-15d\n", i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    tongTien += tienPhat[i];
                }
                printf("-------------------------------------------------------------------------------------\n");
                printf("Tổng tiền phạt toàn hệ thống: %d VNĐ\n", tongTien);
                break;
            }
            case 3: {
                if (soLuong == 0) {
                    printf("Danh sách mượn sách hiện đang rỗng!\n");
                    break;
                }
                char tempMa[15];
                printf("Nhập mã phiếu mượn cần cập nhật: ");
                fgets(tempMa, sizeof(tempMa), stdin);
                tempMa[strcspn(tempMa, "\n")] = '\0';

                int found = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMa) == 0) {
                        found = i;
                        break;
                    }
                }

                if (found == -1) {
                    printf("Không tìm thấy phiếu mượn có mã: %s\n", tempMa);
                } else {
                    printf("Tìm thấy phiếu mượn của sách: %s (Số ngày hiện tại: %d)\n", tenSach[found], soNgayMuon[found]);
                    do {
                        printf("Nhập số ngày mượn thực tế mới: ");
                        if (scanf("%d", &soNgayMuon[found]) != 1 || soNgayMuon[found] <= 0) {
                            printf("Số ngày mượn không hợp lệ. Vui lòng nhập lại số nguyên > 0.\n");
                            while (getchar() != '\n');
                            soNgayMuon[found] = 0;
                        }
                    } while (soNgayMuon[found] <= 0);
                    while (getchar() != '\n');

                    if (soNgayMuon[found] > 14) {
                        tienPhat[found] = (soNgayMuon[found] - 14) * 5000;
                    } else {
                        tienPhat[found] = 0;
                    }
                    printf("Cập nhật số ngày mượn thành công!\n");
                }
                break;
            }
            case 4: {
                if (soLuong == 0) {
                    printf("Danh sách mượn sách hiện đang rỗng!\n");
                    break;
                }
                char tempMa[15];
                printf("Nhập mã phiếu mượn cần xóa: ");
                fgets(tempMa, sizeof(tempMa), stdin);
                tempMa[strcspn(tempMa, "\n")] = '\0';

                int found = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMa) == 0) {
                        found = i;
                        break;
                    }
                }

                if (found == -1) {
                    printf("Không tìm thấy phiếu mượn có mã: %s\n", tempMa);
                } else {
                    for (int i = found; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }
                    soLuong--;
                    printf("Xóa phiếu mượn thành công!\n");
                }
                break;
            }
            case 5: {
                if (soLuong == 0) {
                    printf("Danh sách mượn sách hiện đang rỗng!\n");
                    break;
                }
                int count = 0;
                printf("=================== DANH SÁCH PHIẾU MƯỢN QUÁ HẠN ===================\n");
                printf("%-5s | %-12s | %-30s | %-10s | %-15s\n", "STT", "Mã Phiếu", "Tên Sách", "Số Ngày", "Tiền Phạt (VNĐ)");
                printf("-------------------------------------------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > 14) {
                        count++;
                        printf("%-5d | %-12s | %-30s | %-10d | %-15d\n", count, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    }
                }
                printf("-------------------------------------------------------------------------------------\n");
                if (count == 0) {
                    printf("Không có lượt mượn nào bị quá hạn phạt!\n");
                }
                break;
            }
            case 6:
                printf("Thoát chương trình. Hẹn gặp lại!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại!\n");
                break;
        }
    } while (choice != 6);

    return 0;
}