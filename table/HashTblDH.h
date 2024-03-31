#pragma once
#include <iostream>
#include "Table.h"


template<class T>
class HashTblDH :public Table<T> {
	TRec<T>* WDel;
	TRec<T>** id_tbl;
	int first = -1,last = -1, current = -1;
public:

	HashTblDH(unsigned int idcount = 1) {
		if (idcount == 0) throw "zero size";
		max_data_count = idcount;
		id_tbl = new TRec<T>*[idcount];
		WDel = new TRec<T>();
		for (int i = 0; i < (int)idcount; i++) {
			id_tbl[i] = NULL;
		}
		size = 0;
	}


	HashTblDH(HashTblDH& other) {
		if (&other == nullptr) return;
		max_data_count = other.max_data_count;
		id_tbl = new TRec<T>*[max_data_count];
		first = other.first; last = other.last; current = other.current;
		for (int i = 0; i < max_data_count;i++) id_tbl[i] = other.id_tbl[i];
		size = other.size;
	}


	//~HashTblDH();
	bool IsFull() const;                       // заполнена?
	//навигация 
	int Reset(void); // установить на первую запись
	int IsTabEnded(void) const; // таблица завершена?
	int GoNext(void); // переход к следующей записи
	std::string GetKey(void) const;
	T GetValuePtr(void) const;
	//
	bool Insert(string key, T obj);                                
	bool Delete(std::string key);                                  
	T Find(std::string key);                                       
	bool Exist(std::string key);                                   
	HashTblDH<T>& operator=(HashTblDH<T>& other);
	bool operator==(HashTblDH<T>& other);


private:
	int HashFunc1(std::string key) {             //h(key)  h(key,i)
		int id = 0, id2 = -1, s = 0;
		for (char c : key) s += (int)c;
		int g = HashFunc2(s), i = 0;
		id = (s + (i++) * g) % max_data_count;
		int stop = id;
		while ((id_tbl[id] != NULL)&&(id_tbl[id]->key != key)&&(id)) {
			if ((id2 < 0) && (id_tbl[id] == WDel)) id2 = id;    //если нашли удаленную ячейку, то надо ее запомнить
			id = (s + (i++) * g) % max_data_count;
			if (id == stop) break;
		}
		if (((id_tbl[id] == NULL)||(id==stop))&& (id2 >= 0)) return id2; //если вышли не от того что нашли копию и нашли удаленную по пути
		return id;//если нашли копию или не нашли удаленных ячеек
	}
	int HashFunc2(int int_key) {                      //g(key) подаем уже посчитанную сумму char
		if (max_data_count < 2) return 1;
		return (1 + (int_key%(max_data_count-1)));
	}
	int NewLast();
	int NewFirst();
};
template<class T>
int HashTblDH<T>::NewLast() {
	if (size - 1 > 0) {
		last--;
		while ((last > first) && (id_tbl[last] == NULL || id_tbl[last] == WDel)) last--;
		return 1;
	}
	return 0;
}
template<class T>
int HashTblDH<T>::NewFirst() {
	if (size - 1 > 0) {
		first++;
		while ((first < last) && (id_tbl[first] == NULL || id_tbl[first] == WDel)) first++;
		return 1;
	}
	return 0;
}
template<class T>
bool HashTblDH<T>::IsFull() const
{
	return (size == max_data_count);
}

template<class T>
int HashTblDH<T>::Reset(void)
{
	if (first < 0) return 0;
	current = first;
	return 1;
}

template<class T>
int HashTblDH<T>::IsTabEnded(void) const
{
	if (last < 0) return true;
	return (current == last);
}

template<class T>
int HashTblDH<T>::GoNext(void)
{
	if (IsEmpty()) throw "is empty";
	current++;
	if (current > last) current = first;
	return 1;
}

template<class T>
std::string HashTblDH<T>::GetKey(void) const
{
	if (size == 0) throw "is empty";
	return id_tbl[current]->key;
}

template<class T>
T HashTblDH<T>::GetValuePtr(void) const
{
	if (size == 0) throw "is empty";
	return id_tbl[current]->value;
}

template<class T>
bool HashTblDH<T>::Insert(string key, T obj)
{
	if (IsFull()) throw "is full";
	int id = HashFunc1(key);
	if (size == 0) { first == id; last == id; current = id; }
	else {
		if ((first<0)||(id < first)) first = id;
		if (id > last) last = id;
	}
	TRec<T>* nn = new TRec<T>(); nn->key = key; nn->value = obj;
	if ((id_tbl[id] != NULL) && (id_tbl[id] != WDel)) { size--; delete id_tbl[id]; }
	id_tbl[id] = nn;
	size++;
	return 1;
}

template<class T>
bool HashTblDH<T>::Delete(std::string key)
{
	bool f = 0;
	int id = HashFunc1(key);
	if ((id_tbl[id] == NULL) || (id_tbl[id] == WDel)) return 0;
	if (id == first) NewFirst();
	if (id == last) { NewLast(); f = 1; }
	if (id == current) {
		if (size - 1 == 0) current = -1;
		else {
			current++;
			while ((id_tbl[current] == NULL) || (id_tbl[current] == WDel)) current = (current + 1) % max_data_count;
		}
	}
	delete id_tbl[id];
	id_tbl[id] = WDel;
	if (f) id_tbl[id] = NULL;
	size--;
	
}

template<class T>
T HashTblDH<T>::Find(std::string key)
{
	int id = HashFunc1(key);
	if ((id_tbl[id] == NULL) || (id_tbl[id] == WDel)) throw "cant find";
	return id_tbl[id]->value;
}

template<class T>
bool HashTblDH<T>::Exist(std::string key)
{
	int id = HashFunc1(key);
	return (!((id_tbl[id] == NULL) || (id_tbl[id] == WDel)));
}

template<class T>
HashTblDH<T>& HashTblDH<T>::operator=(HashTblDH<T>& other) {
	if (id_tbl != nullptr) { delete id_tbl; size = 0; current = -1; last = -1; first = -1; }
	if (other == nullptr) return *this;
	max_data_count = other.max_data_count;
	id_tbl = new TRec[max_data_count];
	first = other.first; last = other.last; current = other.current;
	for (int i = 0; i < max_data_count) id_tbl[i] = other.id_tbl[i];
	size = other.size;
	return *this;
};

template<class T>
bool HashTblDH<T>::operator==(HashTblDH<T>& other) {
	if (size != other.size|| first != other.first|| last!=other.last) return false;
	for (int i = 0; i < size; i++) {
		if ((id_tbl[i] == WDel) && (other.id_tbl[i] != other.WDel)) return false;
		if (id_tbl[i] != other.id_tbl[i]) return false;
	}
	return true;
};
