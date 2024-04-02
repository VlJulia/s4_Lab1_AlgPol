#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"
#include "..\table\Table.h"
using namespace std;

template <class T>
struct Item {
	TRec<T> info; //полином 
	Item* next=nullptr; // ссылка на следующий
};

template <class T>
class ListTable : public Table<T> {
protected:
	Item<T>* first = nullptr;
	Item<T>* current = nullptr;
	Item<T>* prev = nullptr;
public:
	ListTable(int _max_data_count = -1) { max_data_count = _max_data_count; }
	~ListTable() {
		Reset();
		while (size != 0) {
			Delete(GetKey());
		}
}
	ListTable(ListTable& other);
	int GetDataCount() const { return size; }// количество записей
	bool IsFull() const {
		return (max_data_count == size); // оно может быть бесконечно, в этом случае -1
	}  // заполнена?
	
	   //навигация 
	int Reset(void) {
		current = first;
		prev = nullptr;
		return 0;
	}// установить на первую запись
	int IsTabEnded(void) const { return (current==nullptr || current->next == nullptr); } // таблица завершена?
	int GoNext(void); // переход к следующей записи
	string GetKey(void) const;
	T GetValuePtr(void) const;
	
	bool Insert(string key, T obj);//  T      вставляем позади Current
	bool Delete(std::string key);
	T Find(std::string key);
	bool Exist(std::string key);

	ListTable<T> operator=(ListTable<T> other);
	bool operator==(ListTable<T>& other) const;

};

template<class T>
ListTable<T>::ListTable(ListTable& other)
{
	Reset();
	if (other.size == 0) return;
	Item<T>* tmp = other.first;
	first = new Item<T>;
	first->info = tmp->info;
	current = first;
	Item<T>* tmp2 = first;

	while (tmp->next!=nullptr) {
		tmp = tmp->next;
		tmp2->next = new Item<T>;
		tmp2->next->info = tmp->info;
		tmp2 = tmp2->next;
	}
}

template<class T>
int ListTable<T>::GoNext(void)
{
	if (size == 0) throw "size =0 ";
	prev = current;
	if (!IsTabEnded()) {
		current = current->next;
	}
	else Reset();
	return 1;
}

template<class T>
string ListTable<T>::GetKey(void) const
{
	if (current != nullptr) {
		return current->info.key;
	}
	else {
		throw "Empty";
	}
}

template<class T>
T ListTable<T>::GetValuePtr(void) const
{
	if (current != nullptr) {
		return current->info.value;
	}
	else {
		throw "Empty";
	}
}

template<class T>
bool ListTable<T>::Insert(string key, T obj)
{
	if (IsFull()) throw "is full";
	TRec<T> nr; nr.key = key; nr.value = obj;
	Item<T>* newItem = new Item<T>;
	newItem->info = nr;
	newItem->next = first;
	if (size == 0) {
		first = newItem;
		current = newItem;
		size++;
		return true;
	}
	else {
		bool b = Exist(key);
		if (b) { delete newItem;  return false; }
		else {
			newItem->next = current;
			if (current != first) {
				prev->next = newItem;
			}
			else {
				first = newItem;
			}
			prev = newItem;
		}
	}
	size++;
	return true;
}

template<class T>
bool ListTable<T>::Delete(std::string key)
{
	if (size == 0) return true;
	Item<T>* tmp = first;
	Item<T>* tmp_w = nullptr;
	while (tmp != nullptr && tmp->info.key != key) {
		tmp_w = tmp;
		tmp = tmp->next;
	}
	if (tmp == nullptr) return 0;
	if ((tmp == current) || (tmp == prev))  Reset();
	if (tmp == first) {
		if (first == current) { GoNext(); prev = nullptr; }
		first = tmp->next;
	}
	if (tmp_w != nullptr) tmp_w->next = tmp->next;
	delete tmp;
	size--;
}

template<class T>
T ListTable<T>::Find(std::string key)
{
	if (size == 0) throw "size=0";
	Item<T>* tmp = first;
	Item<T>* tmp_w = nullptr;
	while (tmp != nullptr && tmp->info.key != key) {
		tmp_w = tmp;
		tmp = tmp->next;
	}
	if (tmp->info.key == key) return tmp->info.value;
	throw "cant find";
}

template<class T>
bool ListTable<T>::Exist(std::string key)
{
	if (size == 0) return false;
	Item<T>* tmp = first;
	Item<T>* tmp_w = nullptr;
	while (tmp != nullptr && tmp->info.key != key) {
		tmp_w = tmp;
		tmp = tmp->next;
	}
	if (tmp == nullptr) return false;
	return (tmp->info.key == key);
}

template<class T>
ListTable<T> ListTable<T>::operator=(ListTable<T> other)
{
	Reset();
	while (size != 0) { Delete(GetKey()); }
	if (other.size == 0) return;
	Item<T>* tmp = other.first;
	while (size != other.size) {
		Insert(tmp->info.key, tmp->info.value);
		tmp = tmp->next;
	}
	return *this;
}

template<class T>
bool ListTable<T>::operator==(ListTable<T>& other) const
{
	if (size != other.size) return false;
	if (size == 0) return true;
	Item<T>* tmp = other.first;
	Item<T>* tmp2 = first;

	while (tmp != nullptr) {
		if (!(tmp->info == tmp2->info)) return false;
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	return true;
}
