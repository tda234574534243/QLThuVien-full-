#include "Admin.cpp"
#include "Sach.cpp"
#include "PhieuMuon.cpp"
#include "BanDoc.cpp"
using namespace std;

void setColor4(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}

// Tạo giao diện để người dùng nhìn thấy và tương tác
void mainMenu() {
    system("cls");
    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor4(9); cout << "*             "; setColor4(10); cout << "MENU CHINH"; setColor4(9); cout << "              *\n";
    setColor4(9);cout << "* "; setColor4(15);cout << "1. Quan ly sach";  setColor4(9);cout << "                     *\n";
    setColor4(9);cout << "* ";setColor4(15);cout << "2. Quan ly ban doc";setColor4(9);cout << "                  *\n"; // Chỉnh sửa cho khớp với 1
    setColor4(9);cout << "* ";setColor4(15);cout << "3. Quan ly phieu muon";setColor4(9);cout << "               *\n"; // Chỉnh sửa cho khớp với 1
    setColor4(9);cout << "* ";setColor4(12);cout << "0. Thoat";setColor4(9);cout << "                            *\n"; // Chỉnh sửa cho khớp với 1
    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLySachMenu() {
    system("cls");
    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor4(9);
    cout << "*           ";
    setColor4(10);
    cout << "QUAN LY SACH";
    setColor4(9);
    cout << "              *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "1. Hien thi tat ca sach";
    setColor4(9);
    cout << "             *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "2. Them sach";
    setColor4(9);
    cout << "                        *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "3. Xoa sach";
    setColor4(9);
    cout << "                         *\n";

    setColor4(9);
    cout << "* ";
    setColor4(12);
    cout << "0. Tro ve";
    setColor4(9);
    cout << "                           *\n";

    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyBanDocMenu() {
    system("cls");
    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor4(9);
    cout << "*          ";
    setColor4(10);
    cout << "QUAN LY BAN DOC";
    setColor4(9);
    cout << "            *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "1. Hien thi tat ca ban doc";
    setColor4(9);
    cout << "          *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "2. Them ban doc";
    setColor4(9);
    cout << "                     *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "3. Xoa ban doc";
    setColor4(9);
    cout << "                      *\n";

    setColor4(9);
    cout << "* ";
    setColor4(12);
    cout << "0. Tro ve";
    setColor4(9);
    cout << "                           *\n";

    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyPhieuMuonMenu() {
    system("cls");
    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor4(9);
    cout << "*          ";
    setColor4(10);
    cout << "QUAN LY PHIEU MUON";
    setColor4(9);
    cout << "         *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "1. Hien thi tat ca phieu muon";
    setColor4(9);
    cout << "       *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "2. Muon sach";
    setColor4(9);
    cout << "                        *\n";

    setColor4(9);
    cout << "* ";
    setColor4(15);
    cout << "3. Tra sach";
    setColor4(9);
    cout << "                         *\n";

    setColor4(9);
    cout << "* ";
    setColor4(12);
    cout << "0. Tro ve";
    setColor4(9);
    cout << "                           *\n";

    setColor4(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void endChuongTrinh() {
    system("cls");
    setColor4(14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "*                                                                                   *\n";
    setColor4(14);
    cout << "*    "; setColor4(10); cout << "CAM ON VI DA SU DUNG DICH VU QUAN LY THU VIEN CUA TEAM NHAU NHUC NHU NHIEU"; setColor4(14); cout << "     * \n";
    setColor4(14);
    cout << "*                                                                                   *\n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}
// Chạy chương trình
int main() {
    Admin admin;
    if (!admin.login()) {
        return 0;
    }

    Sach sach;
    BanDoc banDoc;
    PhieuMuon phieuMuon;

    int iLuaChon;
    do {
        mainMenu();
        setColor4(11);
        cout << "Nhap lua chon: ";
        setColor4(15);
        cin >> iLuaChon;

        // Kiểm tra nhập liệu
        while (cin.fail() || iLuaChon < 0 || iLuaChon > 3) {
            setColor4(12);
            cout << "Lua chon khong hop le. Vui long nhap lai!! ";
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
            setColor4(11);
            cout << "Nhap lua chon: ";
            setColor4(15);
            cin >> iLuaChon;
        }

        switch (iLuaChon) {
        case 1: {
            int luaChonSach;
            do {
                quanLySachMenu();
                setColor4(11);
                cout << "Nhap lua chon: ";
                setColor4(15);
                cin >> luaChonSach;

                // Kiểm tra nhập liệu cho sách
                while (cin.fail() || luaChonSach < 0 || luaChonSach > 3) {
                    setColor4(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor4(11);
                    cout << "Nhap lua chon: ";
                    setColor4(15);
                    cin >> luaChonSach;
                }

                switch (luaChonSach) {
                case 1:
                    sach.hienThiTatCaSach();
                    break;
                case 2:
                    sach.themSach();
                    break;
                case 3:
                    sach.xoaSach();
                    break;
                }
                if (luaChonSach != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor4(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonSach;
                }
            } while (luaChonSach != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        case 2: {
            int luaChonBanDoc;
            do {
                quanLyBanDocMenu();
                setColor4(11);
                cout << "Nhap lua chon: ";
                setColor4(15);
                cin >> luaChonBanDoc;

                // Kiểm tra nhập liệu cho bạn đọc
                while (cin.fail() || luaChonBanDoc < 0 || luaChonBanDoc > 3) {
                    setColor4(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor4(11);
                    cout << "Nhap lua chon: ";
                    setColor4(15);
                    cin >> luaChonBanDoc;
                }

                switch (luaChonBanDoc) {
                case 1:
                    banDoc.hienThiTatCaBanDoc();
                    break;
                case 2:
                    banDoc.themBanDoc();
                    break;
                case 3:
                    banDoc.xoaBanDoc();
                    break;
                }
                if (luaChonBanDoc != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor4(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonBanDoc;
                }
            } while (luaChonBanDoc != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        case 3: {
            int luaChonPhieuMuon;
            do {
                quanLyPhieuMuonMenu();
                setColor4(11);
                cout << "Nhap lua chon: ";
                setColor4(15);
                cin >> luaChonPhieuMuon;

                // Kiểm tra nhập liệu cho phiếu mượn
                while (cin.fail() || luaChonPhieuMuon < 0 || luaChonPhieuMuon > 3) {
                    setColor4(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor4(11);
                    cout << "Nhap lua chon: ";
                    setColor4(15);
                    cin >> luaChonPhieuMuon;
                }

                switch (luaChonPhieuMuon) {
                case 1:
                    phieuMuon.hienThiTatCaPhieuMuon();
                    break;
                case 2:
                    phieuMuon.muonSach();
                    break;
                case 3:
                    phieuMuon.traSach();
                    break;
                }
                if (luaChonPhieuMuon != 0) {
                    // Ask user to press 1 to return to main menu
                    setColor4(14);
                    cout << "Nhan 1 de quay lai menu chinh: ";
                    cin >> luaChonPhieuMuon;
                }
            } while (luaChonPhieuMuon != 0); // Nhấn 0 để trở về menu chính
            break;
        }
        }
    } while (iLuaChon != 0); // Khi nhập 0 từ menu chính, chương trình sẽ thoát
    system("cls");
    endChuongTrinh();
    return 0;
}