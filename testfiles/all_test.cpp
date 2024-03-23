#include <iostream>
#include "Table.h"
#include "TPolinom.h"
#include "Tree.h"
using namespace std;
int main()
{
   // Tree<Polinom<std::string, TPolinom>> a(10);
    Tree<Polinom<string, int>> a(10);
    Polinom<string, int> tmp;
    tmp.name = "name1";
    tmp.polinom = 1;
    a.Add(tmp); 
    cout << a.GetDataCount();
    tmp.name = "name6";
    tmp.polinom = 2;
    a.Add(tmp);
    tmp.name = "name3";
    tmp.polinom = 3;
    a.Add(tmp);
    tmp.name = "name0";
    tmp.polinom = 4;
    a.Add(tmp);
    tmp.name = "name4";
    tmp.polinom = 5;
    a.Add(tmp);
    tmp.name = "name2";
    tmp.polinom = 6;
    a.Add(tmp);
    tmp.name = "name2";
    tmp.polinom = 7;
    a.Add(tmp);
    tmp.name = "name8";
    tmp.polinom = 8;
    a.Add(tmp);
    tmp.name = "name9";
    tmp.polinom = 9;
    a.Add(tmp);
    tmp.name = "name7";
    tmp.polinom = 10;
    a.Add(tmp);
    a.Delete("name8");
    a.Delete("name1");
    cout << a<<endl;
    a.Delete("name0");
    cout << "\ndelete" << endl;


    char aaaaaaaa;

    cout <<"write any char to continue...    ";
    cin >> aaaaaaaa;
    cout << a;

    cout << "END\n";
    cin >> aaaaaaaa;
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
