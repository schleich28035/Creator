#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    if (argc != 4) {
        cerr << "Usage: Reporter <bin_file> <report_file> <rate>\n";
        return 1;
    }

    string binFile = argv[1];
    string reportFile = argv[2];
    double rate = atof(argv[3]);

    ifstream fin(binFile, ios::binary);
    if (!fin) {
        cerr << "Cannot open binary file.\n";
        return 1;
    }

    ofstream fout(reportFile);
    if (!fout) {
        cerr << "Cannot open report file.\n";
        return 1;
    }

    fout << "Отчет по файлу \"" << binFile << "\"\n";
    fout << "---------------------------------------------------\n";
    fout << left << setw(10) << "Номер"
        << setw(15) << "Имя"
        << setw(10) << "Часы"
        << setw(10) << "Зарплата\n";
    fout << "---------------------------------------------------\n";

    employee emp;
    while (fin.read((char*)&emp, sizeof(employee))) {
        double salary = emp.hours * rate;
        fout << left << setw(10) << emp.num
            << setw(15) << emp.name
            << setw(10) << emp.hours
            << setw(10) << salary << '\n';
    }

    cout << "Отчет \"" << reportFile << "\" успешно создан.\n";
    fin.close();
    fout.close();
    return 0;
}