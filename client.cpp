#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const string requestFile = "C:/Users/s0177102/source/repos/file/REQUEST.txt";

    while (true) {
        string name;
        int coffeeParams[3];

        cout << "Введите имя клиента: ";
        cin >> name;
        cout << "Введите параметры кофе [сахар(0-5) молоко(0-3) объем(1-3)]: ";
        for (int i = 0; i < 3; i++)
            cin >> coffeeParams[i];

        // Создаём файл клиента
        string path = "C:/Users/s0177102/source/repos/file/" + name + ".txt";
        ofstream fout(path);
        for (int i = 0; i < 3; i++)
            fout << coffeeParams[i] << " ";
        fout.close();

        // Добавляем имя в общий файл запросов
        ofstream foutReq(requestFile, ios::app);
        foutReq << name << endl;
        foutReq.close();

        cout << "Заказ отправлен бариста. Ожидание приготовления..." << endl;

        // Ожидаем, пока сервер запишет "Ответ:"
        string line;
        bool answered = false;
        while (!answered) {
            Sleep(500);
            ifstream fin(path);
            while (getline(fin, line)) {
                if (line.find("Ответ:") != string::npos) {
                    cout << line << endl;
                    answered = true;
                    break;
                }
            }
            fin.close();
        }

        cout << "----------------------------------\n";
    }

    return 0;
}
