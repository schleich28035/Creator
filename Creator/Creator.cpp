#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    if (argc != 3) {
        cerr << "Usage: Creator <filename> <count>\n";
        return 1;
    }

    string filename = argv[1];
    int count = atoi(argv[2]);

    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Cannot open file for writing.\n";
        return 1;
    }

    employee emp;
    for (int i = 0; i < count; ++i) {
        cout << "Введите данные для сотрудника #" << i + 1 << endl;
        cout << "Номер: ";
        cin >> emp.num;
        cout << "Имя (до 9 символов): ";
        cin >> emp.name;
        cout << "Часы: ";
        cin >> emp.hours;

        fout.write((char*)&emp, sizeof(employee));
    }

    fout.close();
    cout << "Файл \"" << filename << "\" успешно создан.\n";
    return 0;
}