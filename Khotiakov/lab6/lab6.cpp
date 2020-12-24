#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

extern "C" {
    void module_1(int* mass, int NumRatDat, int* mass_after_module1, int Xmin);
    void module_2(int* mass_after_module1, int NumRatDat, int* mass_after_module2, int Xmin, int* LGrInt, int Nint);
}



int main() {
    setlocale(0, "Russian");
    int NumRatDat;//количество чисел для генерации
    int Xmin, Xmax;
    int Nint;//количество границ интервала
    int* LGrInt;//массив левых границ интервала
    int* mass; //массив сгенерированных чисел
    int* mass_after_module1; //массив количества каждого сгенерированного числа
    int* mass_after_module2; //массив количества сгенерированных чисел в заданных интервалов
    int* LGrInt2;

    ofstream out("./out.txt");
    if (!out.is_open()) {
        cout << "Файл не удалось открыть\n";
        exit(1);
    }
    //Ввод исходных данных:
    cin >> NumRatDat;
    cin >> Xmin >> Xmax;
    cin >> Nint;
    LGrInt = new int[Nint];
    LGrInt2 = new int[Nint];
    for (int i = 0; i < Nint; i++) {
        cin >> LGrInt[i];
        LGrInt2[i] = LGrInt[i];
    }

    mass = new int[NumRatDat];
    cout << "Сгенерированные числа:\n";
    //генерация псевдослучайных чисел
    for (int i = 0; i < NumRatDat; i++) {
        mass[i] = Xmin + rand() % (Xmax - Xmin + 1);
        cout << mass[i] << ' ';
    }
    cout << '\n';

    int length_1 = abs(Xmax - Xmin) + 1;//длинная массива mass_after_module1

    mass_after_module1 = new int[length_1];
    for (int i = 0; i < length_1; i++) {
        mass_after_module1[i] = 0;
    }
    module_1(mass, NumRatDat, mass_after_module1, Xmin);

    cout << "Распределение после работы первого модуля: \n";
    out << "Распределение после работы первого модуля: \n";
    for (int i = 0; i < length_1; i++) {
        cout << "Инт№" << i + 1 << "\tЛевая граница:" << i + 1 << "\tКоличество чисел:" << mass_after_module1[i] << '\n';
        out << "Инт№" << i + 1 << "\tЛевая граница:" << i + 1 << "\tКоличество чисел:" << mass_after_module1[i] << '\n';
    }

    mass_after_module2 = new int[Nint + 1];
    for (int i = 0; i < Nint + 1; i++) {
        mass_after_module2[i] = 0;
    }
    module_2(mass_after_module1, NumRatDat, mass_after_module2, Xmin, LGrInt, Nint);

    cout << "Распределение после работы первого модуля: \n";
    out << "Распределение после работы первого модуля: \n";
    if (LGrInt2[0] != Xmin) {
        cout << "Инт№" << 0 << "\tЛевая граница:" << Xmin << "\tКоличество чисел:" << mass_after_module2[0] << '\n';
        out << "Инт№" << 0 << "\tЛевая граница:" << Xmin << "\tКоличество чисел:" << mass_after_module2[0] << '\n';

    }
    for (int i = 1; i < Nint + 1; i++) {
        cout << "Инт№" << i << "\tЛевая граница:" << LGrInt2[i - 1] << "\tКоличество чисел:" << mass_after_module2[i] << '\n';
        out << "Инт№" << i << "\tЛевая граница:" << LGrInt2[i - 1] << "\tКоличество чисел:" << mass_after_module2[i] << '\n';
    }
    return 0;
}