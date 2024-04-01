﻿// Interface.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "Interf.h"
#include "TPolinom.h"
using namespace std;

int hello() {
    int a;
    cout << endl << endl << endl << endl;
    cout << "Select the command: | Выберите команду" << endl;
    cout << "1. Output the table | Вывести таблицу" << endl;
    cout << "2. Add new | Добавить элемент" << endl;
    cout << "3. Delete | Удалить" << endl;
    cout << "4. Find | Найти элемент" << endl;
    cout << "5. Exist | Существует" << endl;
    cout << "6. Division (with remainder) | Деление с остатком" << endl;
    cout << "7. Derivative | Производная" << endl;
    cout << "8. Integral | Интеграл" << endl;
    cout << "9. Multiplication | Умножение" << endl;
    cout << "10. Division (without remainder) | Деление (без остатка)" << endl;
    cout << "11. Sum | Сложение" << endl;
    cout << "12. Difference | Разность" << endl;
    cout << "13. Select table | Выбрать таблицу" << endl;

    cout << "0. Exit | Выход" << endl;
    cin >> a;
    return a;
}

TPolinom CreatePol(string sp) {
    TPolinom tmp(sp);
    return tmp;
}

int main()
{
    Interf <TPolinom> tb(20);
    //примеры входных данных
    TPolinom t1("XYZ -2X2Y2Z3");
    TPolinom t2("X4Y3Z -2X2Y2Z3");

    TPolinom t3("X1Y3Z +3XYZ");
    //TPolinom t4("5X1Y2Z3 -X4Y2Z3");
    //TPolinom t5("-4XYZ +8XYZ");
    tb.Insert("name1", t1);
    tb.Insert("name2", t2);
    tb.Insert("name3", t3);
    tb.NextTabl();

    //tb.Insert("name4", t4);
    //tb.Insert("name5", t5);
    //cout << 1 << tb << endl; //tb.NextTabl();
    //cout << 2 << tb << endl; tb.NextTabl();
    //cout << 3 << tb << endl; tb.NextTabl();
    //cout << 4 << tb << endl; tb.NextTabl();
    //cout << 5 << tb << endl; tb.NextTabl();
    //cout << 6 << tb << endl; 
    cout << "////////////////////////////////////////////" << endl;

    int f, a;
    string sn, sp, sn1;
    char ch;
    
    do {
        f = hello();
        switch (f)
        {
        case 1:
            //вывод таблицы
            cout << tb;
            break;
        case 2:
            //добавить
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            cout << "Enter polinom" << endl;
            cin >> sp;
            tb.Insert(sn, CreatePol(sp));
            break;
        case 3:
            //удалить
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            tb.Delete(sn);
            break;
        case 4:
            //найти
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            cout << "Polinom:" << tb.Find(sn);

            break;
        case 5:
            //существует
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            if (tb.Exist(sn)) {
                cout << "Exist" << endl;
            }
            else {
                cout << "Not exist" << endl;
            }
            break;
        case 6:
            //division
            cout << "Select polinom from table" << endl;
            cout << "Enter name of first operator" << endl;
            cin >> sn;
            cout << "Enter name of second operator" << endl;
            cin >> sn1;
            cout << tb.Division(sn, sn1) << endl;
            break;
        case 7:
            //derivative
            cout << "Select polinom from table" << endl;
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            cout << "Enter char" << endl;
            cin >> ch;
            cout << tb.derivative(sn, ch) << endl;
            break;
        case 8:
            //integral
            cout << "Select polinom from table" << endl;
            cout << "Enter name of polinom" << endl;
            cin >> sn;
            cout << "Enter char" << endl;
            cin >> ch;
            cout << tb.integral(sn, ch) << endl;
            break;
        case 9:
            //mult
            cout << "Select polinom from table" << endl;
            cout << "Enter name of 1 polinom" << endl;
            cin >> sn;
            cout << "Enter name of 2 polinom" << endl;
            cin >> sn1;
            cout << tb.Mult(sn, sn1) << endl;
            break;
        case 10:
            //div
            cout << "Select polinom from table" << endl;
            cout << "Enter name of 1 polinom" << endl;
            cin >> sn;
            cout << "Enter name of 2 polinom" << endl;
            cin >> sn1;
            cout << tb.Div(sn, sn1) << endl;
            break;
        case 11:
            //sum
            cout << "Select polinom from table" << endl;
            cout << "Enter name of 1 polinom" << endl;
            cin >> sn;
            cout << "Enter name of 2 polinom" << endl;
            cin >> sn1;
            cout << tb.Sum(sn, sn1) << endl;
            break;
        case 12:
            //dif
            cout << "Select polinom from table" << endl;
            cout << "Enter name of 1 polinom" << endl;
            cin >> sn;
            cout << "Enter name of 2 polinom" << endl;
            cin >> sn1;
            cout << tb.Dif(sn, sn1) << endl;
            break;
        case 13: 
            cout << "Select table:" << endl;
            cout << "0 - Tree" << endl;
            cout << "1 - Hash Chain" << endl;
            cout << "2 - Hash Double" << endl;
            cout << "3 - List" << endl;
            cout << "4 - Unordered Array" << endl;
            cout << "5 - Ordered Array" << endl;
            cin >> a;
            switch (a) {
            case 0: 
                tb.SetTree();
                break;
            case 1:
                tb.SetHashTblCh();
                break;
            case 2:
                tb.SetHashTblDH();
                break;
            case 3:
                tb.SetListTable();
                break;
            case 4:
                tb.SetunorderedArrayTable();
                break;
            case 5:
                tb.SetorderedArrayTable();
                break;

            default:
                cout << "Wrong number" << endl;
                break;
            }
            break;
        
        default:
            cout << "Wrong number" << endl;
            break;
        }
    } while (f != 0);
}
