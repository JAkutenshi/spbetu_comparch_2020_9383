#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


extern "C" {
	void distribution(int NumRanDat, int* arr, int* LGrInt, int* range);
}


int main() {
	setlocale(LC_ALL, "Russian");
	int NumRanDat = 0, Xmin = 0, Xmax = 0, NInt = 0;
	cout << "������� ������ ������� (������ �� ������ ��������� 2^14):\n";
	cin >> NumRanDat;
	if (NumRanDat > 16 * 1024 || NumRanDat <= 0) {
		cout << "������! �������� ������ �������.\n";
		exit(1);
	}
	cout << "������� ������ ������:\n";
	cin >> Xmin;
	cout << "������ ������� ������:\n";
	cin >> Xmax;
	if (Xmin > Xmax) {
		cout << "������! �������� ������ � ������� �������.\n";
		exit(1);
	}
	cout << "������� ���������� ���������� (���������� ������ ���� <= 24): \n";
	cin >> NInt;
	if (NInt > 24 || NInt < 1 || NInt > (Xmax - Xmin + 1)) {
		cout << "������! �������� ���������� ����������.\n";
		exit(1);
	}
	int* LGrInt = new int[NInt]();
	cout << "������� ������ ������� ���������� � ���������� " << NInt - 1 << ":\n";
	for (int i = 0; i < NInt - 1; i++) {
		cin >> LGrInt[i];
		if (LGrInt[i] < LGrInt[i - 1]) {
			cout << "��������� ������ " << LGrInt[i] << " ������ �����������\n";
			cin >> LGrInt[i];
		}
		if (LGrInt[i] < Xmin || LGrInt[i] > Xmax) {
			cout << "������! �������� ������ ������.\n";
			exit(1);
		}
	}
	LGrInt[NInt - 1] = Xmax;
	int* arr = new int[NumRanDat]();
	for (int i = 0; i < NumRanDat; i++) {
		arr[i] = Xmin + rand() % (Xmax - Xmin);
	}
	int* range = new int[NInt];
	for (int i = 0; i < NInt; i++)
		range[i] = 0;
	distribution(NumRanDat, arr, LGrInt, range);
	ofstream file("result.txt");
	cout << "\n��������������� ��������������� �����:\n";
	file << "��������������� ��������������� �����:\n";
	for (int i = 0; i < NumRanDat; i++) {
		cout << arr[i] << " ";
		file << arr[i] << " ";
	}
	cout << "\n\n";
	file << "\n\n";
	cout << "�����|��������|����������\n";
	file << "�����|��������|����������\n";
	cout << "-------------------------" << endl;
	file << "-------------------------" << endl;
	int n1, n2;
	for (int i = 0; i < NInt; i++) {
		if (i == 0) {
			n1 = Xmin;
			n2 = LGrInt[i];
		}
		else
		{
			n1 = LGrInt[i - 1];
			n2 = LGrInt[i];
		}
		file << "  " << i + 1 << "  |  " << n1 << ", " << n2 << "  |  " << range[i] << "\n";
		cout << "  " << i + 1 << "  |  " << n1 << ", " << n2 << "  |  " << range[i] << "\n";
	}
}
