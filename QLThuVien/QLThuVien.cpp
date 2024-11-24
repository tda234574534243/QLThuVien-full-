#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>  // Cho hàm exit
#include <conio.h>  // Cho hàm _getch() để đặt mật khẩu
#include <ctime>
#include <vector>
#include <limits> // Thư viện cần thiết để sử dụng std::numeric_limits
#include <windows.h>
using namespace std;

// hàm tô màu
void setColor(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}
// Tạo các Class quản lý thư viện
class Admin {
private:
    string _strUserName;
    string _strPassWord;

public:
    Admin(string strUserName = "", string strPassWord = "") : _strUserName(strUserName), _strPassWord(strPassWord) {}

    bool verifyLogin(string strInputUser, string strInputPass) {
        return (strInputUser == _strUserName && strInputPass == _strPassWord);
    }

    bool login() {
        ifstream adminFile("Admin.txt");
        if (!adminFile.is_open()) {
            setColor(4);
            cout << "Khong the mo file Admin.txt\n";
            return false;
        }

        string strUserInput, strPassInput;
        int iAttempts = 0;

        while (iAttempts < 3) {
            // Hiển thị giao diện đăng nhập
            setColor(6);
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            setColor(6);
            cout << "*";
            setColor(10);
            cout << "          DANG NHAP HE THONG         ";
            setColor(6);
            cout << "*\n";
            setColor(6);
            cout << "* * * * * * * * * * * * * * * * * * * *\n";
            setColor(9);
            cout << "User: ";
            setColor(15);
            cin >> strUserInput;
            setColor(9);
            cout << "Password: ";
            setColor(15);

            char szCharInput;
            strPassInput = "";

            while (true) {
                szCharInput = _getch();

                if (szCharInput == 13) { // Enter key
                    break;
                }
                else if (szCharInput == 8) { // Backspace key
                    if (!strPassInput.empty()) {
                        cout << "\b \b"; // Xóa ký tự trên màn hình
                        strPassInput.pop_back(); // Xóa ký tự cuối cùng trong chuỗi mật khẩu
                    }
                }
                else if (szCharInput == 224 || szCharInput == -32) { // Phím điều khiển (arrow keys)
                    int nextCh = _getch(); // Lấy ký tự tiếp theo
                }
                else if (szCharInput >= 0 && szCharInput <= 255 && isprint(szCharInput)) {
                    bool isShiftHeld = (GetKeyState(VK_SHIFT) & 0x8000) != 0;

                    if (isShiftHeld && isalpha(szCharInput)) {
                        szCharInput = toupper(szCharInput);
                    }
                    else if (isShiftHeld && isdigit(szCharInput)) {
                        switch (szCharInput) {
                        case '1': szCharInput = '!'; break;
                        case '2': szCharInput = '@'; break;
                        case '3': szCharInput = '#'; break;
                        case '4': szCharInput = '$'; break;
                        case '5': szCharInput = '%'; break;
                        case '6': szCharInput = '^'; break;
                        case '7': szCharInput = '&'; break;
                        case '8': szCharInput = '*'; break;
                        case '9': szCharInput = '('; break;
                        case '0': szCharInput = ')'; break;
                        }
                    }

                    strPassInput.push_back(szCharInput);
                    cout << "*";
                }
            }

            cout << endl;

            string strLine;
            bool isLoginSuccessful = false;

            while (getline(adminFile, strLine)) {
                stringstream ss(strLine);
                string strStoredUser, strStoredPass;

                getline(ss, strStoredUser, '|');
                getline(ss, strStoredPass, '|');

                Admin admin(strStoredUser, strStoredPass);
                if (admin.verifyLogin(strUserInput, strPassInput)) {
                    setColor(2);
                    cout << "Dang nhap thanh cong!\n";
                    isLoginSuccessful = true;
                    break;
                }
            }

            adminFile.clear();
            adminFile.seekg(0, ios::beg);

            if (isLoginSuccessful) {
                return true;
            }
            else {
                iAttempts++; // Tăng số lần thử

                setColor(4);
                cout << "Sai user hoac password. Vui long thu lai.\n";
                cout << "Ban da nhap sai " << iAttempts << " lan. Qua 3 lan se thoat chuong trinh.\n";

                // Kiểm tra nếu đã đủ 3 lần sai thì không cần gọi system("cls") nữa
                if (iAttempts < 3) {
                    // Đợi một khoảng thời gian ngắn để người dùng có thể đọc thông báo trước khi xóa màn hình
                    Sleep(1000);
                    system("cls");
                }
            }
        }

        setColor(4);
        cout << "Ban da nhap sai qua nhieu, thoat khoi he thong!\n";
        return false;
    }
};
class Sach {
public:
    string _strMaSach, _strTenSach, _strTacGia, _strNhaXuatBan, _strNgayNhapKho;
    int _iGiaBan, _iNamPhatHanh, _iSoTrang, _iTinhTrang;

    Sach() : _iGiaBan(0), _iNamPhatHanh(0), _iSoTrang(0), _iTinhTrang(0) {}

    void hienThiThongTin() {
        // Đặt màu sắc cho các tiêu đề
        setColor(10); // Màu xanh lá cây cho tiêu đề
        cout << "Ma Sach: ";
        setColor(15); // Màu trắng cho giá trị
        cout << _strMaSach << endl;

        setColor(10);
        cout << "Ten Sach: ";
        setColor(11);
        cout << _strTenSach << endl;

        setColor(10);
        cout << "Tac Gia: ";
        setColor(13);
        cout << _strTacGia << endl;

        setColor(10);
        cout << "Nha Xuat Ban: ";
        setColor(15);
        cout << _strNhaXuatBan << endl;

        setColor(10);
        cout << "Gia Ban: ";
        setColor(15);
        cout << _iGiaBan; setColor(14); cout << " dong" << endl;

        setColor(10);
        cout << "Nam Phat Hanh: ";
        setColor(15);
        cout << _iNamPhatHanh << endl;

        setColor(10);
        cout << "So Trang: ";
        setColor(15);
        cout << _iSoTrang; setColor(14); cout <<" trang" << endl;

        setColor(10);
        cout << "Ngay Nhap Kho: ";
        setColor(15);
        cout << _strNgayNhapKho << endl;

        setColor(10);
        cout << "Tinh Trang: ";
        setColor(15);
        cout << (_iTinhTrang == 0 ? "Chua muon" : "Dang duoc muon") << endl;

        // Đặt lại màu sắc cho ngắt dòng
        setColor(6); // Màu vàng cho ngắt dòng
        cout << "----------------------------\n";
        setColor(7); // Đặt lại màu sắc về mặc định nếu cần
    }

    void hienThiTatCaSach() {
        ifstream file("Sach.txt");
        if (!file.is_open()) {
            cout << "Khong the mo file Sach.txt\n";
            return;
        }

        string strLine;
        while (getline(file, strLine)) {
            Sach SachThem;
            stringstream ss(strLine);

            // Đảm bảo rằng các trường được phân tách đúng
            getline(ss, SachThem._strMaSach, '|');
            getline(ss, SachThem._strTenSach, '|');
            getline(ss, SachThem._strTacGia, '|');
            getline(ss, SachThem._strNhaXuatBan, '|');
            ss >> SachThem._iGiaBan;
            ss.ignore(); // Bỏ qua ký tự '|'
            ss >> SachThem._iNamPhatHanh;
            ss.ignore(); // Bỏ qua ký tự '|'
            ss >> SachThem._iSoTrang;
            ss.ignore(); // Bỏ qua ký tự '|'
            getline(ss, SachThem._strNgayNhapKho, '|');
            ss >> SachThem._iTinhTrang;

            SachThem.hienThiThongTin();
        }

        file.close(); // Đóng file
    }

    void themSach() {
        ofstream file("Sach.txt", ios::app);
        if (!file.is_open()) {
            setColor(14);
            cout << "Khong the mo file Sach.txt\n";
            return;
        }

        Sach SachThem;
        setColor(11);
        cout << "Nhap Ma Sach(Vd: B001, B002,...): ";
        setColor(15);
        cin >> SachThem._strMaSach;

        // Kiểm tra mã sách đã tồn tại
        ifstream checkFile("Sach.txt");
        string strLine;
        while (getline(checkFile, strLine)) {
            if (strLine.find(SachThem._strMaSach) != string::npos) {
                setColor(14);
                cout << "Ma sach da ton tai. Khong the them.\n";
                checkFile.close();
                file.close();
                return;
            }
        }
        checkFile.close();

        // Nhập và kiểm tra dữ liệu
        setColor(11);
        cout << "Nhap Ten Sach: ";
        setColor(15);
        cin.ignore();
        getline(cin, SachThem._strTenSach);

        setColor(11);
        cout << "Nhap Tac Gia: ";
        setColor(15);
        getline(cin, SachThem._strTacGia);

        setColor(11);
        cout << "Nhap Nha Xuat Ban: ";
        setColor(15);
        getline(cin, SachThem._strNhaXuatBan);

        while (true) {
            setColor(11);
            cout << "Nhap Gia Ban: ";
            setColor(15);
            cin >> SachThem._iGiaBan;

            if (cin.fail() || SachThem._iGiaBan <= 0) {
                setColor(12);
                cout << "Gia ban khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor(11);
            cout << "Nhap Nam Phat Hanh (1900 - hien tai): ";
            setColor(15);
            cin >> SachThem._iNamPhatHanh;

            if (cin.fail() || SachThem._iNamPhatHanh < 1900 || SachThem._iNamPhatHanh > 2024) {
                setColor(12);
                cout << "Nam phat hanh khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor(11);
            cout << "Nhap So Trang (so trang phai nhap it nhat la 1): ";
            setColor(15);
            cin >> SachThem._iSoTrang;

            if (cin.fail() || SachThem._iSoTrang <= 0) {
                setColor(12);
                cout << "So trang khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor(11);
            cout << "Nhap Ngay Nhap Kho (yyyy-mm-dd): ";
            setColor(15);
            cin >> SachThem._strNgayNhapKho;

            // Kiểm tra ngày hợp lệ
            if (!kiemTraNgayHopLe(SachThem._strNgayNhapKho)) {
                setColor(12);
                cout << "Ngay nhap kho khong hop le. Vui long nhap lai!\n";
            }
            else {
                break;
            }
        }

        SachThem._iTinhTrang = 0; // Mặc định tình trạng chưa được mượn

        // Ghi vào file
        file << SachThem._strMaSach << "|" << SachThem._strTenSach << "|" << SachThem._strTacGia << "|"
            << SachThem._strNhaXuatBan << "|" << SachThem._iGiaBan << "|" << SachThem._iNamPhatHanh
            << "|" << SachThem._iSoTrang << "|" << SachThem._strNgayNhapKho << "|" << SachThem._iTinhTrang << endl;

        setColor(10);
        cout << "Them SachThem thanh cong!\n";
        file.close();
    }

    bool kiemTraNgayHopLe(const string& Ngay) {
        int nam, thang, ngayTrongThang;
        if (sscanf(Ngay.c_str(), "%d-%d-%d", &nam, &thang, &ngayTrongThang) != 3) {
            return false;
        }

        // Kiểm tra năm, tháng, ngày
        if (nam < 1900 || nam > 2024 || thang < 1 || thang > 12 || ngayTrongThang < 1) {
            return false;
        }

        // Số ngày trong tháng
        int soNgayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0)) {
            soNgayTrongThang[1] = 29; // Năm nhuận, tháng 2 có 29 ngày
        }

        return ngayTrongThang <= soNgayTrongThang[thang - 1];
    }


    void xoaSach() {
        string strMaSachXoa;
        setColor(11);
        cout << "Nhap Ma Sach can xoa: ";
        setColor(15);
        cin >> strMaSachXoa;

        ifstream file("Sach.txt");
        ofstream tempFile("temp.txt");
        bool bSachTonTai = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor(12);
            cout << "Khong the mo file\n";
            return;
        }

        string strLine;
        while (getline(file, strLine)) {
            if (strLine.find(strMaSachXoa) == 0) {
                stringstream ss(strLine);
                string _strMaSach;
                for (int i = 0; i < 8; i++) getline(ss, _strMaSach, '|');
                int _iTinhTrang;
                ss >> _iTinhTrang;

                if (_iTinhTrang == 0) {
                    bSachTonTai = true;
                }
                else {
                    setColor(12);
                    cout << "Khong the xoa vi sach dang duoc muon\n";
                    tempFile << strLine << endl;
                    continue;
                }
            }
            else {
                tempFile << strLine << endl;
            }
        }

        file.close();
        tempFile.close();

        if (bSachTonTai) {
            remove("Sach.txt");
            if (rename("temp.txt", "Sach.txt") != 0) {
                setColor(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor(10);
                cout << "Xoa sach thanh cong!\n";
            }
        }
        else {
            setColor(12);
            cout << "Khong tim thay ma sach hoac sach dang duoc muon\n";
            remove("temp.txt");
        }
    }
};
class PhieuMuon {
public:
    int _iSoPhieuMuon;
    string _strMaBanDoc, _strMaSach, _strNgayMuon, _strNgayPhaiTra;
    int _iTinhTrang;

    PhieuMuon() : _iSoPhieuMuon(0), _iTinhTrang(0) {}

    void hienThiThongTin() {
        setColor(10);
        cout << "So Phieu Muon: "; setColor(14); cout << _iSoPhieuMuon << endl;
        setColor(10);
        cout << "Ma Ban Doc: "; setColor(13); cout << _strMaBanDoc << endl;
        setColor(10);
        cout << "Ma Sach: "; setColor(11); cout << _strMaSach << endl;
        setColor(10);
        cout << "Ngay Muon: "; setColor(9);cout << _strNgayMuon << endl;
        setColor(10);
        cout << "Ngay Phai Tra: "; setColor(9);cout << _strNgayPhaiTra << endl;
        setColor(10);
        cout << "Tinh Trang: "; setColor(15); cout << (_iTinhTrang == 1 ? "Dang muon" : "Da tra") << endl;
        setColor(14);
        cout << "----------------------------\n";
        setColor(8);
    }

    void muonSach() {
        ofstream file("PhieuMuon.txt", ios::app);
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return;
        }

        PhieuMuon Phieu;

        // Đọc số phiếu mượn cuối cùng từ file
        ifstream phieuFile("PhieuMuon.txt");
        int iMaxSoPhieuMuon = 0;
        string strLine;

        while (getline(phieuFile, strLine)) {
            stringstream ss(strLine);
            ss >> Phieu._iSoPhieuMuon; // Lấy số phiếu mượn
            if (Phieu._iSoPhieuMuon > iMaxSoPhieuMuon) {
                iMaxSoPhieuMuon = Phieu._iSoPhieuMuon; // Cập nhật số phiếu mượn lớn nhất
            }
        }
        Phieu._iSoPhieuMuon = iMaxSoPhieuMuon + 1; // Tăng số phiếu mượn lên 1
        setColor(11);
        cout << "So Phieu Muon: "; setColor(15); cout << Phieu._iSoPhieuMuon << endl; // Hiển thị số phiếu mượn mới
        setColor(11);
        cout << "Nhap Ma Ban Doc: ";
        setColor(15);
        cin >> Phieu._strMaBanDoc;
        setColor(11);
        cout << "Nhap Ma Sach: ";
        setColor(15);
        cin >> Phieu._strMaSach;

        ifstream sachFile("Sach.txt");
        bool bSachTonTai = false;
        bool bBachDaDuocMuon = false;

        while (getline(sachFile, strLine)) {
            if (strLine.find(Phieu._strMaSach) == 0) {
                bSachTonTai = true;
                stringstream ss(strLine);
                int _iTinhTrang;
                ss.seekg(0, ios::end);
                ss.seekg(-1, ios::cur);
                ss >> _iTinhTrang;

                if (_iTinhTrang == 0) { // Sách chưa được mượn
                    Phieu._iTinhTrang = 1;
                    time_t Now = time(0);
                    tm* ltm = localtime(&Now);
                    stringstream date;
                    date << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                    Phieu._strNgayMuon = date.str();

                    // Nhập ngày phải trả hoặc mặc định là 7 ngày sau
                    setColor(11);
                    cout << "Nhap Ngay Phai Tra (yyyy-mm-dd) hoac nhan Enter de mac dinh tra sau 7 ngay: ";
                    string ngayTraInput;
                    setColor(15);
                    cin.ignore(); // Bỏ qua ký tự newline
                    getline(cin, ngayTraInput);

                    if (ngayTraInput.empty()) { // Nếu không nhập gì
                        // Tính ngày trả là 7 ngày sau ngày mượn
                        ltm->tm_mday += 7; // Cộng 7 ngày
                        mktime(ltm); // Cập nhật lại cấu trúc thời gian
                        stringstream dateTra;
                        dateTra << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday;
                        Phieu._strNgayPhaiTra = dateTra.str();
                    }
                    else {
                        Phieu._strNgayPhaiTra = ngayTraInput; // Gán ngày phải trả nhập vào
                    }

                    // Ghi thông tin vào file phiếu mượn
                    file << Phieu._iSoPhieuMuon << "|" << Phieu._strMaBanDoc << "|" << Phieu._strMaSach << "|"
                        << Phieu._strNgayMuon << "|" << Phieu._strNgayPhaiTra << "|" << Phieu._iTinhTrang << endl;
                    setColor(10);
                    cout << "Muon sach thanh cong!\n";

                    // Cập nhật trạng thái sách trong file
                    sachFile.close();

                    // Cập nhật trạng thái sách trong file Sach.txt
                    ofstream tempSachFile("tempSach.txt");
                    ifstream sachFileForUpdate("Sach.txt");

                    while (getline(sachFileForUpdate, strLine)) {
                        if (strLine.find(Phieu._strMaSach) == 0) {
                            tempSachFile << strLine.substr(0, strLine.size() - 1) << "1" << endl; // Cập nhật trạng thái sách
                        }
                        else {
                            tempSachFile << strLine << endl;
                        }
                    }

                    sachFileForUpdate.close();
                    tempSachFile.close();

                    remove("Sach.txt");
                    if (rename("tempSach.txt", "Sach.txt") != 0) {
                        setColor(12);
                        cout << "Khong the doi ten file Sach.txt\n";
                    }

                    file.close(); // Đóng file sau khi ghi
                    return; // Ngưng vòng lặp khi đã tìm thấy sách
                }
                else {
                    setColor(14);
                    cout << "Sach da co ai do muon roi. Vui long cho nhe!\n";
                    bBachDaDuocMuon = true; // Sách đã được mượn
                    break; // Ngưng vòng lặp khi đã tìm thấy sách
                }
            }
        }

        sachFile.close();

        if (bSachTonTai && !bBachDaDuocMuon) {
            setColor(14);
            cout << "Sach da duoc muon!\n";
        }
        else if (!bSachTonTai) {
            setColor(12);
            cout << "Khong tim thay sach!\n";
        }

        file.close();
    }

    void hienThiTatCaPhieuMuon() {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return;
        }

        string strLine;
        while (getline(file, strLine)) {
            PhieuMuon Phieu;
            stringstream ss(strLine);
            string _strMaSach;

            ss >> Phieu._iSoPhieuMuon;
            ss.ignore(); // Bỏ qua ký tự '|' sau _iSoPhieuMuon
            getline(ss, Phieu._strMaBanDoc, '|');
            getline(ss, Phieu._strMaSach, '|');
            getline(ss, Phieu._strNgayMuon, '|');
            getline(ss, Phieu._strNgayPhaiTra, '|');
            ss >> Phieu._iTinhTrang;

            Phieu.hienThiThongTin();
        }

        file.close();
    }

    void traSach() {
        int soPhieuTra;
        setColor(11);
        cout << "Nhap So Phieu Muon can tra: ";
        setColor(15);
        cin >> soPhieuTra;

        ifstream file("PhieuMuon.txt");
        ofstream tempFile("temp.txt");
        bool timThayPhieu = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor(12);
            cout << "Khong the mo file\n";
            return;
        }

        string strLine;

        while (getline(file, strLine)) {
            stringstream ss(strLine);
            int _iSoPhieuMuon;
            ss >> _iSoPhieuMuon;

            if (_iSoPhieuMuon == soPhieuTra) {
                timThayPhieu = true;
                string _strMaSach;
                getline(ss, _strMaSach, '|');

                ifstream sachFile("Sach.txt");
                ofstream tempSachFile("tempSach.txt");

                string lineSach;
                while (getline(sachFile, lineSach)) {
                    if (lineSach.find(_strMaSach) == 0) {
                        tempSachFile << lineSach.substr(0, lineSach.size() - 1) << "0" << endl; // Cập nhật trạng thái sách
                    }
                    else {
                        tempSachFile << lineSach << endl;
                    }
                }

                sachFile.close();
                tempSachFile.close();

                remove("Sach.txt");
                if (rename("tempSach.txt", "Sach.txt") != 0) {
                    setColor(12);
                    cout << "Khong the doi ten file Sach.txt\n";
                }
                setColor(10);
                cout << "Tra sach thanh cong!\n";
            }
            else {
                tempFile << strLine << endl;
            }
        }

        file.close();
        tempFile.close();

        if (timThayPhieu) {
            remove("PhieuMuon.txt");
            if (rename("temp.txt", "PhieuMuon.txt") != 0) {
                setColor(12);
                cout << "Khong the doi ten file PhieuMuon.txt\n";
            }
        }
        else {
            setColor(14);
            cout << "Khong tim thay so Phieu muon\n";
            remove("temp.txt");
        }
    }
};
class BanDoc {
public:
    string _strMaBanDoc, _strTenBanDoc, _strKhoa;
    int _iNgaySinh, _iThangSinh, _iNamSinh;
    string _strNgayDangKy; // Thêm trường cho ngày đăng ký

    BanDoc() : _iNgaySinh(1), _iThangSinh(1), _iNamSinh(1970) {
        // Lấy ngày hiện tại
        time_t Now = time(0);
        tm* ltm = localtime(&Now);
        // Định dạng ngày đăng ký
        _strNgayDangKy = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    }

    void hienThiTatCaBanDoc() {
        ifstream file("BanDoc.txt");
        if (!file.is_open()) {
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        string strLine;
        while (getline(file, strLine)) {
            BanDoc banDoc;
            stringstream ss(strLine);

            getline(ss, banDoc._strMaBanDoc, '|');
            getline(ss, banDoc._strTenBanDoc, '|');
            getline(ss, banDoc._strKhoa, '|');

            // Đọc ngày, tháng, năm sinh
            ss >> banDoc._iNgaySinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            ss >> banDoc._iThangSinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            ss >> banDoc._iNamSinh;
            ss.ignore(); // Bỏ qua ký tự phân cách
            getline(ss, banDoc._strNgayDangKy, '|'); // Đọc ngày đăng ký

            // Hiển thị thông tin
            banDoc.hienThiThongTin();
        }

        file.close();
    }

    bool isValidDate(int day, int month, int year) {
        if (year < 1900 || year > 2024) return false;
        if (month < 1 || month > 12) return false;
        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            daysInMonth[1] = 29; // Năm nhuận
        }
        return day > 0 && day <= daysInMonth[month - 1];
    }

    void themBanDoc() {
        ofstream file("BanDoc.txt", ios::app);
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        BanDoc banDoc;
        setColor(11);
        cout << "Nhap Ma Ban Doc (MSSV)(VD: 49.01.104.003): ";
        setColor(15);
        cin >> banDoc._strMaBanDoc;

        // Kiểm tra mã bạn đọc đã tồn tại
        ifstream checkFile("BanDoc.txt");
        string strLine;
        while (getline(checkFile, strLine)) {
            if (strLine.find(banDoc._strMaBanDoc) != string::npos) {
                setColor(14);
                cout << "Ma ban doc da ton tai. Khong the them.\n";
                checkFile.close();
                file.close();
                return;
            }
        }
        checkFile.close();

        setColor(11);
        cout << "Nhap Ten Ban Doc: ";
        setColor(15);
        cin.ignore();
        getline(cin, banDoc._strTenBanDoc);
        setColor(11);
        cout << "Nhap Khoa (Khoa dao tao): ";
        setColor(15);
        getline(cin, banDoc._strKhoa);

        do {
            setColor(11);
            cout << "Nhap Ngay Sinh (dd mm yyyy): ";
            setColor(15);

            cin >> banDoc._iNgaySinh >> banDoc._iThangSinh >> banDoc._iNamSinh;

            if (cin.fail()) {
                // Xử lý lỗi nhập liệu
                cin.clear(); // Xóa trạng thái lỗi của cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu còn lại trong bộ đệm
                setColor(12);
                cout << "Ngay sinh khong hop le. Vui long nhap lai!\n";
                continue; // Quay lại đầu vòng lặp
            }

            if (!isValidDate(banDoc._iNgaySinh, banDoc._iThangSinh, banDoc._iNamSinh)) {
                setColor(12);
                cout << "Ngay sinh khong hop le. Vui long nhap lai!\n";
            }
            else {
                break; // Thoát vòng lặp khi ngày hợp lệ
            }

        } while (true);

        // Ghi vào file
        file << banDoc._strMaBanDoc << "|" << banDoc._strTenBanDoc << "|" << banDoc._strKhoa << "|"
            << banDoc._iNgaySinh << "|" << banDoc._iThangSinh << "|" << banDoc._iNamSinh << "|"
            << banDoc._strNgayDangKy << endl;

        setColor(10);
        cout << "Them ban doc thanh cong!\n";
        file.close();
    }


    void hienThiThongTin() {
        setColor(10);
        cout << "Ma Ban Doc: "; setColor(11); cout << _strMaBanDoc << endl;
        setColor(10);
        cout << "Ten Ban Doc: "; setColor(13); cout << _strTenBanDoc << endl;
        setColor(10);
        cout << "Khoa: "; setColor(15); cout << _strKhoa << endl;
        setColor(10);
        cout << "Ngay Sinh: "; setColor(15); cout << _iNgaySinh << "/" << _iThangSinh << "/" << _iNamSinh << endl;
        setColor(10);
        cout << "Ngay Dang Ky: "; setColor(9); cout << _strNgayDangKy << endl; // Hiển thị ngày đăng ký
        setColor(14);
        cout << "----------------------------\n";
        setColor(8);
    }

    void xoaBanDoc() {
        string strMaBanDocXoa;
        setColor(11);
        cout << "Nhap Ma Ban Doc can xoa: ";
        setColor(15);
        cin >> strMaBanDocXoa;

        ifstream file("BanDoc.txt");
        ofstream tempFile("temp.txt");
        bool bBanDocTonTai = false;
        bool bCoPhieuMuon = false;

        if (!file.is_open()) {
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        string strLine;
        while (getline(file, strLine)) {
            if (strLine.find(strMaBanDocXoa) == 0) {
                bBanDocTonTai = true;
                // Kiểm tra nếu bạn đọc có phiếu mượn nào không
                bCoPhieuMuon = checkPhieuMuon(strMaBanDocXoa);
                if (bCoPhieuMuon) {
                    setColor(12);
                    cout << "Khong the xoa ban doc, vi ban doc dang co Phieu muon\n";
                }
                // Nếu có phiếu mượn, không ghi vào tệp tạm
            }
            else {
                tempFile << strLine << endl; // Ghi lại thông tin của bạn đọc không bị xóa
            }
        }

        file.close();
        tempFile.close();

        if (bBanDocTonTai && !bCoPhieuMuon) {
            // Nếu bạn đọc tồn tại và không có phiếu mượn, thực hiện xóa
            remove("BanDoc.txt");
            if (rename("temp.txt", "BanDoc.txt") != 0) {
                setColor(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor(10);
                cout << "Xoa ban doc thanh cong!\n";
            }
        }
        else if (!bBanDocTonTai) {
            setColor(14);
            cout << "Khong tim thay ma ban doc\n";
            remove("temp.txt"); // Xóa file tạm nếu không tìm thấy
        }
    }

    // Hàm kiểm tra xem bạn đọc có phiếu mượn nào không
    bool checkPhieuMuon(const string& _strMaBanDoc) {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor(12);
            cout << "Khong the mo file PhieuMuon.txt\n";
            return false;
        }

        string strLine;
        while (getline(file, strLine)) {
            string strMaBanDocPhieu;
            stringstream ss(strLine);

            // Đọc _iSoPhieuMuon (bỏ qua nếu không cần thiết)
            getline(ss, strMaBanDocPhieu, '|'); // Đọc _iSoPhieuMuon (bỏ qua)
            getline(ss, strMaBanDocPhieu, '|'); // Đọc _strMaBanDoc

            if (strMaBanDocPhieu == _strMaBanDoc) {
                file.close();
                return true; // Có phiếu mượn
            }
        }

        file.close();
        return false; // Không có phiếu mượn
    }
};

// Tạo giao diện để người dùng nhìn thấy và tương tác
void mainMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9); cout << "*             "; setColor(10); cout << "MENU CHINH"; setColor(9); cout << "              *\n";
    setColor(9);cout << "* "; setColor(15);cout << "1. Quan ly sach";  setColor(9);cout << "                     *\n";
    setColor(9);cout << "* ";setColor(15);cout << "2. Quan ly ban doc";setColor(9);cout << "                  *\n"; // Chỉnh sửa cho khớp với 1
    setColor(9);cout << "* ";setColor(15);cout << "3. Quan ly phieu muon";setColor(9);cout << "               *\n"; // Chỉnh sửa cho khớp với 1
    setColor(9);cout << "* ";setColor(12);cout << "0. Thoat";setColor(9);cout << "                            *\n"; // Chỉnh sửa cho khớp với 1
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLySachMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*           ";
    setColor(10);
    cout << "QUAN LY SACH";
    setColor(9);
    cout << "              *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca sach";
    setColor(9);
    cout << "             *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Them sach";
    setColor(9);
    cout << "                        *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Xoa sach";
    setColor(9);
    cout << "                         *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyBanDocMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*          ";
    setColor(10);
    cout << "QUAN LY BAN DOC";
    setColor(9);
    cout << "            *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca ban doc";
    setColor(9);
    cout << "          *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Them ban doc";
    setColor(9);
    cout << "                     *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Xoa ban doc";
    setColor(9);
    cout << "                      *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void quanLyPhieuMuonMenu() {
    system("cls");
    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
    setColor(9);
    cout << "*          ";
    setColor(10);
    cout << "QUAN LY PHIEU MUON";
    setColor(9);
    cout << "         *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "1. Hien thi tat ca phieu muon";
    setColor(9);
    cout << "       *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "2. Muon sach";
    setColor(9);
    cout << "                        *\n";

    setColor(9);
    cout << "* ";
    setColor(15);
    cout << "3. Tra sach";
    setColor(9);
    cout << "                         *\n";

    setColor(9);
    cout << "* ";
    setColor(12);
    cout << "0. Tro ve";
    setColor(9);
    cout << "                           *\n";

    setColor(6);
    cout << "* * * * * * * * * * * * * * * * * * * *\n";
}
void endChuongTrinh() {
    system("cls");
    setColor(14);
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
    cout << "*                                                                                   *\n";
    setColor(14);
    cout << "*    "; setColor(10); cout << "CAM ON VI DA SU DUNG DICH VU QUAN LY THU VIEN CUA TEAM NHAU NHUC NHU NHIEU"; setColor(14); cout << "     * \n";
    setColor(14);
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
        setColor(11);
        cout << "Nhap lua chon: ";
        setColor(15);
        cin >> iLuaChon;

        // Kiểm tra nhập liệu
        while (cin.fail() || iLuaChon < 0 || iLuaChon > 3) {
            setColor(12);
            cout << "Lua chon khong hop le. Vui long nhap lai!! ";
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
            setColor(11);
            cout << "Nhap lua chon: ";
            setColor(15);
            cin >> iLuaChon;
        }

        switch (iLuaChon) {
        case 1: {
            int luaChonSach;
            do {
                quanLySachMenu();
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonSach;

                // Kiểm tra nhập liệu cho sách
                while (cin.fail() || luaChonSach < 0 || luaChonSach > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
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
                    setColor(14);
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
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonBanDoc;

                // Kiểm tra nhập liệu cho bạn đọc
                while (cin.fail() || luaChonBanDoc < 0 || luaChonBanDoc > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
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
                    setColor(14);
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
                setColor(11);
                cout << "Nhap lua chon: ";
                setColor(15);
                cin >> luaChonPhieuMuon;

                // Kiểm tra nhập liệu cho phiếu mượn
                while (cin.fail() || luaChonPhieuMuon < 0 || luaChonPhieuMuon > 3) {
                    setColor(12);
                    cout << "Lua chon khong hop le. Vui long nhap lai!! ";
                    cin.clear(); // Xóa lỗi
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
                    setColor(11);
                    cout << "Nhap lua chon: ";
                    setColor(15);
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
                    setColor(14);
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