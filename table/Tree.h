#include <iostream>
#include "Table.h"
#include "..\polinom\TPolinom.h"

template <class T>
struct TrNode
{
	TrNode* RTrnode = NULL;
	TrNode* LTrnode = NULL;
	TrNode* UTrnode = NULL;

	T val;
	int high = -1;

};

template<class T>
class Tree:public Table<T>
{
// public:
	TrNode<T>* radix = NULL;
	TrNode<T>* Previous = NULL;
	TrNode<T>* Current = NULL;
	TrNode<T>* Last = NULL;
	TrNode<T>* First = NULL;
		//вместо вставки просто add

public:
	Tree(int m=0) { 
		max_data_count = m; 
	};
	Tree(Tree& other) {};
	~Tree() {
	};
	Tree operator=(Tree other) {};


	int Reset(void); // установить на первую запись
	int IsTabEnded(void) const; // таблица завершена?
	int GoNext(void) ; // переход к следующей записи
	std::string GetKey(void) const ;
	 T GetValuePtr(void) const ;
	//
	 bool Add(T obj) ;
	 bool Delete(std::string key) ;
	 T Find(std::string key);
	 bool Exist(std::string key) ;

private:
	TrNode<T>* newTrNode(T obj, int h =0) ;
	void GoDownLeft();
	int FPCLCheck(TrNode<T>* tmp);
};

template<class T>
TrNode<T>* Tree<T>::newTrNode(T obj, int h) {
	TrNode<T>* nn = new TrNode<T>;
	nn->high = h;
	nn->val = obj;
	return nn;
};

template<class T>
int Tree<T>::Reset(void) {
	if (First == NULL) return 0;
	Current = First;
	Previous = NULL;
	return 1;
}; // установить на первую запись

template<class T>
int Tree<T>::IsTabEnded(void) const {
	return Current == Last;
}; // таблица завершена?
template<class T>
void Tree<T>::GoDownLeft() {
	//if (Current ==NULL) std::cout<< Previous->val;
	while (!((Current->LTrnode == NULL) && (Current->RTrnode == NULL))) {
		if (Current->LTrnode != NULL) {
			Current = Current->LTrnode;
			continue;
		}
		if (Current->RTrnode != NULL) {
			if (Current->LTrnode == NULL) {
				//std::cout << Current->val;
				Previous = Current->UTrnode;
				return; }
			Current = Current->RTrnode;
			continue;
		}
	}
	Previous = NULL;
};

template<class T>
int Tree<T>::GoNext(void) 
{
	if (IsEmpty()) throw "is empty";
	if (IsTabEnded()) {
		Reset();
		return 1;
	}
	//if (Previous!=NULL) std::cout << "Prev is " << Previous->val<<"      ";
	//else std::cout << "Prev is  NULL      ";
	if (Current == radix) {
		Current = Current->RTrnode;
		GoDownLeft();
		return 1;
	}
	if (Previous == NULL) {//это лист 
		Previous = Current;
		Current = Current->UTrnode;
		if (Previous == Current->RTrnode) {
			Previous = Current;
			Current = Current->UTrnode;
		}
		return 1;
	}
	if ((Previous == Current->LTrnode)||(Previous == Current->UTrnode)) { // вышли с левой ветки
		Previous = Current;
		Current = Current->RTrnode;
		GoDownLeft();
		return 1;
	}
	if (Current == Current->UTrnode->RTrnode) {//вышли с правой ветки, надо пройти 2 шага
		Previous = Current;
		Current = Current->UTrnode;
		Previous = Current;
		Current = Current->UTrnode;
		return 1;
	}

	return 0;
}; // переход к следующей записи

template<class T>
std::string Tree<T>::GetKey(void) const {
	if (!IsEmpty()) return Current->val.name;
	throw "is empty";
};

template<class T>
T Tree<T>::GetValuePtr(void) const {
	if (!IsEmpty()) return Current->val;
	throw "is empty";
};

template<class T>
bool Tree<T>::Add(T obj) {
	if (IsFull()) { 
		throw "is full";
		return false; }
	if (radix == NULL) {
		radix = newTrNode(obj, 0);
		First = radix;
		Last = radix;
		Current = radix;
		/*std::cout << "First is " << First->val << endl;
		std::cout << "radix is "<<radix->val << endl;*/
		size++;
		return true;
	}
	else {
		TrNode<T>* tmp = radix;
		int h = 0;
		bool l_flag = 1, r_flag = 1;

		while (true) {
			// right way
			if (obj.name > tmp->val.name) {
				if (tmp->RTrnode != NULL) {
					tmp = tmp->RTrnode;
					h++;
					l_flag = 0;
					continue;
				}
				tmp->RTrnode = newTrNode(obj, h);
				tmp->RTrnode->UTrnode = tmp;
				size++;
				if (r_flag) Last = tmp->RTrnode;

				//std::cout <<"UP is "<< tmp->RTrnode->UTrnode->val << endl;

				return true;
			}
			//left way
			if (obj.name < tmp->val.name) {
				if (tmp->LTrnode != NULL) {
					tmp = tmp->LTrnode;
					h++;
					r_flag = 0;
					continue;
				}
				tmp->LTrnode = newTrNode(obj, h);
				tmp->LTrnode->UTrnode = tmp;
				size++;
				if (l_flag) First = tmp->LTrnode;

				//std::cout << "UP is " << tmp->LTrnode->UTrnode->val << endl;


				return true;
			}
			if (obj.name == tmp->val.name) {
				tmp->val = obj;
				return false;
			}

		}
	}
};
template<class T>
int Tree<T>::FPCLCheck(TrNode<T>* tmp) {
	TrNode<T>* a; int p;
	//std::cout << "was radix is " << radix->val  << endl;
	if (tmp->UTrnode != NULL) { a = tmp->UTrnode; p = 0; }
	else if (tmp->LTrnode != NULL) { a = tmp->LTrnode; p = 1; }
	else if (tmp->RTrnode != NULL) {a = tmp->RTrnode; p = 2;}
	if (First == tmp) { 
		if (tmp->RTrnode != NULL) { First = tmp->RTrnode; while (First->LTrnode != NULL) First = First->LTrnode; }
		else if (tmp->UTrnode != NULL) First = tmp->UTrnode;
	}
	if (Last == tmp)  Last = a; 
	if (Previous == tmp) Previous = a;
	if (Current == tmp) Current = a;
	if (radix == tmp)  radix = a; 
	
	//std::cout << "now radix is " << radix->val<<endl<<"  a is "<<a->val<<"  p is"<< p<<endl<<"tmp  "<<tmp->val<<endl;
	return p;

};

template<class T>
bool Tree<T>::Delete(std::string key) {
	if (radix == NULL)	return false;
	TrNode<T>* tmp = radix;
	while (true) {
		//std::cout << tmp->val<<endl;
		if (key == tmp->val.name) {
			if ((tmp->LTrnode==NULL)&&(tmp->RTrnode == NULL)) {
				FPCLCheck(tmp);
				delete tmp;
				size--;
				return 1;
			}
			if (tmp->LTrnode == NULL) {
				if (FPCLCheck(tmp) == 0) {
					if (tmp->UTrnode->LTrnode == tmp) tmp->UTrnode->LTrnode = tmp->RTrnode;
					else tmp->UTrnode->RTrnode = tmp->RTrnode;
				}
				tmp->RTrnode->UTrnode = tmp->UTrnode;
				size--;
				delete tmp;
				return 1;
			}
			if (tmp->RTrnode == NULL) {
				if (FPCLCheck(tmp) == 0) {
					if (tmp->UTrnode->LTrnode == tmp) tmp->UTrnode->LTrnode = tmp->LTrnode;
					else tmp->UTrnode->RTrnode = tmp->LTrnode;
				}
					tmp->LTrnode->UTrnode = tmp->UTrnode;
				delete tmp;
				size--;
				return 1;
			}
			TrNode<T>* tmp2 = tmp->LTrnode;
			size--;
			while (tmp2->RTrnode != NULL) tmp2 = tmp2->RTrnode;
			FPCLCheck(tmp2);
			tmp->val = tmp2->val;
			if (tmp->LTrnode == tmp2) {
				tmp->LTrnode = tmp2->LTrnode;
				delete tmp2;
				return 1;
			}
			if (tmp2->LTrnode != NULL) {
				tmp2->UTrnode->RTrnode = tmp2->LTrnode;
				tmp2->LTrnode->UTrnode = tmp2->UTrnode;
			}
			delete tmp2;
			return 1;
		}
		// right way
		if (key > tmp->val.name) {
			tmp = tmp->RTrnode;
			continue;
		}
		//left way
		if (key < tmp->val.name) {
			tmp = tmp->LTrnode;
			continue;
		}
		if ((tmp->LTrnode == NULL) && (tmp->RTrnode == NULL)) return 0;
	}
};;

template<class T>
T Tree<T>::Find(std::string key) {
	if (radix == NULL)	throw "is empty";
	else {
		TrNode<T>* tmp = radix;
		while (true) {
			// right way
			if (tmp == NULL) throw "is empty";
			if (key > tmp->val.name) {
				tmp = radix->RTrnode;
				continue;
			}
			//left way
			if (key < tmp->val.name) {
				tmp = radix->LTrnode;
				continue;
			}
			if (key == tmp->val.name) {
				return tmp->val;
			}
		}
	}
};

template<class T>
bool Tree<T>::Exist(std::string key) {
	if (radix == NULL)	return false;
	else {
		TrNode<T>* tmp = radix;
		while (true) {
			// right way
			if (tmp == NULL) return false;
			if (key > tmp->val.name) {
				tmp = radix->RTrnode;
				continue;
			}
			//left way
			if (key < tmp->val.name) {
				tmp = radix->LTrnode;
				continue;
			}
			if (key == tmp->val.name) {
				return true;
			}
		}
	}
};



/*
bool Tree::AddPolinom(Polinom<string,TPolinom> pol) {
	if (radix == NULL) {
		radix = newTrNode(pol, 0);
		return true;
	}
	else {
		TrNode* tmp = radix;
		int h = 0;
		while (true) {
			// right way
			if (pol.name > tmp->pol.name) {
				if (tmp->RTrnode != NULL) {
					tmp = radix->RTrnode;
					h++;
					continue;
				}
				tmp->RTrnode = newTrNode(pol, h);
				return true;
			}
			//left way
			if (pol.name < tmp->pol.name) {
				if (tmp->LTrnode != NULL) {
					tmp = radix->LTrnode;
					h++;
					continue;
				}
				tmp->LTrnode = newTrNode(pol, h);
				size++;
				return true;
			}
			if (pol.name == tmp->pol.name) {
				tmp->pol = pol;
				return false;
			}
		
		}
	}

};
bool Tree::PolinomExist(string polinom_name) {
	if (radix == NULL)	return false;
	else {
		TrNode* tmp = radix;
		while (true) {
			// right way
			if (tmp == NULL) return false;
			if (polinom_name > tmp->pol.name) {
					tmp = radix->RTrnode;
					continue;
			}
			//left way
			if (polinom_name < tmp->pol.name) {
					tmp = radix->LTrnode;
					continue;
			}
			if (polinom_name == tmp->pol.name) {
				return true;
			}
		}
	}
};
bool Tree::DelPolinom(string polinom_name) {
	if (radix == NULL)	return false;
	else {
		TrNode* PrevNode = NULL;
		TrNode* tmp = radix;
		while (true) {
			if (tmp == NULL) return false;
			if (polinom_name == tmp->pol.name) {
				if (PrevNode == NULL) {
					radix = NULL;
					size--;
					delete tmp;
					return true;
				}
				if (PrevNode->pol.name > polinom_name) {
					PrevNode->LTrnode = NULL;
					size--;
					delete tmp;
					return true;
				}
				if (PrevNode->pol.name < polinom_name) {
					PrevNode->RTrnode = NULL;
					size--;
					delete tmp;
					return true;
				}
			}
			// right way
			PrevNode = tmp;
			if (polinom_name > tmp->pol.name) {
				tmp = radix->RTrnode;
				continue;
			}
			//left way
			if (polinom_name < tmp->pol.name) {
				tmp = radix->LTrnode;
				continue;
			}
		}
	}
};

Polinom<string, TPolinom>* Tree::FindPolinom(string polinom_name) {
	if (radix == NULL)	return nullptr;
	else {
		TrNode* tmp = radix;
		while (true) {
			// right way
			if (tmp == NULL) return nullptr;
			if (polinom_name > tmp->pol.name) {
				tmp = radix->RTrnode;
				continue;
			}
			//left way
			if (polinom_name < tmp->pol.name) {
				tmp = radix->LTrnode;
				continue;
			}
			if (polinom_name == tmp->pol.name) {
				return &tmp->pol;
			}
		}
	}
};
*/