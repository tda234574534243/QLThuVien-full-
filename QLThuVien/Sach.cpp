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
#include "Admin.cpp"
#include "PhieuMuon.cpp"
#include "BanDoc.cpp"
using namespace std;

// hàm tô màu
void setColor1(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}

class Sach {
public:
    string _strMaSach, _strTenSach, _strTacGia, _strNhaXuatBan, _strNgayNhapKho;
    int _iGiaBan, _iNamPhatHanh, _iSoTrang, _iTinhTrang;

    Sach() : _iGiaBan(0), _iNamPhatHanh(0), _iSoTrang(0), _iTinhTrang(0) {}

    void hienThiThongTin() {
        // Đặt màu sắc cho các tiêu đề
        setColor1(10); // Màu xanh lá cây cho tiêu đề
        cout << "Ma Sach: ";
        setColor1(15); // Màu trắng cho giá trị
        cout << _strMaSach << endl;

        setColor1(10);
        cout << "Ten Sach: ";
        setColor1(11);
        cout << _strTenSach << endl;

        setColor1(10);
        cout << "Tac Gia: ";
        setColor1(13);
        cout << _strTacGia << endl;

        setColor1(10);
        cout << "Nha Xuat Ban: ";
        setColor1(15);
        cout << _strNhaXuatBan << endl;

        setColor1(10);
        cout << "Gia Ban: ";
        setColor1(15);
        cout << _iGiaBan; setColor1(14); cout << " dong" << endl;

        setColor1(10);
        cout << "Nam Phat Hanh: ";
        setColor1(15);
        cout << _iNamPhatHanh << endl;

        setColor1(10);
        cout << "So Trang: ";
        setColor1(15);
        cout << _iSoTrang; setColor1(14); cout << " trang" << endl;

        setColor1(10);
        cout << "Ngay Nhap Kho: ";
        setColor1(15);
        cout << _strNgayNhapKho << endl;

        setColor1(10);
        cout << "Tinh Trang: ";
        setColor1(15);
        cout << (_iTinhTrang == 0 ? "Chua muon" : "Dang duoc muon") << endl;

        // Đặt lại màu sắc cho ngắt dòng
        setColor1(6); // Màu vàng cho ngắt dòng
        cout << "----------------------------\n";
        setColor1(7); // Đặt lại màu sắc về mặc định nếu cần
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
            setColor1(14);
            cout << "Khong the mo file Sach.txt\n";
            return;
        }

        Sach SachThem;
        setColor1(11);
        cout << "Nhap Ma Sach(Vd: B001, B002,...): ";
        setColor1(15);
        cin >> SachThem._strMaSach;

        // Kiểm tra mã sách đã tồn tại
        ifstream checkFile("Sach.txt");
        string strLine;
        while (getline(checkFile, strLine)) {
            if (strLine.find(SachThem._strMaSach) != string::npos) {
                setColor1(14);
                cout << "Ma sach da ton tai. Khong the them.\n";
                checkFile.close();
                file.close();
                return;
            }
        }
        checkFile.close();

        // Nhập và kiểm tra dữ liệu
        setColor1(11);
        cout << "Nhap Ten Sach: ";
        setColor1(15);
        cin.ignore();
        getline(cin, SachThem._strTenSach);

        setColor1(11);
        cout << "Nhap Tac Gia: ";
        setColor1(15);
        getline(cin, SachThem._strTacGia);

        setColor1(11);
        cout << "Nhap Nha Xuat Ban: ";
        setColor1(15);
        getline(cin, SachThem._strNhaXuatBan);

        while (true) {
            setColor1(11);
            cout << "Nhap Gia Ban: ";
            setColor1(15);
            cin >> SachThem._iGiaBan;

            if (cin.fail() || SachThem._iGiaBan <= 0) {
                setColor1(12);
                cout << "Gia ban khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor1(11);
            cout << "Nhap Nam Phat Hanh (1900 - hien tai): ";
            setColor1(15);
            cin >> SachThem._iNamPhatHanh;

            if (cin.fail() || SachThem._iNamPhatHanh < 1900 || SachThem._iNamPhatHanh > 2024) {
                setColor1(12);
                cout << "Nam phat hanh khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor1(11);
            cout << "Nhap So Trang (so trang phai nhap it nhat la 1): ";
            setColor1(15);
            cin >> SachThem._iSoTrang;

            if (cin.fail() || SachThem._iSoTrang <= 0) {
                setColor1(12);
                cout << "So trang khong hop le. Vui long nhap lai!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            setColor1(11);
            cout << "Nhap Ngay Nhap Kho (yyyy-mm-dd): ";
            setColor1(15);
            cin >> SachThem._strNgayNhapKho;

            // Kiểm tra ngày hợp lệ
            if (!kiemTraNgayHopLe(SachThem._strNgayNhapKho)) {
                setColor1(12);
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

        setColor1(10);
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
        setColor1(11);
        cout << "Nhap Ma Sach can xoa: ";
        setColor1(15);
        cin >> strMaSachXoa;

        ifstream file("Sach.txt");
        ofstream tempFile("temp.txt");
        bool bSachTonTai = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor1(12);
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
                    setColor1(12);
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
                setColor1(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor1(10);
                cout << "Xoa sach thanh cong!\n";
            }
        }
        else {
            setColor1(12);
            cout << "Khong tim thay ma sach hoac sach dang duoc muon\n";
            remove("temp.txt");
        }
    }
};