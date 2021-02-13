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
    //LGrInt[0] = Xmin;
    int i = 0;
    cout << "Введите " << NInt - 1 << " нижних границ\n";
    while (i < NInt - 1)
    {
        cin >> LGrInt[i];
        if (LGrInt[i] > Xmax or LGrInt[i] < Xmin)
        {
            cout << "Введенный нижний предел не попадает в интервал" << "[" << Xmin << "," << Xmax << "]" << "\n";
            cout << "Введите значение еще раз:\n";
        }
        else if (i > 0 and LGrInt[i] <= LGrInt[i - 1])
        {
            cout << "Нижняя граница " << LGrInt[i - 1] << " больше или равна предыдущей - " << LGrInt[i] << '\n';
            cout << "Введите значение заново:\n";
        }
        else
        {
            i++;
        }
    }
    //LGrInt[NInt] = Xmax;
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
    LGrInt = new int[NInt - 1];
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
    qsort(arr, NumRanDat, sizeof *arr, [](const void* arr, const void* b)
    {
            int arg1 = *static_cast<const int*>(arr);
            int arg2 = *static_cast<const int*>(b);

            if (arg1 < arg2) return -1;
            if (arg1 > arg2) return 1;
            return 0;
    });
    //printArr(arr, NumRanDat);
    func(NumRanDat, arr, LGrInt, ans, NInt - 1);
    cout << '\n';
    file << '\n';
    cout << "№" << "|" << "интервал" << "|" << "количество" << '\n';
    file << "№" << "|" << "интервал" << "|" << "количество" << '\n';
    for (int i = 0; i < NInt; i++) 
    {
        int n1, n2;
        char l_border = '[';
        char r_border = ')';
        if (i == NInt - 1) r_border = ']';
        n1 = i != 0 ? LGrInt[i - 1] : Xmin;
        n2 = i != NInt - 1 ? LGrInt[i] : Xmax;
        file << i + 1 << " | " << l_border << n1 << ", " << n2 << r_border << " |  " << ans[i] << "\n";
        cout << i + 1 << " | " << l_border << n1 << ", " << n2 << r_border << " |  " << ans[i] << "\n";
    }
}