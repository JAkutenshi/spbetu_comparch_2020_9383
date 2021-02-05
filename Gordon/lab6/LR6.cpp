#include <iostream>
#include <fstream>

using namespace std;

extern "C" void func(int NumRanDat, int* arr, int* LGrInt, int* ans);

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

void writeRangesAmount(int& NInt, const int arr_size)
{
    bool exit = false;
    int amount = arr_size - 1 > 24 ? 24 : arr_size - 1;
    cout << "Введите не более " << amount << " интервалов:\n";
    while (exit != true)
    {
        cin >> NInt;
        if (NInt > amount)
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
    int i = 0;
    cout << "Введите нижние пределы для " << NInt - 1 << " интервалов\n";
    while (i < NInt - 1)
    {
        cin >> LGrInt[i];
        if (LGrInt[i] > Xmax or LGrInt[i] < Xmin)
        {
            cout << "Введенный нижний предел не попадает в интервал" << "[" << Xmin << "," << Xmax << "]" <<"\n";
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
    LGrInt[NInt - 1] = Xmax;
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
    writeRangesAmount(NInt, NumRanDat);
    int* LGrInt = new int[NInt];
    writeRangesBorders(NInt, Xmin, Xmax, LGrInt);
    int* arr = new int[NumRanDat];
    for (int i = 0; i < NumRanDat; i++) 
    {
        arr[i] = Xmin + rand() % (Xmax - Xmin);
    }
    int* ans = new int[NInt];
    for (int i = 0; i < NInt; i++)
    {
        ans[i] = 0;
    }
    func(NumRanDat, arr, LGrInt, ans);
    ofstream file("output.txt");
    cout << "Случайные числа:\n" ;
    file << "Случайные числа:\n";
    for (int i = 0; i < NumRanDat; i++) 
    {
        cout << arr[i] << " ";
        file << arr[i] << " ";
    }
    cout << '\n';
    file << '\n';
    cout << "номер|интервал  |количество\n";
    file << "номер|интервал  |количество\n";
    for (int i = 0; i < NInt; i++) 
    {
        int n1, n2;
        n1 = i != 0 ? LGrInt[i - 1] : Xmin;
        n2 = i != NInt ? LGrInt[i] : Xmax;
        file << i + 1 << "    |  " << "[" << n1 << ", " << n2 << "]" << "  |  " << ans[i] << "\n";
        cout << i + 1 << "    |  " << "[" << n1 << ", " << n2 << "]" << "  |   " << ans[i] << "\n";
    }
}