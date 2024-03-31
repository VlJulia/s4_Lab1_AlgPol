#pragma once
#include "unorderedArrayTable.h"
template <class T>
class orderedArrayTable :public unorderedArrayTable<T>
{
public:
	bool Insert(string key, T obj);
	unorderedArrayTable::unorderedArrayTable;
};
template<class T>
bool orderedArrayTable<T>::Insert(string key, T obj) {
	if (size == max_data_count) { throw("Overflow"); return false;}

	for (int i = 0; i < max_data_count; i++) {
		if (data[i].key == key) {
			data[i].value = obj;			
			return true;
		}
	}

	int i = 0;
	for (i=0; i < max_data_count; i++) {
		if (data[i].key > key) { break; };
	}
	if (i == max_data_count) { for (i = 0; i < max_data_count; i++)if (data[i].key == std::string())break; }
	if (data[i].key == std::string()) {
		data[i].key = key;
		data[i].value = obj;
		size++;
		return true;
	}
	if (pushpull(i, 1)) {

		data[i].key = key;
		data[i].value = obj;
		size++;
		return true;
	}
	return false;
};