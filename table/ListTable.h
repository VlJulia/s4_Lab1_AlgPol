#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"
#include "..\table\Table.h"
using namespace std;

template <class T>
struct Item {
	T info; //полином 
	Item* next=nullptr; // ссылка на следующий
};

template <class T>
class ListTable : public Table<T> {
protected:
	unsigned int size = 0;//текущий размер
	unsigned int max_data_count = 0;//сколько всего может быть записей

	Item* first = nullptr;
	Item* current = nullptr;
	Item* prev = nullptr;

public:
	int GetDataCount() const { return size }// количество записей
	bool IsFull() const {
			return true; // оно бесконечно
	}  // заполнена?
	
	   //навигация 
	int Reset(void) {
		current = first;
		prev = nullptr;
		return 0;
	}// установить на первую запись
	int IsTabEnded(void) { return current->next == nullptr } // таблица завершена?
	int GoNext(void) {
		if (size == 0) throw "size =0 ";
		prev = current;
		if (!IsTabEnded()) {
			current = current->next;
		}
		else Reset();
		return 1;
	} // переход к следующей записи
	string GetKey(void) {
		if (current != nullptr) {
			return current->info.name;
		}
		else {
			throw "Empty";
		}
	}
	T GetValuePtr(void) {
		if (current != nullptr) {
			return current->info;
		}
		else {
			throw "Empty";
		}
	}
	//

	bool Add(T obj) {//  T = Polinom     вставляем позади Current
		Item<T>* newItem = new Item<T>;
		newItem->info = obj;
		newItem->next = first;
		if (size == 0) { first = newItem; current = newItem; }
		else {
			bool b = Exist(obj.name);
			if (b) { delete newItem; return false; }
			else { 
				newItem->next = current;
				if (Current != first) {
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
	bool Delete(std::string key) {
		if (size == 0) return true;
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		if (tmp->info->name == key) {
			if ((tmp == current)|| (tmp == prev))  Reset();
			if (tmp == first) { 
				if (first == current) { GoNext(); prev = nullptr; }
			first = tmp->next; }
			tmp_w->next = tmp->next;
			delete tmp;
			size--;
		}
	}
	T Find(std::string key) {
		if (size == 0) throw "size=0";
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		if (tmp->info->name == key) return tmp->info;
		throw "cant find";
	}
	bool Exist(std::string key) {
		if (size == 0) return false;
		Item<T>* tmp = first;
		Item<T>* tmp_w = nullptr;
		while (tmp != nullptr && tmp->info->name != key) {
			tmp_w = tmp;
			tmp = tmp->next;
		}
		return (tmp->info->name == key);
	}

};
///*
//template <class T>
//int Table<T>::GetDataCount() const {
//	return size;
//};
//template <class T>
//bool Table<T>::IsEmpty() const {
//	return size == 0;
//}
//template<class T>
//bool Table<T>::IsFull() const
//{
//	return max_data_count == size;
//}
///*
//
//
//
//class ListTable : Table {
//	virtual void AddPolinom(Polinom<Tn, Tp> pol) {
//		Item* cur, * prev;
//		cur = ptab;
//		if (!cur) {
//			cur.info = pol;
//		}
//		while (cur->next) { /* есть другие элементы */
//			prev = cur;
//			cur = cur->next;
//		}
//		cur.info = pol;
//	}
//	virtual void DelPolinom(std::string polinom_name) {
//		Item* cur, * prev;
//		cur = ptab;
//		/* проверяем, есть ли в таблице элементы */
//		if (!cur)
//			return -1; /* таблица пуста – отказ */
//		/* возможно, требуется удалить первый элемент таблицы */
//		if (cur.info.name == polinom_name) {
//			/* удаляем первый элемент */
//			ptab = cur->next;
//			delete cur;
//			return 0;
//		}
//		/* ищем удаляемый элемент среди других элементов таблицы */
//		while (cur->next) { /* есть другие элементы */
//			prev = cur;
//			cur = cur->next;
//			if (cur.info.name == polinom_name) {
//				/* нашли элемент, который надо удалить */
//				prev->next = cur->next;
//				delete cur;
//				return 0;
//			}
//		}
//		/* естественный выход из цикла – в таблице нет элемента с ключом k */
//		return -1;
//	}
//	virtual Polinom<Tn, Tp> FindPolinom(std::string polinom_name) {
//		Item* cur, * prev;
//		cur = ptab;
//		/* проверяем, есть ли в таблице элементы */
//		if (!cur)
//			return -1; /* таблица пуста – отказ */
//		/* возможно, требуется удалить первый элемент таблицы */
//		if (cur.info.name == polinom_name) {
//			/* удаляем первый элемент */
//			ptab = cur->next;
//			delete cur;
//			return 0;
//		}
//		/* ищем удаляемый элемент среди других элементов таблицы */
//		while (cur->next) { /* есть другие элементы */
//			prev = cur;
//			cur = cur->next;
//			if (cur->key == k) {
//				/* нашли элемент, который надо удалить */
//				prev->next = cur->next;
//				delete cur;
//				return 0;
//			}
//		}
//		/* естественный выход из цикла – в таблице нет элемента с ключомk */
//		return -1;
//	}
//};
//
//int del1(int k) {
//	Item* cur, * prev;
//	cur = ptab;
//	/* проверяем, есть ли в таблице элементы */
//	if (!cur)
//		return -1; /* таблица пуста – отказ */
//	/* возможно, требуется удалить первый элемент таблицы */
//	if (cur->key == k) {
//		/* удаляем первый элемент */
//		ptab = cur->next;
//		delete cur;
//		return 0;
//	}
//	/* ищем удаляемый элемент среди других элементов таблицы */
//	while (cur->next) { /* есть другие элементы */
//		prev = cur;
//		cur = cur->next;
//		if (cur->key == k) {
//			/* нашли элемент, который надо удалить */
//			prev->next = cur->next;
//			delete cur;
//			return 0;
//		}
//	}
//	/* естественный выход из цикла – в таблице нет элемента с ключомk */
//	return -1;
//}
//
//
//int del2(int k) {
//	Item* cur, ** pptr;
//	pptr = &ptab; /* указатель на указатель на первый элемент таблицы */
//	/* ищем удаляемый элемент среди всех элементов таблицы */
//	while (*pptr) { /* еще есть элементы */
//		if ((*pptr)->key == k) {
//			/* нашли элемент, который надо удалить */
//			cur = *pptr; /* указатель на удаляемый элемент */
//			*pptr = cur->next;
//			Delete cur;
//			return 0;
//		}
//		/* продвигаемся к следующему элементу таблицы */
//		pptr = &(*pptr)->next;
//	}
//	/* естественный выход из цикла – в таблице нет элемента с ключомk */
//	return-1;
//}
//
//*/