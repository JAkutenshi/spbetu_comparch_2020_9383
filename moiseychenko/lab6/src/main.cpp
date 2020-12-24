#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;


extern "C" void distribution(int* arr, int* LGrInt, int NumRanDat, int* result);


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int NumRanDat = 0, Xmin = 0, Xmax = 0, NInt = 0;
	cout << "Enter the size of the array (<=2^14):\n";
	cin >> NumRanDat;
	if (NumRanDat > 16 * 1024 || NumRanDat <= 0) {
		cout << "error: wrong array size entered\n";
		exit(1);
	}
	cout << "Enter the lower limit:\n";
	cin >> Xmin;
	cout << "Enter the upper limit:\n";
	cin >> Xmax;
	if (Xmin > Xmax) {
		cout << "error: wrong limits entered\n";
		exit(1);
	}
	cout << "Enter the number of ranges (<= 24): \n";
	cin >> NInt;
	if (NInt > 24 || NInt < 1 || NInt >(Xmax - Xmin + 1)) {
		cout << "error: wrong number of ranges entered\n";
		exit(1);
	}
	int* LGrInt = new int[NInt+1]();
	LGrInt[0] = Xmin;
	LGrInt[NInt] = Xmax + 1;
	if (NInt == 2)
		cout << "Enter the lower limit of the second range:\n";
	else
		cout << "Enter " << NInt - 1 << " lower range limits:\n";
	for (int i = 1; i < NInt; i++) {
		cin >> LGrInt[i];
		while (LGrInt[i] < LGrInt[i-1]) {
			cout << "The limit should be greater than the previous one (>" << LGrInt[i-1] << ")\n";
			cin >> LGrInt[i];
		}
		if (LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
			cout << "error: wrong lower limit entered\n";
			exit(1);
		}
	}
	int* arr = new int[NumRanDat]();
	for (int i = 0; i < NumRanDat; i++) {
		arr[i] = rand() % (Xmax - Xmin + 1) + Xmin;
	}
	sort(arr, arr + NumRanDat);
	int* result = new int[NInt];
	for (int i = 0; i < NInt; i++)
		result[i] = 0;
	distribution(arr, LGrInt, NumRanDat, result);
	LGrInt[NInt] -= 1;
	ofstream file("result.txt");
	cout << "\nGenerated numbers:\n";
	file << "Generated numbers:\n";
	for (int i = 0; i < NumRanDat; i++) {
		cout << arr[i] << " ";
		file << arr[i] << " ";
	}
	cout << "\n\n";
	file << "\n\n";
	cout << "Number | Range | Quantity\n";
	file << "Number | Range | Quantity\n";
	cout << "-------------------------" << endl;
	file << "-------------------------" << endl;
	for (int i = 0; i < NInt; i++) {
		if (i == NInt - 1) {
			file << "  " << i + 1 << "  |  [" << LGrInt[i] << ", " << LGrInt[i + 1] << "]  |  " << result[i] << "\n";
			cout << "  " << i + 1 << "  |  [" << LGrInt[i] << ", " << LGrInt[i + 1] << "]  |  " << result[i] << "\n";
		}
		else {
			file << "  " << i + 1 << "  |  [" << LGrInt[i] << ", " << LGrInt[i + 1] << ")  |  " << result[i] << "\n";
			cout << "  " << i + 1 << "  |  [" << LGrInt[i] << ", " << LGrInt[i + 1] << ")  |  " << result[i] << "\n";
		}
	}
}