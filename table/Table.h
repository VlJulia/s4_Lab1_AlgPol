#pragma once
#include <iostream>
using namespace std;

template <class T>
struct  TRec//trec
{
	T value; //polinom
	string key; //name

	TRec& operator=(TRec &other) {
		key = other.key;
		value = other.value;
		return *this;
	}

	bool operator==(TRec other) { return (key == other.key); }
	friend std::ostream& operator<<(std::ostream& os, TRec& p)
	{
		os << " Key: " << p.key <<  " val: " << p.value;
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
	virtual bool Insert(string key, T obj)=0;
	virtual bool Delete(std::string key)=0;
	virtual T Find(std::string key)=0;
	virtual bool Exist(std::string key)=0;

public:
	friend std::ostream& operator<<(std::ostream& os, Table& tab)
	{
		std::cout << "Table printing" << endl;
		if (tab.IsEmpty()) {
			return os;
		}
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			//std::cout << tab.GetValuePtr()<<endl;
			os << tab.GetKey()<<" " << tab.GetValuePtr() << endl;
			//std::cout << "end "<< tab.IsTabEnded();
		}

		if (!(tab.IsEmpty())) os << tab.GetKey() << " " << tab.GetValuePtr() << endl;
		return os;
	}
};
template <class T>
int Table<T>::GetDataCount() const {
	return size;
};
template <class T>
bool Table<T>::IsEmpty() const {
	return (size == 0);
}
template<class T>
bool Table<T>::IsFull() const
{
	return max_data_count==size ;
}
