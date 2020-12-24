#include <ctime>
#include <random>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>


extern "C" {
    void first(int* result, int* arr, int minX);
    void second(int* result, int lenResult, int* LGrInt, int nInt, int minX, int maxX, int* output);
}

int main() {
    int lenArr;
    int minX, maxX;
    int nInt;

    srand(time(NULL));

    std::cout << "Size of array = 16 * N, input N: ";
    std::cin >> lenArr;

    if (lenArr > 16 * 1024) {
        std::cout << "\nError of size!\n";
        return 0;
    }

    std::cout << "\nInput Min X: ";
    std::cin >> minX;

    std::cout << "\nInput Max X: ";
    std::cin >> maxX;

    std::cout << "\nInput count of intervals (<= 24): ";
    std::cin >> nInt;

    if (nInt <= 0 || nInt > 24) {
        std::cout << "\nError of count intervals\n";
        return 0;
    }

    std::cout << "\nInput left borders: ";

    int* LGrInt = new int[nInt];

    for (int i = 0; i < nInt; i++) {
        std::cin >> LGrInt[i];
        if (LGrInt[i] > maxX || LGrInt[i] < minX) {
            std::cout << "\nBorder out of array!\n";
            return 0;
        }
    }

    int* arr = new int[lenArr];
    for (int j = 0; j < lenArr; j++)
        arr[j] = minX + rand() % (maxX - minX + 1);

    int* result = new int[abs(maxX - minX) + 1];
    for (int k = 0; k <= abs(maxX - minX); k++)
        result[k] = 0;

    int lenResult = abs(maxX - minX) + 1;

    first(result, arr, minX);

    int* output = new int[nInt + 1];

    for (int k = 0; k <= nInt; k++)
        output[k] = 0;

    second(result, lenResult, LGrInt, nInt, minX, maxX, output);

    std::ofstream file;
    file.open("./output.txt");

    for (int i = 1; i < nInt; i++) {
        std::cout << i << ")  ";
        file << i << ")  ";

        std::cout << "Border: " << LGrInt[i - 1] << "  ";
        file << "Border: " << LGrInt[i - 1] << "  ";

        int count = 0;
        for (int j = 0; j <= abs(maxX - minX); j++) {
            if (output[j] >= LGrInt[i - 1] && output[j] < LGrInt[i])
                count++;
        }

        std::cout << "count in interval: " << count << "\n";
        file << "count in interval: " << count << "\n";

    }

    std::cout << '\n';

    file.close();

    delete[] LGrInt;
    delete[] arr;
    delete[] result;
    delete[] output;

    return 0;
}
