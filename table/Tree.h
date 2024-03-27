#pragma once
#include <iostream>
#include "Table.h"
template <class T>
struct TrNode
{
public:
	TrNode* RTrnode = NULL;
	TrNode* LTrnode = NULL;
	TrNode* UTrnode = NULL;

	T val;
	int h = 0;
	void newH() {
		int a = 0;
		if (RTrnode != NULL) a += RTrnode->h + 1;
		if ((LTrnode != NULL)&&(LTrnode->h+1>a)) a = LTrnode->h + 1;
		h = a;
	}

	int Add(T obj) {   //1 -новый уровень 0 -без нового уровня -1 -не добавился(уже есть)
		int a = 0;
		if (this->val.name < obj.name) {
			if (this->RTrnode != NULL) {
				a = this->RTrnode->Add(obj);
				if (a == 1) newH();
				return a;
			}
			else
			{
				this->RTrnode = new TrNode<T>;
				this->RTrnode->UTrnode = this;
				this->RTrnode->h = 0;
				this->RTrnode->val = obj;

				if (this->LTrnode == NULL) {
					newH();
					return 1;
				}
				return 0;
			}
		}
		if (this->val.name > obj.name) {
			if (this->LTrnode != NULL) {
				a = this->LTrnode->Add(obj);
				if (a == 1) newH();
				return a;
			}
			else
			{
				this->LTrnode = new TrNode<T>;
				this->LTrnode->UTrnode = this;
				this->LTrnode->h = 0;
				this->LTrnode->val = obj;

				if (this->RTrnode == NULL) {
					newH();
					return 1;
				}
				return 0;
			}
		}
		if (this->val.name == obj.name) {
			this->val = obj;
			return -1;
		}
	}

	void LeftRot() {
		TrNode* tmpC = RTrnode;
		if (tmpC == NULL) {
			return;
		}
		if (UTrnode != NULL) {
			tmpC->UTrnode = UTrnode;
			if (UTrnode->RTrnode = this) UTrnode->RTrnode = tmpC;
			else UTrnode->LTrnode = tmpC;
		}
		else {
			tmpC->UTrnode = NULL;
		}
		if (tmpC->LTrnode != NULL) {
			tmpC->LTrnode->UTrnode = this;
		}
			RTrnode = tmpC->LTrnode;

		tmpC->LTrnode = this;
		UTrnode = tmpC;
		newH();
	/*	std::cout << " L ROT " << val << "   u" << UTrnode->val << endl;
		std::cout << " L ROT " << (LTrnode == NULL) << "  - " << (RTrnode==NULL) << endl;*/
		//std::cout << " L ROT " << UTrnode->LTrnode->val << "   " << UTrnode->RTrnode->val << endl;
	};
	void RightRot() {
		TrNode* tmpB = LTrnode;
		if (tmpB == NULL) {
			return;
		}
		if (UTrnode != NULL) {
			tmpB->UTrnode = UTrnode;
			if (UTrnode->RTrnode = this) UTrnode->RTrnode = tmpB;
			else UTrnode->LTrnode = tmpB;
		}
		else {
			tmpB->UTrnode = NULL;
		}
		if (tmpB->RTrnode != NULL) {
			tmpB->RTrnode->UTrnode = this;
		}
			LTrnode = tmpB->RTrnode;
		tmpB->RTrnode = this;
		UTrnode = tmpB;
		newH();
	};
	int dh() {
		int t = 0;
		if ((RTrnode != NULL)) t += (RTrnode->h+1);
		if ((LTrnode != NULL)) t -= (LTrnode->h+1);
		return t;
	}
};

template<class T>
class Tree:public Table<T>
{
// public:
	TrNode<T>* radix = NULL;
	TrNode<T>* CrBr = NULL;
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
	 int GetBalance() {
		 return radix->dh();
	 };
	 bool operator==(Tree other) { return 1; }
private:
	void GoDownLeft();
	int FPCLCheck(TrNode<T>* tmp);
	public :void Balance();
	void BalanceOne(TrNode<T>* t);
	int DeleteRec(std::string key, TrNode<T>* t);
	void NewRadix();
};
template<class T>
void Tree<T>::NewRadix() {
	TrNode<T>* tmp = new TrNode<T>;
	if (radix->LTrnode != NULL) {
		int nh = 0,nh2=0;

		tmp->val = radix->LTrnode->val;

		tmp->RTrnode = radix;
		tmp->LTrnode = radix->LTrnode->LTrnode;
		tmp->UTrnode = NULL;
		if (radix->LTrnode == First) First = tmp;
		if (tmp->LTrnode != NULL) { tmp->LTrnode->UTrnode = tmp; nh2 = tmp->LTrnode->h + 1; }
		if (radix->LTrnode->RTrnode != NULL) {
			nh = radix->LTrnode->RTrnode->h + 1;
			radix->LTrnode = radix->LTrnode->RTrnode;
			radix->LTrnode->UTrnode = radix;
		}
		else {
			radix->LTrnode = NULL;
		}
		if ((radix->RTrnode != NULL) && (radix->RTrnode->h + 1 > nh)) nh = radix->RTrnode->h + 1;
		radix->h = nh;
		radix->UTrnode = tmp;
		if (tmp->RTrnode->h + 1 > nh2) nh2 = tmp->RTrnode->h + 1;
		tmp->h = nh2;

		radix = tmp;
		radix->UTrnode = NULL;
		Reset();
		return;
	}
	if (radix->RTrnode != NULL) {
		int nh = 0, nh2 = 0;
		tmp->val = radix->RTrnode->val;
		tmp->LTrnode = radix;
		tmp->RTrnode = radix->RTrnode->RTrnode;
		if (radix->RTrnode == Last) Last = tmp;
		if (tmp->RTrnode != NULL) { tmp->RTrnode->UTrnode = tmp; nh2 = tmp->RTrnode->h + 1; }
		if (radix->RTrnode->LTrnode != NULL) {
			nh = radix->RTrnode->LTrnode->h + 1;
			radix->RTrnode = radix->RTrnode->LTrnode;
			radix->RTrnode->UTrnode = radix;
		}
		else {
			radix->RTrnode = NULL;
		}
		if ((radix->LTrnode != NULL) && (radix->LTrnode->h + 1 > nh)) nh = radix->LTrnode->h + 1;
		radix->h = nh;
		if (tmp->LTrnode->h + 1 > nh2) nh2 = tmp->LTrnode->h + 1;
		tmp->h = nh2;
		radix->UTrnode = tmp;

		radix = tmp;
		Reset();
		return;
	}
};

template<class T>
int Tree<T>::Reset(void) {
	if (First == NULL) return 0;
	Current = First;
	CrBr = Current;
	return 1;
}; // установить на первую запись

template<class T>
int Tree<T>::IsTabEnded(void) const {
	return Current == Last;
}; // таблица завершена?
template<class T>
void Tree<T>::GoDownLeft() {
	//идем в самый левый лист
	while (!((Current->LTrnode == NULL) && (Current->RTrnode == NULL))) {
		if (Current->LTrnode != NULL) {
			Current = Current->LTrnode;
			continue;
		}
		if (Current->RTrnode != NULL) {
			//Current = Current->RTrnode;
			CrBr = Current;
			return;
		}
	}
	CrBr = Current->UTrnode;
};

template<class T>
int Tree<T>::GoNext(void) 
{
	if (IsEmpty()) throw "is empty";
	if (IsTabEnded()) {
		Reset();
		return 1;
	}

	/*std::cout << Current->val.name<< " h=" << Current->h << " ";
	if (Current->UTrnode != NULL) std::cout << "UTrnode =  " << Current->UTrnode->val << " ";
	if ( Current->LTrnode!=NULL) std::cout  << "LTrnode =  " << Current->LTrnode->val << " ";
	if (Current->RTrnode != NULL) std::cout << "RTrnode =  " << Current->RTrnode->val << " ";
	std::cout << endl;*/
	if (Current == radix) {
		Current = Current->RTrnode;
		CrBr = Current;
		GoDownLeft();
		return 1;
	}
	if (Current == CrBr->LTrnode) {
		Current = CrBr;
		return 1;
	}
	if (Current == CrBr->RTrnode) {

		if (CrBr == radix) { return 1; throw "is end"; }

		Current = CrBr->UTrnode;
		while (CrBr == Current->RTrnode) {
			CrBr = CrBr->UTrnode;
			Current = Current->UTrnode;
		}
		CrBr = Current;
		return 1;
	}
	if (Current == CrBr) {
		if (Current->RTrnode == NULL) {
			Current = Current->UTrnode;
			CrBr = Current;
			return 1;
		}
		Current = Current->RTrnode;
		GoDownLeft();
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
		radix = new TrNode<T>;
		radix->h = 0;
		radix->val = obj;
		First = radix;
		Last = radix;
		Current = radix;
		radix->UTrnode = NULL;
		size++;
		return true;
	}
	int a= radix->Add(obj);
	if (a == -1) return 0;
	if (obj.name > Last->val.name) {
		Last = Last->RTrnode;
	};
	if (obj.name < First->val.name) First = First->LTrnode;
	size++;
	Balance();
	return 1;
};

template<class T>
int Tree<T>::FPCLCheck(TrNode<T>* tmp) {
	TrNode<T>* a; int p;
	if (tmp->UTrnode != NULL) { a = tmp->UTrnode; p = 0; }
	else if (tmp->LTrnode != NULL) { a = tmp->LTrnode; p = 1; }
	else if (tmp->RTrnode != NULL) {a = tmp->RTrnode; p = 2;}

	if (First == tmp) { 
		if (tmp->RTrnode != NULL) { First = tmp->RTrnode; while (First->LTrnode != NULL) First = First->LTrnode; }
		else if (tmp->UTrnode != NULL) First = tmp->UTrnode;
	}
	if (Last == tmp)  Last = a; 
	if (CrBr == tmp) CrBr = a;
	if (Current == tmp) Current = a;
	if (radix == tmp) { NewRadix(); }
	return p;

};

template<class T>
int Tree<T>::DeleteRec(std::string key, TrNode<T>* t) {//1 -минус уровень 0 -уровни не поменялись -1 -не нашлось
	if (key == t->val.name) {
		FPCLCheck(t);
		if ((t->LTrnode == NULL) && (t->RTrnode==NULL)) {
			int a = 0;
			if ((t->UTrnode->LTrnode == NULL) || (t->UTrnode->RTrnode == NULL)) a = 1;
			if (t->UTrnode->LTrnode == t) t->UTrnode->LTrnode = NULL;
			if (t->UTrnode->RTrnode == t) t->UTrnode->RTrnode = NULL;
			size--;
			delete t;
			return a;
		}

		if (t->LTrnode == NULL) {
			int y= FPCLCheck(t);
			TrNode<T>* k = t->UTrnode;
			if ((k!=NULL)&&(k->val.name == radix->val.name)) k = radix;
			if ((k != NULL) && (k->val.name < t->val.name)) {
				k->RTrnode = t->RTrnode; 
			}
			else  
			{
				if (k != NULL) k->LTrnode = t->RTrnode;
			}
			t->RTrnode->UTrnode = k;
			size--;
			delete t;
			return 1;
		} 
		if (t->RTrnode == NULL) {
			FPCLCheck(t);
			if (t->UTrnode->RTrnode == t) t->UTrnode->RTrnode = t->LTrnode;
			else  t->UTrnode->LTrnode = t->LTrnode;
			t->LTrnode->UTrnode = t->UTrnode;
			size--;
			delete t;
			return 1;
		}
		TrNode<T>* tmp2 = t->LTrnode;
		while (tmp2->RTrnode != NULL) tmp2 = tmp2->RTrnode;
		FPCLCheck(tmp2);
		T  y = tmp2->val;
		int a=  Delete(tmp2->val.name);
		t->val = y;
		return a;
	}
	if ((t->LTrnode == NULL) && (t->RTrnode == NULL)) return -1;
	// right way
	int a = 0;
	if (key > t->val.name) {
		if (t->RTrnode == NULL) {
			return -1;
		}
		a = DeleteRec(key,t->RTrnode);
		if (a == 1) t->h--;
		return a;
	}
	//left way
	if (key < t->val.name) {
		if (t->LTrnode == NULL) {
			return -1;
		}
		a = DeleteRec(key, t->LTrnode);
		if (a == 1) t->h--;
		return a;
	}
}

template<class T>
bool Tree<T>::Delete(std::string key) {
	if ((radix == NULL)||(size==0))	return false;
	if (size == 1) { delete radix; radix == NULL;  size--; return 1; }
	if (radix->val.name == key) {
		NewRadix();
	}
	int a = DeleteRec(key, radix) != -1;
	if (a != -1) Balance();	
	return a;
};

template<class T>
T Tree<T>::Find(std::string key) {
	if (radix == NULL)	throw "is empty";
	else {
		TrNode<T>* tmp = radix;
		while (true) {
			// right way
			if (tmp == NULL) throw "cant find";
			if (key > tmp->val.name) {
				tmp = tmp->RTrnode;
				continue;
			}
			//left way
			if (key < tmp->val.name) {
				tmp = tmp->LTrnode;
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
template<class T>
void Tree<T>::Balance() {
	if (IsEmpty()) return;
	if ((radix->dh() <= 1) && (radix->dh() >= -1)) { return; }
	//std::cout << " B1" << *this << endl;
	BalanceOne(radix);
	radix->UTrnode == NULL;
	radix->newH();
	//std::cout << " B2" << *this << endl;
	Reset();
};
template<class T>
void Tree<T>::BalanceOne(TrNode<T>* t) {
	if ((t->LTrnode == NULL) && (t->RTrnode == NULL)) return;
	if (t->LTrnode != NULL) BalanceOne(t->LTrnode);
	if (t->RTrnode != NULL) BalanceOne(t->RTrnode);

	int dh = t->dh();
	if (dh < -1) {
		
		if ((t->LTrnode != NULL) && (t->LTrnode->dh() <= 0)) { 
			if (t == radix) radix = t->LTrnode;
			t->RightRot(); 
		}
		else {
			//std::cout << "BIG R" << endl;
			if (t->LTrnode == radix) radix = t->LTrnode->RTrnode;
			t->LTrnode->LeftRot();
			if (t == radix) radix = t->LTrnode;
			t->RightRot();
		}
	}
	if (dh > 1) {

		if ((t->RTrnode != NULL) && (t->RTrnode->dh() >= 0)) { 
			if (t == radix) radix = t->RTrnode;
			t->LeftRot();
		}
		else {
			//std::cout << "BIG L" << endl;
			if (t->RTrnode == radix) radix = t->RTrnode->LTrnode;
			t->RTrnode->RightRot();
			if (t == radix) radix = t->RTrnode;
			t->LeftRot();
		}
	}
};
