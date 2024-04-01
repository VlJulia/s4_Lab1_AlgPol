#pragma once
#include <iostream>
#include "Table.h"
#include "Tree.h"
#include "HashTblCh.h"
#include "HashTblDH.h"
#include "ListTable.h"
#include "orderedArrayTable.h"
#include "unorderedArrayTable.h"
#include "TPolinom.h"

using namespace std;
const int n = 6;

template<class T = TPolinom>
class Interf {
	Table<T>* tbl_array[n];
	Table<T>* current;
	int cur = 0;
	int size;

	public:
	Interf(int s=0) {
		size = s;
		tbl_array[0] = new Tree<T>(s);
		tbl_array[1] = new HashTblCh<T>(s);
		tbl_array[2] = new HashTblDH<T>(s);
		tbl_array[3] = new ListTable<T>(s);
		tbl_array[4] = new unorderedArrayTable<T>(s);
		tbl_array[5] = new orderedArrayTable<T>(s);
		current = tbl_array[cur];
	}
	int NextTabl() { cur = (cur + 1) % n; current = tbl_array[cur]; return 1; }
	int GetDataCount()   const; // ���������� �������
	bool IsEmpty() const;  // �����?
	bool IsFull() const;                       // ���������?
	//��������� 
	int Reset(void) ; // ���������� �� ������ ������
	int IsTabEnded(void) const; // ������� ���������?
	int GoNext(void); // ������� � ��������� ������
	std::string GetKey(void) const;
	 T GetValuePtr(void) const;
	//�����
	bool Insert(string key, T obj);
	bool Delete(std::string key);
	 T Find(std::string key);
	bool Exist(std::string key);
	//
	//�������� � ����������
	T Division(string key1, string key2);
	T derivative(string key, char md);
	T integral(string key, char md);
	T Mult(string key1, string key2, char md);
	T Div(string key1, string key2, char md);
	T Sum(string key1, string key2, char md);
	T Dif(string key1, string key2, char md);
	void calculate(string key1, double X = 0, double Y = 0, double Z = 0);
	friend std::ostream& operator<<(std::ostream& os, Interf& tab)
	{
		std::cout << *tab.current;
		return os;
	}
private:
	void AddDialog(T obj) { 
		std::cout << " please print key for new obj..\n";
		string key; std::cin >> key;
		Insert(key, obj);
	};
};

template<class T>
int Interf<T>::GetDataCount() const
{
	return current->GetDataCount();
}

template<class T>
bool Interf<T>::IsEmpty() const
{
	return current->IsEmpty();
}

template<class T>
bool Interf<T>::IsFull() const
{
	return current->IsFull();
}

template<class T>
int Interf<T>::Reset(void)
{
	return current->Reset();
}

template<class T>
int Interf<T>::IsTabEnded(void) const
{
	return current->IsTabEnded();
}

template<class T>
int Interf<T>::GoNext(void)
{
	return current->GoNext();
}

template<class T>
std::string Interf<T>::GetKey(void) const
{
	return current->GetKey();
}

template<class T>
T Interf<T>::GetValuePtr(void) const
{
	return current->GetValuePtr();
}

template<class T>
bool Interf<T>::Insert(string key, T obj)
{
	bool b = false;
	for (int i = 0; i < n; i++) b=tbl_array[i]->Insert(key, obj);
	return b;
}

template<class T>
bool Interf<T>::Delete(std::string key)
{
	bool b = false;
	for (int i = 0; i < n; i++) b = tbl_array[i]->Delete(key, obj);
	return b;
}

template<class T>
T Interf<T>::Find(std::string key)
{
	return current->Find(key);
}

template<class T>
bool Interf<T>::Exist(std::string key)
{
	return current->Exist(key);
}

template<class T>
T Interf<T>::Division(string key1, string key2) //� ��������
{
	try {
		T p1 = current->Find(key1);
		T p2 = current->Find(key2);
	}
	catch (...) { std::cout << "cant find "<<endl; }
	T ost;
	T res = Division(p1, p2, ost);
	std::cout << "res is " << res << " ost is" << ost<<endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv=0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	std::cout << "save ost? 0-no 1-yes" << endl;
	std::cin >> otv;
	if (otv) AddDialog(ost);
	return res;
}

template<class T>
inline T Interf<T>::derivative(string key, char md)
{
	try {
		T p1 = current->Find(key1);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1.derivative(md);
	std::cout << "res is " << res <<  endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::integral(string key, char md)
{
	try {
		T p1 = current->Find(key1);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1.integral(md);
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Mult(string key1, string key2, char md)
{
	try {
		T p1 = current->Find(key1);
		T p2 = current->Find(key2);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1*p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Div(string key1, string key2, char md)
{
	try {
		T p1 = current->Find(key1);
		T p2 = current->Find(key2);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1 / p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Sum(string key1, string key2, char md)
{
	try {
		T p1 = current->Find(key1);
		T p2 = current->Find(key2);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1 + p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Dif(string key1, string key2, char md)
{
	try {
		T p1 = current->Find(key1);
		T p2 = current->Find(key2);
	}
	catch (...) { std::cout << "cant find " << endl; }
	T res = p1 - p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline void Interf<T>::calculate(string key1, double X, double Y, double Z)
{
	try {
		T p1 = current->Find(key1);
	}
	catch (...) { std::cout << "cant find " << endl; }
	double res = p1.calculate(X, Y, Z);
	std::cout << "res is " << res << endl;
	return;
	
}
