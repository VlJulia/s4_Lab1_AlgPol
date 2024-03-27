#pragma once
#include <iostream>
#include "HashTblCh.h"
#include "TPolinom.h"
using namespace std;
int main()
{
	cout << "                  999999999999999999999999999   " << endl;
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); p.name = "name4";
	a.Add(p); p.name = "name5";
	a.Add(p);
	HashTblCh<Polinom<string, TPolinom>> t = a;
	p.name = "name6";
	a.Add(p);

	bool b = (t == a);

    char aaaaaaaa;
    int l;
    cin >> aaaaaaaa;
    cin >> aaaaaaaa;
    cin >> l;
    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
