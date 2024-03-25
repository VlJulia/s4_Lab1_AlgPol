#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"

template <class Tn, class Tp>
struct  Polinom//trec
{
	Tn name;
	Tp polinom;

	friend ostream& operator<<(ostream& os, Polinom& p)
	{
		os << " Key: " << p.name << " val: " << p.polinom;
		return os;
	}

};

template <class T>
class Table
{
protected: unsigned int size=0;//текущий размер
		 unsigned int max_data_count = 0;//сколько всего может быть записей
public:
	int GetDataCount()   const; // количество записей
	bool IsEmpty() const;  // пуста?
	bool IsFull() const;                       // заполнена?
	//навигация 
	virtual int Reset(void) = 0; // установить на первую запись
	virtual int IsTabEnded(void) const = 0; // таблица завершена?
	virtual int GoNext(void) = 0; // переход к следующей записи
	virtual std::string GetKey(void) const = 0;
	virtual T GetValuePtr(void) const = 0;
	//
	virtual bool Add(T obj)=0;
	virtual bool Delete(std::string key)=0;
	virtual T Find(std::string key)=0;
	virtual bool Exist(std::string key)=0;

public:
	friend ostream& operator<<(ostream& os, Table& tab)
	{
		cout << "Table printing" << endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			//std::cout << tab.GetValuePtr()<<endl;
			os << tab.GetValuePtr() << endl;
		}
		if (!(tab.IsEmpty())) os << tab.GetValuePtr() << endl;
		return os;
	}
};
template <class T>
int Table<T>::GetDataCount() const {
	return size;
};
template <class T>
bool Table<T>::IsEmpty() const {
	return size == 0;
}
template<class T>
bool Table<T>::IsFull() const
{
	return max_data_count==size ;
}
