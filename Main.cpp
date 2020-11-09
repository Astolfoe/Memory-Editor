#include <iostream>
#include <windows.h>
#include <string>

int main() {

    SetConsoleTitleA("Memory Writer");

    std::wstring aa;
    std::cout << "Enter a process name: ";
    std::wcin >> aa;

    HWND hwnd = FindWindow(0, aa.c_str());

    if (hwnd == 0)
    {
        std::cout << "The process has not been found... please open it before opening the tool next time...\n";
        system("Pause");
    }
    else
    {
    again:
        DWORD process_ID;
        GetWindowThreadProcessId(hwnd, &process_ID);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_ID);
        int a;
        std::cout << "Type 1 to enter: ";
        std::cin >> a;
        if (a > 1)
        {
            std::cout << "There is no option higher than 1...\n";
            system("Pause");
        }
        if (a == 1) {
            uintptr_t address;
            std::cout << "Enter your address: ";
            std::cin >> std::hex >> address;
            std::cout << "\n";
            int b;
            std::cout << "What do you want to set this address value as: ";
            std::cin >> b;
            DWORD sizeh = sizeof(b);
            if (WriteProcessMemory(hProcess, (LPVOID)address, &b, sizeh, NULL)) {
                std::cout << "Address has been written successfully.\n";
                system("Pause");
            }
            else {
                system("cls");
                std::cout << "Address was unavailable\n";
                std::cout << "Last Error > \"" << GetLastError() << "\" \n";
                std::cout << std::hex << "Window Address > \"" << hProcess << "\" \n";
                std::cout << std::hex << b << '\n';
                system("Pause");
            }
        }
        system("cls");
        goto again;
    }
}
