#include <iostream>
#include <random>
#include <fstream>
#include <ctime>

extern "C"
{
    void ASM_MOD(short* arr, unsigned short* res, short* LGrInt, unsigned short NInt, unsigned short NumRanDat);
}

int main()
{
    srand(time(0));
    unsigned short NumRanDat;
    short Xmin;
    short Xmax;
    unsigned short NInt;
    std::cout << "Input length of the array: ";
    std::cin >> NumRanDat;
    if (NumRanDat > 16 * 1024 || NumRanDat <= 0)
    {
        std::cout << "Invalid length!\n";
        return 0;
    }
    std::cout << "Input min of values: ";
    std::cin >> Xmin;
    std::cout << "Input max of values: ";
    std::cin >> Xmax;
    if (Xmin > Xmax)
    {
        std::cout << "Minimum > maximum!\n";
        return 0;
    }
    std::cout << "Input number of interval: ";
    std::cin >> NInt;
    if (NInt > 24)
    {
        std::cout << "Invalid number!\n";
        return 0;
    }
    short* LGrInt = new short[NInt];
    std::cout << "Input elements of left borders:\n";
    for (int i = 0; i < NInt; i++)
    {
        std::cin >> LGrInt[i];
        if (LGrInt[i] < Xmin || LGrInt[i] > Xmax) std::cout << "Invalid border!\n";
    }
    for (int i = 0; i < NInt - 1; i++)
    {
        for (int j = 0; j < NInt - 1 - i; j++)
        {
            if (LGrInt[j] < LGrInt[j + 1])
            {
                short temp = LGrInt[j];
                LGrInt[j] = LGrInt[j + 1];
                LGrInt[j + 1] = temp;
            }
        }
    }
    short* arr = new short[NumRanDat];
    std::cout << "Random array: ";
    for (int i = 0; i < NumRanDat; i++) 
    {
        arr[i] = Xmin + rand() % (Xmin + Xmax);
        std::cout << arr[i] << ' ';
    }
    unsigned short* res = new unsigned short[NInt];
    for (int i = 0; i < NInt; i++) res[i] = 0;
    ASM_MOD(arr, res, LGrInt, NInt, NumRanDat);
    std::ofstream out;
    out.open("file.txt");
    for (int i = 0; i < NInt; i++)
    {
        std::cout << "Left border: " << LGrInt[i] << " ___ " << "Amount of numbers: " << res[i] << '\n';
        out << "Left border: " << LGrInt[i] << " ___ " << "Amount of numbers: " << res[i] << '\n';
    }
    delete[] arr;
    delete[] res;
    delete[] LGrInt;
    out.close();
    return 0;
}

