#pragma once
#include <iostream>
#include "Table.h"

template <class T>
struct HsNode
{
	HsNode<T>* Next = nullptr;
	TRec<T> val;
};

template <class T>
struct HsNodeU
{
	HsNode<T>* u = nullptr;
	int id = -1;
};


template<class T>
class HashTblCh :public Table<T> {
	unsigned int idcount = 1;
	HsNode<T>** id_tbl;
	HsNodeU<T> Current;
	HsNodeU<T> Last;
	HsNodeU<T> First;
public:

	HashTblCh(unsigned int idcount = 1) {
		if (idcount == 0) throw "zero size";
		id_tbl = new HsNode<T>*[idcount];
		Current.u = nullptr;
		First.u = nullptr;
		Last.u = nullptr;
		for (int i = 0; i < (int)idcount; i++) {
			id_tbl[i] = nullptr;
		}
		size = 0;
	}
	//~HashTblCh();
	bool IsFull() const;                       // заполнена?
	//навигация 
	int Reset(void); // установить на первую запись
	int IsTabEnded(void) const ; // таблица завершена?
	int GoNext(void); // переход к следующей записи
	std::string GetKey(void) const;
	T GetValuePtr(void) const ;
	//
	bool Insert(string key, T obj) ;
	bool Delete(std::string key) ;
	T Find(std::string key) ;
	bool Exist(std::string key);
	HashTblCh<T>& operator=( HashTblCh<T>& other);
	bool operator==(HashTblCh<T>& other);


private:
	int HashFunc(std::string key) {
		int s = 0;
		for (char i : key) s += (int)i;
		return (s % idcount);
	}
	int NewLast();
	int NewFirst();
};
template<class T>
int HashTblCh<T>::NewLast() {
	if (size - 1 > 0) {
		int nid = Last.id;
		HsNode<T>* tmp = id_tbl[nid];

		while ((nid != -1) && (tmp == nullptr) && (tmp == Last.u)) nid--;
		if (tmp == nullptr) { Last.u = nullptr; First.u = nullptr; Current.u = nullptr; size = 0; return 0; }
		while ((tmp->Next != nullptr) && (tmp->Next != Last.u)) tmp = tmp->Next;
		if (Current.u == Last.u) Reset();
		Last.u = tmp;
		Last.id = nid;

		return 1;
	}
	return 0;
}
template<class T>
int HashTblCh<T>::NewFirst() {
	if (size - 1 > 0) {
		int nid = First.id;
		HsNode<T>* tmp = First.u->Next;
		while ((tmp != Last.u) && (tmp == nullptr)) tmp = id_tbl[++nid];
		if (tmp == nullptr) { Last.u = nullptr; First.u = nullptr; Current.u = nullptr; size = 0; return 0; }
		if (Current.u == First.u) { Current.id = First.id; Current.u = First.u; }
		First.u = tmp;
		First.id = nid;
		return 1;
	}
	return 0;
}
template<class T>
bool HashTblCh<T>::IsFull() const
{
	for (int i = 0; i < idcount; i++) if (id_tbl[i] == nullptr) return false;
	return true;
}

template<class T>
int HashTblCh<T>::Reset(void)
{
	if (idcount == 0) return 0;
	Current.id = First.id;
	Current.u = First.u;
	return 1;
}

template<class T>
int HashTblCh<T>::IsTabEnded(void) const
{
	return (Current.u==Last.u);
}

template<class T>
int HashTblCh<T>::GoNext(void)
{
	if (IsEmpty()) throw "is empty";
	if (Current.u == Last.u) { Reset(); return 1; }
	if (Current.u == nullptr) Reset();
	Current.u = Current.u->Next;
	int i = Current.id;
	while ((Current.u == nullptr) && (Current.id != Last.id)) {
		Current.u = id_tbl[++i];
		Current.id = i;
	}
	return 1;
}

template<class T>
std::string HashTblCh<T>::GetKey(void) const
{
	return Current.u->val.key;
}

template<class T>
T HashTblCh<T>::GetValuePtr(void) const
{
	return Current.u->val.value;
}

template<class T>
bool HashTblCh<T>::Insert(string key, T obj)
{
	TRec<T> nr; nr.key = key; nr.value = obj;
	int id = HashFunc(key);
	HsNode<T>* nNode= new HsNode<T>;
	nNode->val = nr;
	nNode->Next = nullptr;
	if (First.u == nullptr) { First.id = id; First.u = nNode; }
	if (id_tbl[id] == nullptr) id_tbl[id] = nNode;
	else {
		HsNode<T>* tmp = id_tbl[id];
		while ((tmp->Next != nullptr)&&(tmp->val.key!=key)) tmp = tmp->Next;
		if (tmp->val.key == key) { tmp->val = nr; delete nNode; return 0; }
		tmp->Next = nNode;
	}
	if ((id >= Last.id)||(Last.u==nullptr)) { Last.id = id; Last.u = nNode; }
	if (id < First.id) { First.id = id; First.u = nNode; }
	size++;
	return 1;
}

template<class T>
bool HashTblCh<T>::Delete(std::string key)
{
	int id = HashFunc(key);
	if (id_tbl[id] == nullptr) return 0;
	else {
		HsNode<T>* tmp = id_tbl[id];
		HsNode<T>* tmp2 = nullptr;
		while (!((tmp->Next == nullptr) || (tmp->Next->val.key == key))) { tmp = tmp->Next;}

		if ((tmp->Next!= nullptr)||(tmp->Next->val.key==key)) { 
			if (Last.u == tmp->Next) NewLast();
			if (First.u == tmp->Next) NewFirst();
			if (tmp->Next != nullptr) tmp2 = tmp->Next->Next;
			delete tmp->Next;
			tmp->Next = tmp2;
			size--;
			return 1;
		}
	}
	return 0;
}

template<class T>
T HashTblCh<T>::Find(std::string key)
{
	int id = HashFunc(key);
	HsNode<T>* tmp = id_tbl[id];
	while (!((tmp->Next== nullptr)||(tmp->val.key==key))) tmp = tmp->Next;
	if (tmp->val.key != key) throw "cant find";
	return tmp->val.value;
}

template<class T>
bool HashTblCh<T>::Exist(std::string key)
{
	int id = HashFunc(key);
	HsNode<T>* tmp = id_tbl[id];
	while (!((tmp->Next == nullptr) || (tmp->val.key != key))) tmp = tmp->Next;
	if (tmp->val.key != key) return 0;
	return 1;
}

template<class T>
HashTblCh<T>& HashTblCh<T>::operator=( HashTblCh<T>& other) {
	std::cout << "\n\n\n   BIGIN   " << endl;
	if (this == &other) {	return *this;}
	if (*this == other) { return *this; }
	if (this == nullptr) { return *this; }

	if (other.id_tbl != nullptr) {

		for (int i=0;i<other.idcount;i++)
			if (other.id_tbl[i] != nullptr) {
				HsNode<T>* tmp = other.id_tbl[i];
				tmp->Next = nullptr;
				HsNode<T>* tmp2 = other.id_tbl[i];
				while (tmp != nullptr) {
					tmp2 = tmp->Next;
					delete tmp;
					tmp = tmp2;
				}

			}
	
	}
	delete other.id_tbl;
	other.id_tbl = new HsNode<T>*[idcount];

	other.idcount = idcount; other.size = 0;
	for (int i = 0; i < idcount; i++)
		if (id_tbl[i] != nullptr) {
			HsNode<T>* t = id_tbl[i];

			while (t!= nullptr) { 
				other.Add(t->val);
				t = t->Next;
			}
		}
		else other.id_tbl[i] = nullptr;

	std::cout << "other  " << other << endl;
	std::cout << "this  " << *this << endl;
	return *this;
};

template<class T>
bool HashTblCh<T>::operator==(HashTblCh<T>& other) {
	if (idcount != other.idcount) return false;
	if (size != other.size) return false;
	if (!(First.u->val == other.First.u->val)) return false;
	if (!(Last.u->val == other.Last.u->val)) return false;

	for (int i = 0; i < idcount; i++)
		if (id_tbl[i] != nullptr) {
			HsNode<T>* t = id_tbl[i];
			HsNode<T>* t2 = other.id_tbl[i];

			while (t!= nullptr) {
				if (!(t->val == t2->val)) return false;
				t = t->Next; t2 = t2->Next;
			}
		}
		else if (other.id_tbl[i] != nullptr) return false;
	return true;
};
//
//template<class T>
//HashTblCh<T>::~HashTblCh()
//{
//	Reset();
//	int b = First.id, e = Last.id;
//	if ((id_tbl != nullptr)&&(size!=0)) {
//		for (int i = b; (i <= e) && (size != 0); i++)
//			if (id_tbl[i] != nullptr) {
//				HsNode<T>* tmp = id_tbl[i];
//				HsNode<T>* tmp2 = id_tbl[i];
//
//					while ((tmp != nullptr) && (size != 0)) {
//						tmp2 = tmp;
//						tmp = tmp->Next;
//						delete tmp2;
//						size--;
//					}
//
//			}
//		delete id_tbl;
//	}
//
//}