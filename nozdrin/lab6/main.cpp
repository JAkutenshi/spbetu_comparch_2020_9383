#include <iostream> 
#include <fstream> 
#include <random>

#include <ctime> 

extern "C" {
    void unit(int* result1, int* randDataArr, int NumRanDat, int Xmin);
    void final(int* result1, int result_len, int* LGrInt, int NInt, int Xmin, int Xmax, int* result2);
}

void readParams(int*, int*, int*, int*);
void readLGrInt(int*, int);
void printResult1(int*);
void printResult2(int*, int*, int, int, int, int, std::ofstream);

int main() {
  int NumRanDat, Xmin, Xmax, NInt;
  int *LGrInt = nullptr;

  readParams(&NumRanDat, &Xmin, &Xmax, &NInt);
  readLGrInt(LGrInt, NInt);

  for (int i = 0; i < NInt; i++)
    if (LGrInt[i] > Xmax || LGrInt[i] < Xmin) {
      delete [] LGrInt;
      return 0;
    }

  int *randDataArr  = new int[NumRanDat];
  int result_len    = abs(Xmax-Xmin)+1;
  int *result1      = new int[result_len];
  int *result2      = new int[NInt+1];

  srand(time(NULL));
  for (int i = 0; i < NumRanDat; i++)
      randDataArr[i] = Xmin+rand()%(Xmax-Xmin+1);
  for (int i = 0; i < result_len; i++)
      result1[i] = 0;
  for (int i = 0; i < NInt+1; i++)
      result2[i] = 0;

  unit(result1, randDataArr, NumRanDat, Xmin);
  
  printResult1(result1);
  
  final(result1, result_len, LGrInt, NInt, Xmin, Xmax, NumRanDat, result2);

  std::ofstream output;
  file.open("output.txt");
  printResult2(result2, LGrInt, NInt, Xmin, Xmax, output);
  
  file.close();
  delete [] LGrInt;
  delete [] randDataArr;
  delete [] result1;
  delete [] result2;
  
  return 0;
}

void readParams(int *NumRanDat, int *Xmin, int *Xmax, int *NInt) {
  std::cout << "Enter NumRanDat\n";       std::cin >> &NumRanDat;
  if (&NumRanDat > 16*1024) { &NumRanDat = 16*1024; }
  std::cout << "Enter Xmin\n";            std::cin >> &Xmin;
  std::cout << "Enter Xmax\n";            std::cin >> &Xmax;
  std::cout << "Enter NInt\n";            std::cin >> &NInt;
  if (&NInt <= 0 || &NInt > 24) { &NInt = 2; }
}

void readLGrInt(int *LGrInt, int NInt){
  LGrInt = new int[NInt];
  std::cout << "Enter LGrInt randDataArray";
  for (int i = 0; i < NInt; i++)
    std::cin >> LGrInt[i];
}

void printResult1(int* result1){
  for (int j = 0; j < result_len; j++)
    std::cout << result1[j] << ' ';
  std::cout << '\n';
}

void printResult2(int *result2, int *LGrInt, int NInt, int Xmin, int Xmax, int NumRanDat, std::ofstream output){
  std::cout << "Result:\n";               file << "Result:\n";
  std::cout << "DataArray: ";             file << "DataArray: ";
  for (int i = 0; i < NumRanDat; i++) {
    std::cout << randDataArr[i] << ' ';   file << randDataArr[i] << ' ';
  }
  std::cout << '\n';                      file << '\n';

  for (int i = 1; i < NInt; i++) {
    std::cout << i << ") \t";
    file      << i << ") \t";
    std::cout << "Left Border: " << LGrInt[i - 1] << " ";
    file      << "Left Border: " << LGrInt[i - 1] << " ";
    int c = 0;
    for (int j = 0; j < result_len; j++) {
      if (i == NInt)
        if (result2[j] >= LGrInt[i - 1]) {
          c++;
          continue;
        }
      if (result2[j] >= LGrInt[i - 1] && result2[j] < LGrInt[i])
        c++;
    }
    std::cout << "\tcount in interval: " << c << "\n";
    file      << "\tcount in interval: " << c << "\n";
  }
}
