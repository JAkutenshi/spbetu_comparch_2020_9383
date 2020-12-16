#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <clocale>

#define PATH "/Users/ramka178rus/Desktop/Any_Poject_XC/asm_lab6/asm_lab6/output.txt"
#define PATH_VS "output.txt"
using namespace std;

extern "C" {
    void ASSEMBLY_ARR(unsigned short* result, short* arrLeftInt, short* array, unsigned short countInterval, unsigned short sizeArray);
}


int main() {
    srand(time(0));

    
    unsigned short sizeArray = 0;                  // длина массива
    short xmin = 0;                                // диапазон
    short xmax = 0;
    short* array;                                  // массив заданных чисел
    unsigned short countInterval = 0;              // кол-во интеравалов
    short* arrLeftInt;                             // массив левых границ
    unsigned short* result;                        // кол-во чисел в каждом интеравле

    std::ofstream out("output.txt");
    
#pragma region INPUT
    cout << "Enter size array: ";
    cin >> sizeArray;
    while (sizeArray > 16000 || sizeArray < 0){
        cout << "Error size, try again\n";
        cin >> sizeArray;
    }
    cout << endl;
    
    cout << "Enter number boundaries" << endl;
    cout << "xmin = ";
    cin >> xmin;
    
    cout << "xmax = ";
    cin >> xmax;
    
    cout << endl;
    
    while(xmax <= xmin) {
        cout << "Error xmin/xmax, try again\n";
        cout << "xmin = ";
        cin >> xmin;
        
        cout << "xmax = ";
        cin >> xmax;
    }

    cout << endl;
    
    cout << "Enter the number of intervals: ";
    cin >> countInterval;
    while(countInterval > 24 || countInterval < 0){
        cout << "Error countInterval, try again\n";
        cin >> countInterval;
    }


    cout << endl;
#pragma endregion
    
    array = new short[sizeArray];
    arrLeftInt = new short[countInterval];
    
    for (int i = 0; i < countInterval; i++)
    {
        std::cout << i + 1 << ":";
        std::cin >> arrLeftInt[i];
        std::cout << '\n';
    }


    /*for(int i = 1; i < countInterval - 1; ++i){
        do{
            cout << i + 1 << ": ";
            cin >> arrLeftInt[i];
            cout << endl;
        } while(arrLeftInt[i] < xmin || arrLeftInt[i] > xmax);
    }*/
    // отсортировали массив границ
    for(int i = 0; i < countInterval - 1; ++i){
        for (int j = 0; j < countInterval - i - 1; ++j){
            if(arrLeftInt[j] < arrLeftInt[j + 1]) {
                short temp = arrLeftInt[j];
                arrLeftInt[j] = arrLeftInt[j + 1];
                arrLeftInt[j + 1] = temp;
            }
        }
    }
    
    
    // равномерно распределим
    for(int i = 0; i < sizeArray; ++i){
        array[i] = xmin + rand() % (xmax - xmin);
    }

    
    
    
    result = new unsigned short[countInterval];
    for(int i = 0; i < countInterval; ++i){
        result[i] = 0;
    }
    
    ASSEMBLY_ARR(result, arrLeftInt, array, countInterval, sizeArray);
    
    out << "Result:\n" << endl;
    out << "Left border\tNumber of numbers" << endl;
    cout << "Result:\n" << endl;
    cout << "Left border\t\tNumber of numbers" << endl;

    for (int i = 0; i < countInterval; i++)
    {
        cout << i + 1 << ' ' << arrLeftInt[i] << '\t' << " Count numbers in interval: " << result[i] << '\n';
        out << i + 1 << "\t" << arrLeftInt[i] << "; Count numbers in interval: " << result[i] << '\n';
    }

    /*for(int i = 0; i < countInterval; ++i){
        out << i + 1 << ' ' << arrLeftInt[i] << ' ' << result[i] << endl;
        cout << i + 1 << ' ' << arrLeftInt[i] << ' ' << result[i] << endl;
    }
    */
    cout << endl;
    cout << "_______________________________" << endl;
    
    
    cout << "CHECK _________" << endl << endl;

    for (int i = 0; i < sizeArray - 1; ++i) {
        for (int j = 0; j < sizeArray - i - 1; ++j) {
            if (array[j] < array[j + 1]) {
                short temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }


    for(int i = 0; i < sizeArray; ++i){
        cout << array[i] << ' ';
        out << array[i] << ' ';
    }
    
    /*cout << "массив до сортирвоки" << endl;
    for(int i = 0; i < countInterval; ++i){
        cout << arrLeftInt[i] << ' ';
    }
     
    cout << endl;
    cout << "массив после сортировки" << endl;
    // сортировка
    int temp;
    for(int i = 0; i < countInterval - 1; i++) {
        for(int j = i + 1; j < countInterval; j++) {
            if (arrLeftInt[i] < arrLeftInt[j]) {
                temp = arrLeftInt[i];
                arrLeftInt[i] = arrLeftInt[j];
                arrLeftInt[j] = temp;
            }
        }
    }
     
    for(int i = 0; i < countInterval; ++i){
        cout << arrLeftInt[i] << ' ';
    }
    */
    
    
    delete[] array;
    delete[] arrLeftInt;
    delete[] result;
    out.close();
    return 0;
}
