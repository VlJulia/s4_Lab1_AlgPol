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
	int m_key_size = 0;

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
	int NextTabl() { 
		cur = (cur + 1) % n; 
		current = tbl_array[cur]; 
		return 1; 
	}
	int GetDataCount()   const; // количество записей
	bool IsEmpty() const;  // пуста?
	bool IsFull() const;                       // заполнена?
	//навигация 
	int Reset(void) ; // установить на первую запись
	int IsTabEnded(void) const; // таблица завершена?
	int GoNext(void); // переход к следующей записи
	std::string GetKey(void) const;
	 T GetValuePtr(void) const;
	//общее
	bool Insert(string key, T obj);
	bool Delete(std::string key);
	 T Find(std::string key);
	bool Exist(std::string key);
	//
	//операции с полиномами
	T derivative(string key, char md);
	T integral(string key, char md);
	T Mult(string key1, string key2);
	T Div(string key1, string key2);
	T Sum(string key1, string key2);
	T Dif(string key1, string key2);
	
	void SetTree() {
		cur = 0;
		current = tbl_array[cur];
	}
	void SetHashTblCh() {
		cur = 1;
		current = tbl_array[cur];
	}
	void SetHashTblDH() {
		cur = 2;
		current = tbl_array[cur];
	}
	void SetListTable() {
		cur = 3;
		current = tbl_array[cur];
	}
	void SetunorderedArrayTable() {
		cur = 4;
		current = tbl_array[cur];
	}
	void SetorderedArrayTable() {
		cur = 5;
		current = tbl_array[cur];
	}
	
	void calculate(string key1, double X = 0, double Y = 0, double Z = 0);
	friend std::ostream& operator<<(std::ostream& os, Interf& tab)
	{
		os << "data count = " << tab.current->GetDataCount() << endl;
		switch (tab.cur) {
		case 0:
			std::cout << "Tree ";
			break;
		case 1:
			std::cout << "Hash CH ";
			break;
		case 2:
			std::cout << "Hash DH ";
			break;
		case 3:
			std::cout << "List ";
			break;
		case 4:
			std::cout << "Array unordered ";
			break;
		case 5:
			std::cout << "Array ordered ";
			break;
		default:
			break;
		}
		os << endl;
		string s1 = "key", s2 = "value";
		os << s1;
		for (int i = s1.length(); i < tab.m_key_size; i++) os << " ";
		os << "|" << s2 << endl;
		for (int i = 0; i < tab.m_key_size; i++) os << "-";
		os << "+----------------------------------------" << endl;
		if (tab.current->IsEmpty()) {
			return os;
		}
		for (tab.current->Reset(); !tab.current->IsTabEnded(); tab.current->GoNext())
		{
			string key = tab.current->GetKey();
			os << key;
			for (int i = key.length(); i < tab.m_key_size; i++) os << " ";
			os << "|" << tab.current->GetValuePtr() << endl;
		}
		if (!(tab.current->IsEmpty())) {
			string key = tab.current->GetKey();
			os << key;
			for (int i = key.length(); i < tab.m_key_size; i++) os << " ";
			os << "|" << tab.current->GetValuePtr() << endl;
		}
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
	if (key.length() > m_key_size) {
		m_key_size = key.length();
	}
	for (int i = 0; i < n; i++) 
		b=tbl_array[i]->Insert(key, obj);
	return b;
}

template<class T>
bool Interf<T>::Delete(std::string key)
{
	bool b = false;
	for (int i = 0; i < n; i++) b = tbl_array[i]->Delete(key);
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
T Interf<T>::Div(string key1, string key2) //с остатком
{
	T p1, p2;
		p1 = current->Find(key1);
		p2 = current->Find(key2);
	T ost;
	p1 = p1.T::Division(p2,ost);
	std::cout << "res is " << p1 << " ost is" << ost<<endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv=0;
	std::cin >> otv;
	if (otv) AddDialog(p1);
	std::cout << "save ost? 0-no 1-yes" << endl;
	std::cin >> otv;
	if (otv) AddDialog(ost);
	return p1;
}

template<class T>
inline T Interf<T>::derivative(string key, char md)
{
	T p1;
	p1 = current->Find(key);
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
	T p1;
		p1 = current->Find(key);
	T res = p1.integral(md);
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Mult(string key1, string key2)
{
	T p1;
	T p2;
		p1 = current->Find(key1);
		p2 = current->Find(key2);
	T res = p1*p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Sum(string key1, string key2)
{
	T p1;
	T p2;
		p1 = current->Find(key1);
		p2 = current->Find(key2);
	T res = p1 + p2;
	std::cout << "res is " << res << endl;
	std::cout << "save res? 0-no 1-yes" << endl; int otv = 0;
	std::cin >> otv;
	if (otv) AddDialog(res);
	return res;
}

template<class T>
inline T Interf<T>::Dif(string key1, string key2)
{
	T p1;
	T p2;

		p1 = current->Find(key1);
		p2 = current->Find(key2);
	
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
	T p1;
	try {
		p1 = current->Find(key1);
	}
	catch (...) { std::cout << "cant find " << endl; return; }
	double res = p1.calculate(X, Y, Z);
	std::cout << "res is " << res << endl;
	return;
	
}
