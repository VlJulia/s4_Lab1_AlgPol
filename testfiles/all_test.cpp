// VrPr2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Table.h"
using namespace std;
int main()
{
    cout << "hello!";
    /*
   TPolinom p("3X3Y3Z3 - 2X2Y2Z2 + 1XYZ");
   
   TPolinom p2("XYZ");
   TPolinom p3;
    cout << "\n p\n" << p << endl;
    cout << "\n p2\n" << p2 << endl;

    cout << p / p2;
    cout << "First without throws\n\n";
    p2.AddMonom(TMonom(1,0,0,0));
    cout << "\n p2\n" << p2 << endl;
    cout << p.Division(p2,p3);
    cout << "Second without throws\n\n";
    cout << "\n p2\n" << p2 << endl;
    try {
        cout << p / p2;
        cout << "shoud be throw\n\n";
    }
    catch (const char* a) {
        string s(a);
        if (s == "impossible division operation without remainder")
            cout << "success!!"<<endl;
        else
        {
            cout << s;
        }
    }
    */
   /*
    TPolinom p3;

    
    p3.AddMonom(TMonom(1, 9, 3, 4));
    cout << "\n p3\n" << p3 << endl;
    p3.AddMonom(TMonom(1, 2, 9, 4));
    cout << "\n p3\n" << p3 << endl;
    p3.AddMonom(TMonom(1,2,3,4));
    p3.Reset();
    p3.AddMonom(TMonom(1, 5, 3, 4));
    p3.Reset();
    p3.AddMonom(TMonom(1, 9, 3, 4));
    p3.Reset();
    p3.GoNext();
    cout << "\n p3\n" << p3 << endl;
    p3.GoNext();
    cout << "\n p3\n" << p3 << endl;
    p3.DeleteCurrent();
    cout << "\n p3\n" << p3 << endl;
    p3.GoNext();
    
  
    //p.AddPolinom("3X4Y7Z8 - 6X1Y1Z1");
    */
 
    char aaaaaaaa;
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
