#include <ctime> 
#include <random>
#include <iostream> 
#include <fstream> 

extern "C" {
    void single(int* result, int* arr, int lenArr, int minX);
    void multiply(int* result, int lenResult, int* leftBorders, int nInt, int minX, int maxX, int* res);
}

int main() {
    int lenArr;
    int minX, maxX;
    int nInt;

    srand(time(NULL));

    std::cout << "Enter the number of elements of the array: ";
    std::cin >> lenArr;

    if (lenArr > 16 * 1024) {
        std::cout << "\nError of size of the array!\n";
        return 0;
    }

    std::cout << "\nEnter minimum range of values: ";
    std::cin >> minX;

    std::cout << "\nEnter maximum range of value: ";
    std::cin >> maxX;

    std::cout << "\nEnter the number of intervals: ";
    std::cin >> nInt;

    if (nInt <= 0) {
        std::cout << "\nNumber of intervals don't be <= 0!!!\n";
        return 0;
    }

    std::cout << "\nEnter array elements of left borders: ";
    int* leftBorders = new int[nInt];
    for (int i = 0; i < nInt; i++) {
        std::cin >> leftBorders[i];
        if (leftBorders[i] > maxX || leftBorders[i] < minX) {
            std::cout << "\nBorder out of range array!\n";
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

    single(result, arr, lenArr, minX);

    int* res = new int[nInt + 1];

    for (int k = 0; k <= nInt; k++)
        *(res + k) = 0;

    multiply(result, lenResult, leftBorders, nInt, minX, maxX, res);

    std::ofstream file;
    file.open("./output.txt");

    std::cout << "Result:\n";
    file << "Result:\n";

    std::cout << "Numbers: ";
    file << "Numbers: ";

    for (int i = 0; i < lenArr; i++) {
        std::cout << arr[i] << ' ';
        file << arr[i] << ' ';
    }
    std::cout << '\n';
    file << '\n';

    for (int j = 0; j < lenResult; j++) {
        std::cout << result[j] << ' ';
        file << result[j] << ' ';
    }

    std::cout << '\n';
    file << '\n';

    for (int i = 1; i < nInt; i++) {
        std::cout << i << ") \t";
        file << i << ") \t";

        std::cout << "Left Border: " << leftBorders[i - 1] << " ";
        file << "Left Border: " << leftBorders[i - 1] << " ";

        int count = 0;
        for (int j = 0; j <= abs(maxX - minX); j++) {
            if (i == nInt)
                if (res[j] >= leftBorders[i - 1]) {
                    count++;
                    continue;
                }
            if (res[j] >= leftBorders[i - 1] && res[j] < leftBorders[i])
                count++;
        }

        std::cout << "\tcount in interval: " << count << "\n";
        file << "\tcount in interval: " << count << "\n";

    }

    for (int i = 0; i < abs(maxX - minX); i++) {
        std::cout << arr[i] << ' ';
        file << arr[i] << ' ';
    }

    std::cout << '\n';

    file.close();

    delete[] leftBorders;
    delete[] arr;
    delete[] result;
    delete[] res;

    return 0;
}