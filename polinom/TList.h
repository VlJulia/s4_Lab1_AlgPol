#pragma once
#include <iostream>
#include <string>
#include "TNode.h"
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pStop= NULL; // �������� ���������, ����������� ����� ������
	TNode<T>* pFirst=pStop; // ������ �����
	TNode<T>* pCurrent = pStop; // ������� �����, ������ ��������� �� ��� �� ������ ��� ��������� ����� (����� ��������� ����)
	TNode<T>* pPrevious=pStop; // ����� ����� �������
	TNode<T>* pLast=pStop; // ��������� �����
	int length=0; // ���������� ������� � ������

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // ������ ���� ?
	// ������� �������
	void InsertFirst(T item); // ����� ������
	void InsertCurrent(T item); // ����� ������� 
	void InsertLast(T item);  // �������� ��������� 

	// �������� �������
	//void Clear();
	void DeleteFirst();// ������� ������ ����� 
	void DeleteCurrent(); // ������� ������� �����

	void GoNext(); // ����� ������ �������� �����
	// (=1 ����� ���������� GoNext ��� ���������� ����� ������)

	void Reset(); // ���������� �� ������ ������
	bool IsEnd();  // ������ �������� ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }


	friend ostream& operator<<(ostream& os, const TList<T>& obj) {
		//os << &obj;
		if (obj.length == 0) { os << "length = 0 \n[\n]" << endl; return os; }
		try { os << "first = " << obj.pFirst->value << endl; } catch (...) { os << "no first" << endl; }
		try { os << "last = " << obj.pLast->value << endl; } catch (...) { os << "no last" << endl; }
		os << "length = " << obj.length << endl;
		TNode<T>* tmp = obj.pFirst;
		os << "[" << endl;
		for(int i=0;i<obj.length;i++)
		{

			os << tmp->value;// << " next" << tmp->pNext;
			if (tmp == obj.pCurrent) os << "<-- current";
			if (tmp == obj.pPrevious) os << "<-- pr";
			os << endl;
			tmp = tmp->pNext;
		}
		os << "]" << endl;
		return os;
	}

};

//*p - ������ �� ������ int*p
//&p - ������ �� ������ int p
template <class T>
TList<T>::TList()
{
	length = 0;
	pStop = NULL;
	pFirst = pStop;
	pPrevious = pStop;
	pLast = pStop;
}

template <class T>
TList<T>::~TList()
{
	//std::cout << *this;
	while ((length>0))
		DeleteFirst();

	pFirst=nullptr;
	pLast = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	//std::cout << "\nposle\n" << *this;
	

}

template <class T>
bool TList<T>::IsEmpty()
{
	if (length == 0) return true;
	return false;
}

template <class T>
void TList<T>::InsertFirst(T item)
{	
	if (length == 0) {
		TNode<T>* tmp = new TNode<T>();
		tmp->pNext = pStop;
		tmp->value = item;
		pFirst= tmp; 
		pCurrent = pFirst;
		pLast = pFirst;
	}
	else {
		TNode<T>* tmp= new TNode<T>();
		tmp->pNext = pFirst;
		tmp->value = item;
		if (pCurrent == pFirst) {pPrevious = tmp;}
		pFirst = tmp;
		tmp = nullptr;
	}
	length++;

}

template <class T>
void TList<T>::InsertLast(T item)
{
	if (IsEmpty()) { InsertFirst(item); return; }
	TNode<T>* tmp = new TNode<T>();
	tmp->pNext = pStop;
	tmp->value = item;
	pLast->pNext = tmp;
	pLast = tmp;
	tmp = nullptr;
	length++;
}
template <class T>
void TList<T>::InsertCurrent(T item)
{
	if (length == 0) {
		InsertFirst(item);
		return;
	}
	if (pCurrent == pFirst) { InsertFirst(item); return; }
	TNode<T>* tmp = pPrevious;
	pPrevious = new TNode<T>();
	pPrevious->value = item;
	pPrevious->pNext = pCurrent;
	tmp->pNext = pPrevious;
	length++;

}

template <class T>
void TList<T>::DeleteFirst()
{
	//std::cout << "delf\n";
	if (length == 0) throw "is Empty";
	try {
		if ((pFirst == NULL) || (pFirst == pStop))
			return;
	}
	catch (...) { return; }
	if(pCurrent == pFirst) pCurrent= pFirst->pNext;
	if (pLast == pFirst) pLast = pFirst->pNext;
	if (pPrevious == pFirst) pPrevious = pFirst->pNext;
	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	tmp = NULL;
	length--;


}

template <class T>
void TList<T>::DeleteCurrent()
{
	if (length == 0) throw "is Empty";

	if (pCurrent==pStop) throw "Currend in end";
	if ((pCurrent == pFirst)&&(length==1)) {
		DeleteFirst(); return; }
	if (pCurrent->pNext == pStop) {
		pLast->copy(pPrevious); 
		pLast->pNext = pStop;
		delete pCurrent;
		Reset();
		length--;
		return;
	
	}

	TNode<T>* tmp = pCurrent->pNext;
	pCurrent->pNext= tmp->pNext;
	pCurrent->value = tmp->value;
	//std::cout << pCurrent<<"ddd"<<endl;
	length--;
}

template <class T>
T TList<T>::GetCurrentItem()
{
	if (length == 0) throw "NOElem";
	if (pCurrent == pStop) throw "IsEnd";
	//std::cout << pCurrent << "ddd2" << endl;
	return pCurrent->value;
}

template <class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = NULL;
}

template <class T>
void TList<T>::GoNext()
{
	//std::cout << "sasaa" << *this << this << endl;
		if (IsEnd()) throw "is end";
		pPrevious = pCurrent;
		pCurrent = pCurrent->pNext;
}

template <class T>
bool TList<T>::IsEnd()
{
	if (length == 0) return true;
	if (IsEmpty()) return true;
	if (pCurrent == pLast) return true;
	if (pCurrent == pStop) return true;
	if (pCurrent->pNext == pStop) return true;
	return false;
}






