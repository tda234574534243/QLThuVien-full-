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
#include "BanDoc.cpp"
using namespace std;

void setColor2(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}

class PhieuMuon {
public:
    int _iSoPhieuMuon;
    string _strMaBanDoc, _strMaSach, _strNgayMuon, _strNgayPhaiTra;
    int _iTinhTrang;

    PhieuMuon() : _iSoPhieuMuon(0), _iTinhTrang(0) {}

    void hienThiThongTin() {
        setColor2(10);
        cout << "So Phieu Muon: "; setColor2(14); cout << _iSoPhieuMuon << endl;
        setColor2(10);
        cout << "Ma Ban Doc: "; setColor2(13); cout << _strMaBanDoc << endl;
        setColor2(10);
        cout << "Ma Sach: "; setColor2(11); cout << _strMaSach << endl;
        setColor2(10);
        cout << "Ngay Muon: "; setColor2(9);cout << _strNgayMuon << endl;
        setColor2(10);
        cout << "Ngay Phai Tra: "; setColor2(9);cout << _strNgayPhaiTra << endl;
        setColor2(10);
        cout << "Tinh Trang: "; setColor2(15); cout << (_iTinhTrang == 1 ? "Dang muon" : "Da tra") << endl;
        setColor2(14);
        cout << "----------------------------\n";
        setColor2(8);
    }

    void muonSach() {
        ofstream file("PhieuMuon.txt", ios::app);
        if (!file.is_open()) {
            setColor2(12);
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
        setColor2(11);
        cout << "So Phieu Muon: "; setColor2(15); cout << Phieu._iSoPhieuMuon << endl; // Hiển thị số phiếu mượn mới
        setColor2(11);
        cout << "Nhap Ma Ban Doc: ";
        setColor2(15);
        cin >> Phieu._strMaBanDoc;
        setColor2(11);
        cout << "Nhap Ma Sach: ";
        setColor2(15);
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
                    setColor2(11);
                    cout << "Nhap Ngay Phai Tra (yyyy-mm-dd) hoac nhan Enter de mac dinh tra sau 7 ngay: ";
                    string ngayTraInput;
                    setColor2(15);
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
                    setColor2(10);
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
                        setColor2(12);
                        cout << "Khong the doi ten file Sach.txt\n";
                    }

                    file.close(); // Đóng file sau khi ghi
                    return; // Ngưng vòng lặp khi đã tìm thấy sách
                }
                else {
                    setColor2(14);
                    cout << "Sach da co ai do muon roi. Vui long cho nhe!\n";
                    bBachDaDuocMuon = true; // Sách đã được mượn
                    break; // Ngưng vòng lặp khi đã tìm thấy sách
                }
            }
        }

        sachFile.close();

        if (bSachTonTai && !bBachDaDuocMuon) {
            setColor2(14);
            cout << "Sach da duoc muon!\n";
        }
        else if (!bSachTonTai) {
            setColor2(12);
            cout << "Khong tim thay sach!\n";
        }

        file.close();
    }

    void hienThiTatCaPhieuMuon() {
        ifstream file("PhieuMuon.txt");
        if (!file.is_open()) {
            setColor2(12);
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
        setColor2(11);
        cout << "Nhap So Phieu Muon can tra: ";
        setColor2(15);
        cin >> soPhieuTra;

        ifstream file("PhieuMuon.txt");
        ofstream tempFile("temp.txt");
        bool timThayPhieu = false;

        if (!file.is_open() || !tempFile.is_open()) {
            setColor2(12);
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
                    setColor2(12);
                    cout << "Khong the doi ten file Sach.txt\n";
                }
                setColor2(10);
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
                setColor2(12);
                cout << "Khong the doi ten file PhieuMuon.txt\n";
            }
        }
        else {
            setColor2(14);
            cout << "Khong tim thay so Phieu muon\n";
            remove("temp.txt");
        }
    }
};
