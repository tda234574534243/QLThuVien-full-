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
#include "Sach.cpp"
#include "PhieuMuon.cpp"
#include "BanDoc.cpp"
using namespace std;

void setColor(int color) {
    // Lấy handle của console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Đặt màu cho console
    SetConsoleTextAttribute(hConsole, color);
}

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