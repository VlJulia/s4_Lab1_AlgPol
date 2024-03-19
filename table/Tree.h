#include "Table.h"
struct TrNode
{
	TrNode* RTrnode = NULL;
	TrNode* LTrnode = NULL;
	Polinom<string, TPolinom> pol;
	int high = -1;

};


class Tree: Table<string,TPolinom>
{
	TrNode* radix = NULL;
public:
	Tree() {};
	Tree(Tree& other);
	~Tree();
	Tree operator=(Tree other);
	bool AddPolinom(Polinom<string , TPolinom> pol);
	bool DelPolinom(string polinom_name);
	Polinom<string, TPolinom>* FindPolinom(string polinom_name);
	bool PolinomExist(string polinom_name);

private:
	TrNode* newTrNode(Polinom<string, TPolinom> pol, int h =0) ;
};

TrNode* Tree::newTrNode(Polinom<string, TPolinom> pol, int h) {
	TrNode* nn = new TrNode();
	nn->high = h;
	nn->pol = pol;
	return nn;
};
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