#include <iostream>
#include <fstream>

#define N 80

using namespace std;

int main() {
	setlocale(0, "");
	cout << "________________________________________________________________________" << endl
		<< "|Version #5.                                                           |" << endl
		<< "|The type of conversion is:                                            |" << endl
		<< "|Convert all lowercase Latin letters of the input string to uppercase, |" << endl
		<< "|and decimal digits to inverse, the remaining characters of the input  |" << endl
		<< "|string are passed directly to the output string.                      |" << endl
		<< "|The work was performed by Anna Karpekina, a student of group 9383.    |" << endl
		<< "|______________________________________________________________________| " << endl;
	char arr[N], res[N];
	cout << "Input string: ";
	cin.getline(arr, N);
	__asm{
	mov edi, 0; 
	mov esi, 0; 

	start:
	mov al, arr[edi]  ; ñ÷èòûâàåì òåêóùèé ñèìâîë str1 ïî èíäåêñó edi â al
	cmp al, 'z'    ; åñëè áîëüøå ÷åì z,
	jg write
	cmp al, 'a'    ; åñëè ìåíüøå ÷åì a,
	jl check_ten   ; òî ïðîâåðÿåì, ÿâëÿåòñÿ ëè ñèìâîë öèôðîé,
	sub al, 0x20   ; èíà÷å ïåðåâîäèì ëàòèíñêóþ áóêâó ê âåðõíåìó ðåãèñòðó
	jmp write

	check_ten:
	cmp al, 0x30   ; åñëè ìåíüøå ÷åì 0,
	jl write       ; òî çàïèñûâàåì ñèìâîë â âûõîäíóþ ñòðîêó
	cmp al, 0x39   ; åñëè áîëüøå ÷åì 9,
	jg write       ; òî çàïèñûâàåì ñèìâîë â âûõîäíóþ ñòðîêó
	mov ah, 0x69   ; çàïèñsâàåì â ah 9
	sub ah, al     ; âû÷èòàåì èç 9 íàøå ÷èñëî
	mov al,ah
	jmp write
	

	write:
	mov res[esi], al; ïîìåùàåì òåêóùèé ñèìâîë â âûõîäíóþ ñòðîêó
	cmp al, 0        ; åñëè áûë âñòðå÷åí íóëåâîé ñèìâîë,
	je end_func      ; òî çàêàí÷èâàåì
	inc edi          ; èíà÷å óâåëè÷èâàåì èíäåêñû
	inc esi
	jmp start        ; è âîçâðàùàåìñÿ ê ñ÷èòûâàíèþ ñòðîêè

	end_func:
	}
	cout << res;
	ofstream output;
	output.open("out.txt");
	output << res;
	output.close();
	return 0;
}
