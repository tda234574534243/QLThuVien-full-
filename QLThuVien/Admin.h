#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>  // Cho hàm exit
#include <conio.h>  // Cho hàm _getch() ?? ??t m?t kh?u
#include <ctime>
#include <vector>
#include <limits> // Th? vi?n c?n thi?t ?? s? d?ng std::numeric_limits
#include <windows.h>

using namespace std;
void setColor(int color) {
    // L?y handle c?a console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // ??t màu cho console
    SetConsoleTextAttribute(hConsole, color);
}
class Admin {
private:
    string username;
    string password;

public:
    Admin(string user = "", string pass = "") : username(user), password(pass) {}

    bool verifyLogin(string inputUser, string inputPass) {
        return (inputUser == username && inputPass == password);
    }

    bool login() {
        ifstream adminFile("Admin.txt");
        if (!adminFile.is_open()) {
            setColor(4);
            cout << "Khong the mo file Admin.txt\n";
            return false;
        }

        string userInput, passInput;
        int attempts = 0;

        while (attempts < 3) {
            // Hi?n th? giao di?n ??ng nh?p
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
            cin >> userInput;
            setColor(9);
            cout << "Password: ";
            setColor(15);

            char ch;
            passInput = "";

            while (true) {
                ch = _getch();

                if (ch == 13) { // Enter key
                    break;
                }
                else if (ch == 8) { // Backspace key
                    if (!passInput.empty()) {
                        cout << "\b \b"; // Xóa ký t? trên màn hình
                        passInput.pop_back(); // Xóa ký t? cu?i cùng trong chu?i m?t kh?u
                    }
                }
                else if (ch == 224 || ch == -32) { // Phím ?i?u khi?n (arrow keys)
                    int nextCh = _getch(); // L?y ký t? ti?p theo
                }
                else if (ch >= 0 && ch <= 255 && isprint(ch)) {
                    bool isShiftHeld = (GetKeyState(VK_SHIFT) & 0x8000) != 0;

                    if (isShiftHeld && isalpha(ch)) {
                        ch = toupper(ch);
                    }
                    else if (isShiftHeld && isdigit(ch)) {
                        switch (ch) {
                        case '1': ch = '!'; break;
                        case '2': ch = '@'; break;
                        case '3': ch = '#'; break;
                        case '4': ch = '$'; break;
                        case '5': ch = '%'; break;
                        case '6': ch = '^'; break;
                        case '7': ch = '&'; break;
                        case '8': ch = '*'; break;
                        case '9': ch = '('; break;
                        case '0': ch = ')'; break;
                        }
                    }

                    passInput.push_back(ch);
                    cout << "*";
                }
            }

            cout << endl;

            string line;
            bool isLoginSuccessful = false;

            while (getline(adminFile, line)) {
                stringstream ss(line);
                string storedUser, storedPass;

                getline(ss, storedUser, '|');
                getline(ss, storedPass, '|');

                Admin admin(storedUser, storedPass);
                if (admin.verifyLogin(userInput, passInput)) {
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
                attempts++; // T?ng s? l?n th?

                setColor(4);
                cout << "Sai user hoac password. Vui long thu lai.\n";
                cout << "Ban da nhap sai " << attempts << " lan. Qua 3 lan se thoat chuong trinh.\n";

                // Ki?m tra n?u ?ã ?? 3 l?n sai thì không c?n g?i system("cls") n?a
                if (attempts < 3) {
                    // ??i m?t kho?ng th?i gian ng?n ?? ng??i dùng có th? ??c thông báo tr??c khi xóa màn hình
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
