#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

extern "C" {
    void distribution(int arr_length, int* arr, int* lower_ranges_arr, int* range_arr);
}

int main() {
    setlocale(0, "RU");
    int arr_length = 0, x_min = 0, x_max = 0, range_count = 0;
    cout << "Введите длину массива (длина массива не должна превышать 2^14): ";
    cin >> arr_length;
    if (arr_length > 16 * 1024 || arr_length < 0) {
        cout << "Неверно введена длина массива. Выход из программы." << endl;
        exit(1);
    }
    if (arr_length == 0) {
        cout << "Длина массива равна 0. Выход из программы." << endl;
        exit(1);
    }
    cout << "Нижний предел: ";
    cin >> x_min;
    cout << "Верхний предел: ";
    cin >> x_max;
    if (x_min > x_max) {
        cout << "Верхний предел меньше нижнего. Выход из программы." << endl;
        exit(1);
    }
    cout << "Количество диапазонов (должно быть <= 24): ";
    cin >> range_count;
    if (range_count > 24 || range_count < 1 || range_count > x_max - x_min + 1) {
        cout << "Неверно введено количество диапазонов. Выход из программы." << endl;
        exit(1);
    }
    int* lower_ranges_arr = new int[range_count];
    cout << "Введите нижние пределы диапазонов в количестве " << range_count - 1 << ": " << endl;
    for (int i = 0; i < range_count - 1; i++) {
        cin >> lower_ranges_arr[i];
        if (lower_ranges_arr[i] < lower_ranges_arr[i - 1]) {
            cout << "Введенный предел " << lower_ranges_arr[i] << " больше предыдущего." << endl;
            cin >> lower_ranges_arr[i];
        }
        if (lower_ranges_arr[i] < x_min || lower_ranges_arr[i] > x_max) {
            cout << "Неверно задан нижний предел. Выход из программы." << endl;
            exit(1);
        }
    }
    lower_ranges_arr[range_count - 1] = x_max;
    int* arr = new int[arr_length]();
    for (int i = 0; i < arr_length; i++)
        arr[i] = x_min + rand() % (x_max - x_min);
    int* range_arr = new int[range_count];
    for (int i = 0; i < range_count; i++)
        range_arr[i] = 0;
    distribution(arr_length, arr, lower_ranges_arr, range_arr);
    ofstream output("output.txt");
    cout << "Сгенерированные псевдослучайные числа:" << endl;
    output << "Сгенерированные псевдослучайные числа:" << endl;
    for (int i = 0; i < arr_length; i++) {
        cout << arr[i] << " ";
        output << arr[i] << " ";
    }
    cout << endl;
    output << endl;
    cout << "Число|Диапазон|Содержит количество чисел" << endl;
    output << "Число|Диапазон|Содержит количество чисел" << endl;
    cout << "________________________________________" << endl;
    output << "________________________________________" << endl;
    for (int i = 0; i < range_count; i++) {
        int count1, count2;
        if (i != 0)
            count1 = lower_ranges_arr[i - 1];
        else
            count1 = x_min;
        if (i != range_count)
            count2 = lower_ranges_arr[i];
        else
            count2 = x_max;
        output << i + 1 << "    |  " << count1 << ", " << count2 << "  |  " << range_arr[i] << endl;
        cout << i + 1 << "    |  " << count1 << ", " << count2 << "  |  " << range_arr[i] << endl;
    }
    delete[] lower_ranges_arr;
    delete[] arr;
    delete[] range_arr;
    return 0;
}
