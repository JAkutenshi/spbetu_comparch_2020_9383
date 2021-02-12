#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

extern "C" void func(int NumRanDat, int* arr, int* LGrInt, int* ans, int NInt);


void printArr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

void writeNumRanDat(int& NumRanDat)
{
    bool exit = false;
    cout << "Введите размер массива (меньше 16384):\n";
    while (exit != true)
    {
        cin >> NumRanDat;
        if (NumRanDat < 16 * 1024 and NumRanDat > 0)
        {
            exit = true;
        }
        else
        {
            cout << "Введенное значение больше 16384 или меньше 0! Введите еще раз!\n";
        }
    }
}

void writeRangesAmount(int& NInt, const int Xmin, const int Xmax)
{
    bool exit = false;
    int amount = Xmax - Xmin > 24 ? 24 : Xmax - Xmin + 1;
    cout << "Введите не более " << "24" << " интервалов:\n";
    while (exit != true)
    {
        cin >> NInt;
        if (NInt > 24 || NInt <= 0)
        {
            cout << "Введенное количество интервалов неверно! Введите еще раз\n";
        }
        else
        {
            exit = true;
        }
    }
}

void writeRangesBorders(const int NInt, const int Xmin, const int Xmax, int* LGrInt)
{
    int i = 1;
    cout << "Введите " << NInt - 1 << " нижних границ\n";
    while (i < NInt)
    {
        cin >> LGrInt[i];
        if (LGrInt[i] > Xmax or LGrInt[i] < Xmin)
        {
            cout << "Введенный нижний предел не попадает в интервал" << "[" << Xmin << "," << Xmax << "]" << "\n";
            cout << "Введите значение еще раз:\n";
        }
        else if (i > 0 and LGrInt[i] < LGrInt[i - 1])
        {
            cout << "Нижняя граница " << LGrInt[i - 1] << " больше, чем предыдущая - " << LGrInt[i] << '\n';
            cout << "Введите значение заново:\n";
        }
        else
        {
            i++;
        }
    }
    LGrInt[NInt] = Xmax;
    LGrInt[0] = Xmin;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int NumRanDat = 0, Xmin = 0, Xmax = 0, NInt = 0;
    writeNumRanDat(NumRanDat);
    cout << "Xmin:\n";
    cin >> Xmin;
    cout << "Xmax:\n";
    cin >> Xmax;
    writeRangesAmount(NInt, Xmin, Xmax);
    int* LGrInt;
    LGrInt = new int[NInt + 1];
    writeRangesBorders(NInt, Xmin, Xmax, LGrInt);
    int* arr = new int[NumRanDat];
    srand((time(0)));
    for (int i = 0; i < NumRanDat; i++)
    {
        arr[i] = Xmin + rand() % (Xmax - Xmin + 1);
    }
    int* ans = new int[NInt];
    for (int i = 0; i < NInt; i++)
    {
        ans[i] = 0;
    }
    ofstream file("output.txt");
    cout << "Случайные числа:\n";
    file << "Случайные числа:\n";
    for (int i = 0; i < NumRanDat; i++)
    {
        cout << arr[i] << " ";
        file << arr[i] << " ";
    }
    func(NumRanDat, arr, LGrInt, ans, NInt);
    cout << '\n';
    file << '\n';
    for (int i = 0; i < NInt; ++i)
    {
        cout << i << "   |  " << "[" << LGrInt[i] << "," << LGrInt[i + 1] << "]" << "  |  " << ans[i] << '\n';
        file << i << "   |  " << "[" << LGrInt[i] << "," << LGrInt[i + 1] << "]" << "  |  " << ans[i] << '\n';
    }
    
}