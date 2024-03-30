#pragma once
#define PULL -1
#define PUSH 1
#include "Table.h"
template <class T>
class unorderedArrayTable : public Table<T>
{
protected: unsigned int size;//текущий размер
		 unsigned int max_data_count;//сколько всего может быть записей
		 unsigned int currentLine;
		 TRec<T>* data;
		 bool pushpull(int index, int mode);
public:
	unorderedArrayTable(int arraysize = 20);
	int GetDataCount() const; // количество записей
	bool IsEmpty() const;  // пуста?
	bool IsFull() const;  // заполнена?
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
};
template<class T>
bool unorderedArrayTable<T>::pushpull(int index, int mode) {//PUSH: перемещает элементы массива на единицу вперёд, начиная с элемента [index] до NULL; PULL: смещает все элементы массива, начиная с [index+1], на единицу назад, на место элемента [index] 

	if (index < 0 || index >= max_data_count)return false;
	if (mode == PUSH && !(size == max_data_count)) {
		int target = -1;
		for (int i = index; i < max_data_count - 1; i++) {
			if (data[i].key == std::string()) {
				target = i; break;
			}
		}
		if (target != -1) {
			for (int i = target; i > index; i--) {
				data[i].key = data[i - 1].key;
				data[i].value = data[i - 1].value;

			}
			data[index].key = std::string();
			return true;
		}
	}
	if (mode == PULL) {
		for (int i = index; i < max_data_count - 2; i++) {
			data[i].key = data[i + 1].key;
			data[i].value = data[i + 1].value;
		}
		data[max_data_count - 1].key = std::string();
		return true;
	}
	return false;
};
template<class T>
unorderedArrayTable<T>::unorderedArrayTable(int arraysize = 20) {
	data = new TRec<T>[arraysize];
	max_data_count = arraysize;
	size = 0;
	currentLine = 0;
	for (int i = 0; i < max_data_count; i++) {
		data[i].key = std::string();
	}
}
template<class T>
int unorderedArrayTable<T>::GetDataCount() const { return size; }
template<class T>
bool unorderedArrayTable<T>::IsEmpty() const { return (size == 0); }
template<class T>
bool unorderedArrayTable<T>::IsFull() const { return (size = max_data_count); };
template<class T>
int unorderedArrayTable<T>::Reset(void) { currentLine = 0; return 1; };
template<class T>
int unorderedArrayTable<T>::IsTabEnded(void) const { if (currentLine == max_data_count - 1)return 1; else return 0; };
template<class T>
int unorderedArrayTable<T>::GoNext(void) { if (currentLine == max_data_count - 1)return 0; else { currentLine++;  return 1; } };
template<class T>
std::string unorderedArrayTable<T>::GetKey(void) const { return data[currentLine].key; };
template<class T>
T unorderedArrayTable<T>::GetValuePtr(void) const { return data[currentLine].value; };
template<class T>
bool unorderedArrayTable<T>::Insert(string key, T obj) {
	if (size == max_data_count) { throw("Overflow"); return false; };
	for (int i = 0; i < max_data_count; i++) {
		if (data[i].key == key) {
			data[i].value = obj;
			return true;
		}
	}
	if (data[currentLine].key == std::string()) {
		data[currentLine].key = key;
		data[currentLine].value = obj;
		size = size + 1;
		return true;
	}
	if (pushpull(currentLine, PUSH)) {
		data[currentLine].key = key;
		data[currentLine].value = obj;
		size = size + 1;
		return true;
	}
	return false;
};
template<class T>
bool unorderedArrayTable<T>::Delete(std::string key) {
	for (int i = 0; i < max_data_count - 1; i++)
		if (data[i].key == key) {
			pushpull(i, PULL);
			size = size - 1;
			return true;
		}
	return false;
};
template<class T>
T unorderedArrayTable<T>::Find(std::string key) { for (int i = 0; i < max_data_count; i++) if (data[i].key == key) return data[i].value; throw("Nothing found"); };
template<class T>
bool unorderedArrayTable<T>::Exist(std::string key) { for (int i = 0; i < max_data_count; i++) if (data[i].key == key) return true; return false; };

