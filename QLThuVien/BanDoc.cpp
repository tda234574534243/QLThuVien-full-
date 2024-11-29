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
#include "Sach.cpp"
#include "PhieuMuon.cpp"
using namespace std;

void setColor3(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}


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
            setColor3(12);
            cout << "Khong the mo file BanDoc.txt\n";
            return;
        }

        BanDoc banDoc;
        setColor3(11);
        cout << "Nhap Ma Ban Doc (MSSV)(VD: 49.01.104.003): ";
        setColor3(15);
        cin >> banDoc._strMaBanDoc;

        // Kiểm tra mã bạn đọc đã tồn tại
        ifstream checkFile("BanDoc.txt");
        string strLine;
        while (getline(checkFile, strLine)) {
            if (strLine.find(banDoc._strMaBanDoc) != string::npos) {
                setColor3(14);
                cout << "Ma ban doc da ton tai. Khong the them.\n";
                checkFile.close();
                file.close();
                return;
            }
        }
        checkFile.close();

        setColor3(11);
        cout << "Nhap Ten Ban Doc: ";
        setColor3(15);
        cin.ignore();
        getline(cin, banDoc._strTenBanDoc);
        setColor3(11);
        cout << "Nhap Khoa (Khoa dao tao): ";
        setColor3(15);
        getline(cin, banDoc._strKhoa);

        do {
            setColor3(11);
            cout << "Nhap Ngay Sinh (dd mm yyyy): ";
            setColor3(15);

            cin >> banDoc._iNgaySinh >> banDoc._iThangSinh >> banDoc._iNamSinh;

            if (cin.fail()) {
                // Xử lý lỗi nhập liệu
                cin.clear(); // Xóa trạng thái lỗi của cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Loại bỏ dữ liệu còn lại trong bộ đệm
                setColor3(12);
                cout << "Ngay sinh khong hop le. Vui long nhap lai!\n";
                continue; // Quay lại đầu vòng lặp
            }

            if (!isValidDate(banDoc._iNgaySinh, banDoc._iThangSinh, banDoc._iNamSinh)) {
                setColor3(12);
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

        setColor3(10);
        cout << "Them ban doc thanh cong!\n";
        file.close();
    }


    void hienThiThongTin() {
        setColor3(10);
        cout << "Ma Ban Doc: "; setColor3(11); cout << _strMaBanDoc << endl;
        setColor3(10);
        cout << "Ten Ban Doc: "; setColor3(13); cout << _strTenBanDoc << endl;
        setColor3(10);
        cout << "Khoa: "; setColor3(15); cout << _strKhoa << endl;
        setColor3(10);
        cout << "Ngay Sinh: "; setColor3(15); cout << _iNgaySinh << "/" << _iThangSinh << "/" << _iNamSinh << endl;
        setColor3(10);
        cout << "Ngay Dang Ky: "; setColor3(9); cout << _strNgayDangKy << endl; // Hiển thị ngày đăng ký
        setColor3(14);
        cout << "----------------------------\n";
        setColor3(8);
    }

    void xoaBanDoc() {
        string strMaBanDocXoa;
        setColor3(11);
        cout << "Nhap Ma Ban Doc can xoa: ";
        setColor3(15);
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
                    setColor3(12);
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
                setColor3(12);
                cout << "Loi khi doi ten file\n";
            }
            else {
                setColor3(10);
                cout << "Xoa ban doc thanh cong!\n";
            }
        }
        else if (!bBanDocTonTai) {
            setColor3(14);
            cout << "Khong tim thay ma ban doc\n";
            remove("temp.txt"); // Xóa file tạm nếu không tìm thấy
        }
    }

    // Hàm kiểm tra xem bạn đọc có phiếu mượn nào không
    bool checkPhieuMuon(const string& _strMaBanDoc) {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor3(12);
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