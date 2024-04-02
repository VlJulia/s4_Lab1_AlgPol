#pragma once


template<class T>
struct TNode
{
	T value;
	TNode* pNext;
	void copy(TNode<T>* other) {
		value = other->value;
		pNext = other->pNext;
	}

};

