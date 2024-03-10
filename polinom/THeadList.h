#pragma once
#include "TList.h"
using namespace std;


template<class T>
class THeadList : public TList<T>
{
protected:
	TNode<T>* pHead;  // заголовок, pFirst - звено за pHead
public:
	THeadList();
	~THeadList<T>()
	{
		this->TList<T>::~TList<T>();
		pHead = NULL;
	}
	void InsertFirst(T item); // вставка звеньев после заголовка
	void InsertLast(T item);
	void InsertCurrent(T item); // перед текущим 
	void DeleteFirst(); // удалить первое звено
	void DeleteCurrent() {
		TList<T>::DeleteCurrent();
		if (TList<T>::pFirst == TList<T>::pCurrent) TList<T>::pPrevious = TList<T>::pLast;

	}
	void GoNext();
	void Reset();
	void Clear();

};
template <class T>
void THeadList<T>::Clear() {
	//std::cout << "Clear   " << *this;
	Reset();
	while (TList<T>::length > 0) { DeleteFirst(); }
	TList<T>::pCurrent = TList<T>::pStop; TList<T>::pPrevious =  pHead; TList<T>::pLast = TList<T>::pStop;
	TList<T>::pFirst = TList<T>::pStop;
	//std::cout << "Clear END  " << *this;
	TList<T>::length = 0;
}

template<class T>
THeadList<T>::THeadList() :TList<T>()
{
	pHead = new TNode<T>();
	pHead->pNext = TList<T>::pFirst;
}

template<class T>
void THeadList<T>::Reset()
{
	TList<T>::Reset();
	if (pHead == nullptr) {
		pHead = new TNode<T>();
		pHead->pNext = TList<T>::pFirst;
	}
	TList<T>::pPrevious = pHead;
}
template<class T>
void THeadList<T>::GoNext()
{
	if (TList<T>::IsEnd()) {
		TList<T>::pCurrent = TList<T>::pFirst;
		TList<T>::pPrevious = pHead;
		return;
	}
	TList<T>::pCurrent = TList<T>::pCurrent->pNext;
	TList<T>::pPrevious = TList<T>::pPrevious->pNext;

}

template <class T>
void THeadList<T>::InsertFirst(T item)
{

	TList<T>::InsertFirst(item);
	if (TList<T>::length == 1) TList<T>::pLast->pNext = pHead;
	pHead->pNext = TList<T>::pFirst;
	if (TList<T>::pCurrent == TList<T>::pFirst) TList<T>::pPrevious = pHead;
}

template <class T>
void THeadList<T>::DeleteFirst()
{
	TList<T>::DeleteFirst();
	if (TList<T>::length != 0) pHead = TList<T>::pFirst;
	else pHead = nullptr;
}

template <class T>
void THeadList<T>::InsertLast(T item)
{
	TList<T>::InsertLast(item);
	TList<T>::pLast->pNext = pHead;
}

template <class T>
void THeadList<T>::InsertCurrent(T item) {
	TList<T>::InsertCurrent(item);
	pHead->pNext = TList<T>::pFirst;

}; // перед текущим 
