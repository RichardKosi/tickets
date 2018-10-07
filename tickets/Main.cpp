#include <stdlib.h>
#include <string>
#include <iostream>
#include <limits.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define LENGHT 40
#define SYSNOT 10
#define NOTEST //BINTESTOUT // DECTESTOUT // TIMETEST

typedef unsigned long long ull;
typedef unsigned int uint;
//using namespace std;
using std::cout;
using std::cin;
using std::endl;

const ull ALL1 = ~0ull;
const ull MAXI = ~0ull >> 1;
const ull IMAX = ~(~0ull >> 1);
const ull ALL0 = 0ull;

struct list {
	ull data;
	list* next;
	list(ull Data = 0ull) { data = Data; next = NULL; }
};
char* ulltoa(ull u, char *str)
{
	ull f = 1;
	for (int i = 63; i >= 0; i--) {
		if (u & f) str[i] = '1'; else str[i] = '0';
		f <<= 1;
	}
	return str;
}
char* strpow2(char str[], ull lenght, ull SystemNotation = 10ull)
  {
    ull nulls = '0';
    ull added = 0;
    for (ull l = lenght - 1;; l--)
    {
		added += (str[l] - nulls) * 2;
        str[l] = char(added % SystemNotation + nulls);
        added /= SystemNotation;
		if (l == 0) break;
    }
	return str;
  }
char* strsum(char str1[], char str2[], ull lenght, ull SystemNotation = 10ull)
  {
	ull nulls = '0';
	ull null2s = 2 * nulls;
    ull added = 0;
    for (ull l = lenght - 1;; l--)
    {
        added += str1[l] + str2[l] - null2s;
        str1[l] = char(added % SystemNotation + nulls);
        added /= SystemNotation;
        if (l == 0) break;
    }
    return str1;
  }
class BigInt
{
public: list *l;
		BigInt(ull i = 0ull)
		{
			l = new list();
			l->data = i;
		}
		char* ToString(ull size, ull SN = 10)
		{
			char* str = new char[size + 1];
			char* str2pow = new char[size];
			for (ull i = 0; i < size; i++) str[i] = str2pow[i] = '0';
			str[size] = '\0';
			str2pow[size - 1] = '1';
    list *List = l;
            do
            {
               for(ull st = 1; !(st & IMAX); st <<= 1)
               {
                  if (List->data & st)
                  {
					  strsum(str, str2pow, size);
                  }
                strpow2(str2pow, size);
               }
            }
            while(List = List->next);
			delete str2pow;
        return str;
		}
};

BigInt CalcLuck(uint LenghtNTicket, uint SysNot)
{
	uint SysNot_s = SysNot - 1;
	uint height = LenghtNTicket * SysNot_s / 2 + 1;
	BigInt** Arr[2];
	Arr[0] = new BigInt*[height];
	Arr[1] = new BigInt*[height];
	Arr[0][0] = new BigInt(1ull);
	Arr[1][0] = new BigInt(1ull);
	for (ull i = 1; i < height; i++)
	{
		Arr[0][i] = new BigInt();
		Arr[1][i] = new BigInt();
	}
	ull k, i = 0, l = SysNot, left = 0, right = 1;
	list *List, *List0, *List1, *List2, *List3;
	bool addbit = false;
	bool offbit = false;
	//[3][ ]
	//[|][|]
	//[ ][2]
	//[1][0]
	ull element;
	char ch[65];
	ch[64] = '\0';
	bool f = false;
	for (; i < LenghtNTicket; i++, l += SysNot_s)
	{
		for (k = 1; k < SysNot; k++)
		{
			List = List0 = Arr[right][k]->l;
			List1 = Arr[left][k]->l;
			List2 = Arr[right][k - 1]->l;
			f = false;
			while (List0 || List1 || List2 || addbit) {
				if (List0 == NULL) List->next = List0 = new list;
				List0->data = (List1 ? List1->data : 0ull) + (List2 ? List2->data : 0ull);
				if (addbit) {
					List0->data++;
					addbit = false;
				}
				if (List0->data & IMAX)
				{
					List0->data &= MAXI;
					addbit = true;
				}
#ifdef BINTESTOUT
				printf("%03d %064s ", k, ulltoa(List0->data, ch));
#endif // BINTESTOUT
				if (List0) List0 = List0->next;
				if (List1) List1 = List1->next;
				if (List2) List2 = List2->next;
				if (f) List = List->next;
				f = true;
			};
#ifdef BINTESTOUT
			printf("\n");
#endif // BINTESTOUT
		}
#ifdef DECTESTOUT
		for (ull j = 0; j < SysNot; j++)cout << j << "	" << (Arr[left][j] ? Arr[left][j]->l->data : 0) << "	" << (Arr[right][j] ? Arr[right][j]->l->data : 0) << endl;
#endif // DECTESTOUT
		for (; k < l && k < height; k++)
		{
			List = List0 = Arr[right][k]->l;
			List1 = Arr[left][k]->l;
			List2 = Arr[right][k - 1]->l;
			List3 = Arr[left][k - SysNot]->l;
			f = false;
			while (List0 || List1 || List2 || List3 || addbit)
			{
				if (List0 == NULL) List->next = List0 = new list;
				element = (List1 ? List1->data : 0ull) + (List2 ? List2->data : 0ull);
				if (offbit)
				{
					element--;
					offbit = false;
				}
				if (element < (List3 ? List3->data : 0ull))
				{
					element |= IMAX;
					offbit = true;
				}
				List0->data = element - (List3 ? List3->data : 0ull);//при вычитании проверить предыдущий элемент списка
				if (addbit) {
					List0->data++;
					addbit = false;
				}
				if (List0->data & IMAX)
				{
					List0->data &= MAXI;
					addbit = true;
				}
#ifdef BINTESTOUT
				printf("%03d %064s ", k, ulltoa(List0->data, ch));
#endif // BINTESTOUT
				if (List0) List0 = List0->next;
				if (List1) List1 = List1->next;
				if (List2) List2 = List2->next;
				if (List3) List3 = List3->next;
				if (f) List = List->next;
				f = true;
			};
#ifdef BINTESTOUT
			printf("\n");
#endif // BINTESTOUT
		}
#ifdef DECTESTOUT
		for (ull j = SysNot; j < l && j < height; j++) cout << j << "	" << (Arr[left][j] ? Arr[left][j]->l->data : 0) << "	" << (Arr[right][j] ? Arr[right][j]->l->data : 0) << endl;
		cout << endl;
#endif // DECTESTOUT
		if (right != 0) { right = 0; left = 1; }
		else { right = 1; left = 0; }
	}
#ifndef TIMETEST
	cout << endl;
#endif // !TIMETEST
	return *Arr[left][height - 1];
}

int main(int argc, char* argv[]) {
	int maxstr = 256;
	char *a = new char[maxstr + 1];
	for (int i = 0, j = 0; j < maxstr; i--, j++) a[j] = ((i == -1) ? i = 9 : i) + '0';
	a[maxstr] = '\0';
#ifndef TIMETEST
	uint LenghtNTicket;
	uint SysNot;
	cout << "Enter full ticket lenght: ";
	cin >> LenghtNTicket;
	cout << "Enter system notation: ";
	cin >> SysNot;
	cout /*<< a*/ << endl << CalcLuck(LenghtNTicket, SysNot).ToString(maxstr, 10) << endl;
	_getch();
#else
	LARGE_INTEGER a1, b1, c1;
	QueryPerformanceFrequency(&c1);
	QueryPerformanceCounter(&a1);
	cout << a << endl << CalcLuck(LENGHT, SYSNOT).ToString(maxstr, 10) << endl;
	QueryPerformanceCounter(&b1);
	printf("%lld %lld %lld %Lfsec\n", a1.QuadPart, b1.QuadPart, c1.QuadPart, long double(b1.QuadPart - a1.QuadPart) / c1.QuadPart);
	_getch();
#endif // !TIMETEST
	return 0;
}
