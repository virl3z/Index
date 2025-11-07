#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

struct CoffeeOrder {
    string name;
    int coffeeParams[4];
};

// Определяем тип кофе и результат
int evaluate(const CoffeeOrder& order) {
    int strength = order.coffeeParams[0];
    int sugar = order.coffeeParams[1];
    int milk = order.coffeeParams[2];
    int volume = order.coffeeParams[3];

    bool hasSugar = (sugar > 0);
    bool hasMilk = (milk > 0);
    
    // Определяем тип кофе на основе параметров
    if (strength >= 4 && milk == 0) return 0;      // эспрессо
    if (strength >= 3 && milk == 1) return 1;      // американо
    if (strength <= 2 && milk >= 2) return 2;      // капучино
    if (strength <= 1 && milk >= 3) return 3;      // латте
    
    return 1; // по умолчанию американо
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Кофейня открыта. Ожидание заказов...\n";

    const string requestFile = "C:/Users/s0177102/source/repos/file/REQUEST.txt";

    string lastProcessed; // чтобы знать, какой заказ уже обработан

    while (true) {
        Sleep(500);

        ifstream fin(requestFile);
        if (!fin.is_open()) continue;

        string currentName;
        string lastName = "";
        while (fin >> currentName) { // читаем последнюю строку
            lastName = currentName;
        }
        fin.close();

        // Проверяем, появился ли новый заказ
        if (lastName.empty() || lastName == lastProcessed)
            continue;

        lastProcessed = lastName;

        // Открываем файл клиента (например, Ivan.txt)
        string path = "C:/Users/s0177102/source/repos/file/" + lastName + ".txt";
        ifstream fperson(path);
        if (!fperson.is_open()) continue;

        CoffeeOrder order;
        order.name = lastName;
        for (int i = 0; i < 4; i++) fperson >> order.coffeeParams[i];
        fperson.close();

        int coffeeType = evaluate(order);
        int sugar = order.coffeeParams[1];
        int milk = order.coffeeParams[2];

        cout << "Приготовлен заказ для " << order.name << " → тип кофе " << coffeeType << endl;

        // Записываем ответ в конец файла клиента
        ofstream fout(path, ios::app);
        fout << "\nОтвет: ";
        switch (coffeeType) {
        case 0: 
            fout << "Эспрессо"; 
            if (sugar > 0) fout << " с " << sugar << " порц. сахара";
            break;
        case 1: 
            fout << "Американо";
            if (sugar > 0) fout << " с " << sugar << " порц. сахара";
            if (milk > 0) fout << " и " << milk << " порц. молока";
            break;
        case 2: 
            fout << "Капучино с " << milk << " порц. молока";
            if (sugar > 0) fout << " и " << sugar << " порц. сахара";
            break;
        case 3: 
            fout << "Латте с " << milk << " порц. молока";
            if (sugar > 0) fout << " и " << sugar << " порц. сахара";
            break;
        }
        fout << ". Приятного аппетита!";
        fout.close();
    }

    return 0;
}
