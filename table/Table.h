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
protected: unsigned int size=0;//������� ������
		 unsigned int max_data_count = 0;//������� ����� ����� ���� �������
public:
	int GetDataCount()   const; // ���������� �������
	bool IsEmpty() const;  // �����?
	bool IsFull() const;                       // ���������?
	//��������� 
	virtual int Reset(void) = 0; // ���������� �� ������ ������
	virtual int IsTabEnded(void) const = 0; // ������� ���������?
	virtual int GoNext(void) = 0; // ������� � ��������� ������
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
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			//std::cout << tab.GetValuePtr()<<endl;
			os << tab.GetKey()<<" " << tab.GetValuePtr() << endl;
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
