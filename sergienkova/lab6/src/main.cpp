#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#define PATH "..."
using namespace std;
// 1
extern "C" {
    void AFunc(short* res, short* LGrInt, short* arr, short NInt, short NumRanDat);
}

int main() {
    srand(time(0));
    
    short* arr;                         // массив заданных чисел
    short NumRanDat = 0;                // длина массива
    
    short Xmin = 0;                     // диапазон
    short Xmax = 0;
    
    short* LGrInt;                      // массив левых границ
    short NInt = 0;                     // кол-во интеравалов
    short* res;                         // кол-во чисел в каждом интеравле

    ofstream out(PATH);                 // файл
    
    cout << "Len array: ";
    cin >> NumRanDat;
    while (NumRanDat > 16000 || NumRanDat < 0){
        cout << "Invalid len" << endl;;
        cin >> NumRanDat;
    }
    cout << endl;
    
    arr = new short[NumRanDat];
    //-------------------------------------------
    cout << "Count Intervals: ";
    cin >> NInt;
    while(NInt > 24 || NInt < 1){
        cout << "Invalid count" << endl;;
        cin >> NInt;
    }
    cout << endl;
    
    LGrInt = new short[NInt];
    //-------------------------------------------
    cout << "Xmin/Xmax" << endl;
    cout << "Xmin = ";
    cin >> Xmin;
    cout << "Xmax = ";
    cin >> Xmax;
    
    cout << endl;
    
    while(Xmax <= Xmin) {
        cout << "Invalid Xmin/Xmax" << endl;;
        cout << "Xmin = ";
        cin >> Xmin;
        
        cout << "Xmax = ";
        cin >> Xmax;
    }

    cout << endl;
    //-------------------------------------------
        
    // заполним остальные границы
    cout << "\nEnter the left bord: " << endl;
    cout << "1: " << Xmin << endl << endl;
    LGrInt[0] = Xmin;
    
    for(int i = 1; i < NInt; ++i){
        do{
            cout << i + 1 << ": ";
            cin >> LGrInt[i];
            cout << endl;
        } while(LGrInt[i] < Xmin || LGrInt[i] > Xmax);
    }
    
    // отсортировали массив границ
    for(int i = 0; i < NInt - 1; ++i){
        for (int j = 0; j < NInt - i - 1; ++j){
            if(LGrInt[j] < LGrInt[j + 1]) {
                short t = LGrInt[j];
                LGrInt[j] = LGrInt[j + 1];
                LGrInt[j + 1] = t;
            }
        }
    }
    //-------------------------------------------
    
    // равномерно распределим
    for(int i = 0; i < NumRanDat; ++i){
        for(int i = 0; i < NumRanDat; ++i)
            arr[i] = Xmin + rand() % (Xmax - Xmin);
    }
    // sort
    for(int i = 0; i < NumRanDat - 1; i++) {
        for(int j = 0; j < NumRanDat - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                short t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    
    
    res = new short[NInt];
    for(int i = 0; i < NInt; ++i){
        res[i] = 0;
    }
    
    AFunc(res, LGrInt, arr, NInt, NumRanDat);
    
    out << "Result:\n" << endl;
    out << "Left\t\tCount of digit" << endl;
    cout << "Result:\n" << endl;
    cout << "Left\t\tCount of digit" << endl;
    for(int i = 0; i < NInt; ++i){
        out << i + 1 << '\t' << LGrInt[i] << '\t' << "Count numbers in interval:  " << res[i] << endl;
        cout << i + 1 << '\t' << LGrInt[i] << '\t' << "Count numbers in interval:   " << res[i] << endl;
    }
    cout << endl;
    cout << "_______________________________" << endl;
    out << endl;
    out << "_______________________________" << endl;
    
    // сортируем рандомные числа
    for(int i = 0; i < NumRanDat - 1; ++i){
        for(int j = 0; j < NumRanDat - i - 1; ++j){
            if(arr[j] < arr[j + 1]){
                short t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    cout << endl;
    out << endl;
    cout << "Array random digit: " << endl;
    out << "Array random digit: " << endl;
    for(int i = 0; i < NumRanDat; ++i){
        cout << arr[i] << ' ';
        out << arr[i] << ' ';
    }
    
   
    out.close();
    delete[] LGrInt;
    delete[] res;
    delete[] arr;

    return 0;
}


