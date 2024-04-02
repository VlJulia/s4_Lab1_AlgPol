#pragma once
#include <iostream>
#include <string>
#include "TNode.h"
using namespace std;

template<class T>
class TList
{
protected:
	TNode<T>* pStop= NULL; // значение указателя, означающего конец списка
	TNode<T>* pFirst=pStop; // первое звено
	TNode<T>* pCurrent = pStop; // текущее звено, всегда указывает на тот же обьект при изменении длины (кроме изменения себя)
	TNode<T>* pPrevious=pStop; // звено перед текущим
	TNode<T>* pLast=pStop; // последнее звено
	int length=0; // количество звеньев в списке

public:

	TList();
	~TList();
	int GetLength() { return length; }
	bool IsEmpty(); // список пуст ?
	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertCurrent(T item); // перед текущим 
	void InsertLast(T item);  // вставить последним 

	// удаление звеньев
	//void Clear();
	void DeleteFirst();// удалить первое звено 
	void DeleteCurrent(); // удалить текущее звено

	void GoNext(); // сдвиг вправо текущего звена
	// (=1 после применения GoNext для последнего звена списка)

	void Reset(); // установить на начало списка
	bool IsEnd();  // список завершен ?

	T GetCurrentItem();
	void SetCurrentItem(T item) { pCurrent->value = item; }
	void Clear();

	TList<T>& operator=(TList<T>& other);

	friend ostream& operator<<(ostream& os, const TList<T>& obj) {
		//os << &obj;
		if (obj.length == 0) { 
			//os << "length = 0 \n[\n]" << endl;
			return os; }
		//os << "length = " << obj.length << endl;
		//try { os << "first = " << obj.pFirst->value << endl; } catch (...) { os << "no first" << endl; }
		//try { os << "last = " << obj.pLast->value << endl; } catch (...) { os << "no last" << endl; }
		TNode<T>* tmp = obj.pFirst;
		//os << "[" << endl;
		
		for(int i=0;i<obj.length;i++)
		{

			if (tmp->value.coef>=0)os << "+";
			os << tmp->value;// << " next" << tmp->pNext;
			//if (tmp == obj.pCurrent) os << "<-- current";
			//if (tmp == obj.pPrevious) os << "<-- pr";
			os << " ";
			tmp = tmp->pNext;
		}
		
		//os << "]" << endl;
		return os;
	}

};

//*p - данные по ссылке int*p
//&p - ссфлка на данные int p
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
	//std::cout<<" ---- " << this;
	if (length == 0) throw "NOElem";
	if (pCurrent == pStop) throw "IsEnd";
	//std::cout << pCurrent << "ddd2" << endl;
	return pCurrent->value;
}

template<class T>
TList<T>& TList<T>::operator=(TList<T>& other)
{
	Clear();
	if (other.IsEmpty()) { return *this; }
	TNode<T>* tmp = other.pFirst;
	for (int i = 0; i < other.length; i++) {
		InsertLast(tmp->value);
		if (other.pCurrent == tmp) pCurrent = pLast;
		if (other.pPrevious == tmp) pPrevious = pLast;
		tmp = tmp->pNext;
	}
	return *this;
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

template <class T>
void TList<T>::Clear() {
	Reset();
	while (length > 0) { DeleteFirst(); }
	pCurrent = pStop; pPrevious = pStop; pLast = pStop;
	pFirst = pStop;
	length = 0;
}





