#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

extern "C"
{
    void _sort(int NumRanDat, int* arr, int* LGrInt, int* res_arr);
}

int main()
{
    int NumRanDat = 0, Xmin = 0, Xmax = 0, NInt = 0;
    cout << "length of array less than 2^14: " << endl;
    cin >> NumRanDat;
    if (NumRanDat > 16 * 1024 || NumRanDat < 0) {
        cout << "Oops";
        exit(1);
    }
    cout << "lower limit: " << endl;
    cin >> Xmin;
    cout << "upper limit: " << endl;
    cin >> Xmax;
    std::cout << "number of ranges(<= 24): " << endl;
    std::cin >> NInt;
    if (NInt > 24) {
        cout << "Oops";
        exit(1);
    }
    int* LGrInt = new int[NInt]();
    std::cout << "Your " << NInt - 1 << " lower limits of ranges:" << endl;
    for (int i = 0; i < NInt - 1; i++) {
        cin >> LGrInt[i];
        if (LGrInt[i] < LGrInt[i - 1]) {
            cout << "Entered limit " << LGrInt[i] << " is bigger than previous, enter again" << endl;
            cin >> LGrInt[i];
        }
        if (LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
            cout << "Oops";
            exit(1);
        }
    }
    LGrInt[NInt - 1] = Xmax;
    int* mas = new int[NumRanDat]();
    for (int i = 0; i < NumRanDat; i++) {
        mas[i] = Xmin + rand() % (Xmax - Xmin);
    }
    int* rmas = new int[NInt];
    for (int i = 0; i < NInt; i++)
        rmas[i] = 0;
    _sort(NumRanDat, mas, LGrInt, rmas);
    ofstream file("res.txt");
    cout << "Generated random numbers:" << endl;
    file << "Generated random numbers:" << endl;
    for (int i = 0; i < NumRanDat; i++) {
        cout << mas[i] << " ";
        file << mas[i] << " ";
    }
    cout << endl;
    file << endl;
    cout << "number|range|contain" << endl;
    file << "number|range|contain" << endl;
    cout << "____________________"<< endl;
    file << "____________________"<< endl;
    for (int i = 0; i < NInt; i++) {
        int n1, n2;
        n1 = i != 0 ? LGrInt[i - 1] : Xmin;
        n2 = i != NInt ? LGrInt[i] : Xmax;
        file << i + 1 << "   #  " << n1 << ", " << n2 << " #  " << rmas[i] << "\n";
        cout << i + 1 << "   #  " << n1 << ", " << n2 << " #  " << rmas[i] << "\n";
    }
}