#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main() {
    setlocale(LC_ALL, "rus");
    string binFile, reportFile;
    int count;
    double rate;

    cout << "Введите имя бинарного файла: ";
    cin >> binFile;
    cout << "Введите количество записей: ";
    cin >> count;

    
    string creatorCmd = "Creator.exe " + binFile + " " + to_string(count);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;  

    
    if (!CreateProcessA(nullptr, creatorCmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        cerr << "Ошибка запуска Creator.\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    
    cout << "\nСодержимое бинарного файла:\n";
    ifstream fin(binFile, ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть бинарный файл.\n";
        return 1;
    }

    employee emp;
    while (fin.read((char*)&emp, sizeof(employee))) {
        cout << emp.num << " " << emp.name << " " << emp.hours << endl;
    }
    fin.close();

    
    cout << "\nВведите имя файла отчета: ";
    cin >> reportFile;
    cout << "Введите оплату за час работы: ";
    cin >> rate;

    
    string reporterCmd = "Reporter.exe " + binFile + " " + reportFile + " " + to_string(rate);

    
    if (!CreateProcessA(nullptr, reporterCmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        cerr << "Ошибка запуска Reporter.\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    
    cout << "\nСодержимое отчета:\n";
    ifstream rep(reportFile);
    if (!rep) {
        cerr << "Не удалось открыть файл отчета.\n";
        return 1;
    }

    string line;
    while (getline(rep, line)) {
        cout << line << endl;
    }

    rep.close();
    cout << "\nРабота завершена.\n";
    return 0;
}