/*#pragma once
#include <iostream>
#include "Tree.h"
#include "TPolinom.h"
using namespace std;
int main()
{
   // Tree<Polinom<std::string, TPolinom>> a(10);
    Tree<Polinom<string, int>> a(20);
    Polinom<string, int> tmp;
    tmp.polinom = 1;
    if (false) {
        tmp.name = "name1";
        tmp.polinom = 1;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name6";
        tmp.polinom = 2;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name3";
        tmp.polinom = 3;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name0";
        tmp.polinom = 4;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name4";
        tmp.polinom = 5;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name2";
        tmp.polinom = 6;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name2";
        tmp.polinom = 7;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name8";
        tmp.polinom = 8;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name9";
        tmp.polinom = 9;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name7";
        tmp.polinom = 10;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        //a.Delete("name8");
        //a.Delete("name1");
        //cout << a<<endl;
        //a.Delete("name0");
        //cout << "\ndelete" << endl;
        tmp.name = "name7";
        tmp.polinom = 10;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name8";
        tmp.polinom = 10;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name9";
        tmp.polinom = 10;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        tmp.name = "name10";
        tmp.polinom = 10;
        a.Add(tmp);
        cout << "add " << tmp << endl;
        cout << a << endl;

    }
    tmp.name = "name0"; cout << "ADDED "<<tmp.name << endl;  a.Add(tmp);
    tmp.name = "name2"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp); cout << a << endl;
    tmp.name = "name3"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp); cout << a << endl;
    tmp.name = "name4"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp);
    tmp.name = "name5"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp); 
    tmp.name = "name1"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp);
    tmp.name = "name10"; cout << "ADDED " << tmp.name << endl;  a.Add(tmp);

    cout << "                  ALL ADDED                   " << a<<endl<<endl << endl;
    char aaaaaaaa;

    int f = a.Delete("name10");
    cout << "DELETED name10 " << f << endl;
    cin >> aaaaaaaa;
    cout << a << endl;
    f = a.Delete("name1");
    cout << "DELETED name1 " << f << endl;
    cin >> aaaaaaaa;
    cout << a << endl;
    f = a.Delete("name2");
    cout << "DELETED name2 " << f << endl;
    cin >> aaaaaaaa;
    cout << a << endl;
    cout << "              000000000000000000000000000                "<<endl;
    a.Delete("name3"); cout << "DELETED name3 " << endl;
    a.Delete("name0"); cout << "DELETED name0 " << endl;
    a.Delete("name4"); cout << "DELETED name4 " << endl;
    a.Delete("name2"); cout << "DELETED name2 " << endl;
    a.Delete("name0"); cout << "DELETED name0 " << endl;
    a.Delete("name5"); cout << "DELETED name5 " << endl;
       cout << "DELETED all" << endl;
   cout << a << endl;
    cout <<"write any char to continue...    ";
    cin >> aaaaaaaa;
    cout << a;

    cout << "END\n";
    cin >> aaaaaaaa;
    return 0;
}
*/


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
