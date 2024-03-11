#include <iostream>
#include <cmath>
#include <string>
#include "stack.h"
#include "TPolinom.h"
#include "Table.h"

//define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
using namespace std;
class TCalculator
{
protected:
	string infix;
	string postfix;
	TStack<TPolinom> st;
	TStack<string> sts;
	Table<string, TPolinom>* tb;
public:
	TCalculator(Table<string, TPolinom>* a) :st(50), sts(50)
	{
		tb = a;
		infix = "";
		postfix = "";
	}
	string GetExpression() { return infix; }
	void SetExpression(string ex) { infix = ex; }
	string GetPostfix() { return postfix; }
	void ToPostfix();
	TPolinom CalcPostfix();
	double Calc(double x=0,double y=0, double z=0);

protected:
	//int Priority(char c);
	int Priority(string c);

};
//template<class T>
//int TCalculator<T>::Priority(char c) {
//	switch (c)
//	{
//	case ')':
//	case '(': return 1;
//	case '+':
//	case '-': return 2;
//	case '*':
//	case '/': return 3;
//	default: throw "unknow elem " + c;
//	}
//}

int TCalculator::Priority(string c) { 

	if (c.size() == 1) {
		char a = c[0];
		switch (a)
		{
		case ')':
		case '(': return 1;
		case '+':
		case '-': return 2;
		case '*':
		case '/': return 3;
		}
	}

	if ((c == "$int_x")||(c == "$int_y")||(c == "$int_z")) return 4;
	if ((c == "$der_x") || (c == "$der_y") || (c == "$der_z")) return 4;

	return 0;

}

void TCalculator::ToPostfix() {
	int i = 0;
	string c;
	bool flag = true;
	int pr = 0;
	while (i < infix.size())
	{
		c = infix[i];
		//std::cout << sts << endl << postfix << endl;
		int j = i;
		if ((c == " ")) { i++; continue; }
		pr = Priority(c);

		if ((pr == 0)&&(c=="$")) {//if this is operation name
			string tmp = c;
			while (pr == 0) {
				if (j == infix.size()) break;
				tmp += infix[j];
				pr = Priority(tmp);
				j++;
			}
			if (pr == 0) j = 0;
			else { c = tmp;  i = j; }
		}

		if (pr!=0) {
			flag = false;
			if (c == "(") {
				sts.Push(c);
				i++;
				continue;
			}

			if (sts.IsEmpty()) {
				sts.Push(c);
				i++;
				continue; }

			string tmp = sts.TopView();

			if (Priority(tmp) < pr) { sts.Push(c);}
			else {
				while ((Priority(tmp) >= pr)&&(!sts.IsEmpty())) {
					//std::cout << sts << endl << postfix << endl;
					postfix += sts.Pop();
					//std::cout << "\n"<<postfix<<endl;
					postfix += " ";
					if (sts.IsEmpty()) { break; }
				}
				sts.Push(c);
			}
			i++;
			continue;
		}



		if (c[0] == ')') 
		{
			flag = false;
			string tmp = sts.Pop();
			while ((tmp.size()!=1)||((tmp.size()==1)&&(tmp[0] != '(')))
			{
				postfix += tmp;
				tmp = sts.Pop();
			}
		}

		string tmp = c;
		string tmp2 = tmp;
		while ((infix[j] != ' ')&&(j != infix.size())) {
			if (tb->PolinomExist(tmp)) tmp2 = tmp;
			tmp += infix[j];
			j++;
		}
		if (tb->PolinomExist(tmp2)) {
			flag = false;
			i = j;
			postfix += tmp2;
			c = tmp2;
		}

		if ((c.size()==1)&&(c[0] >= '0') && (c[0] <= '9'))
		{
			size_t inx=0;
			double tmp = stod(&infix[i], &inx);
			//std::cout <<"\nSTOD inx "<< inx << endl;
			postfix += to_string(tmp)+" ";
			i += inx;
			continue;
		}

		i++;
		if (flag) throw "unknow elem " + c;
	}
	

	while (!(sts.IsEmpty())) { postfix += sts.Pop(); }
	
};

TPolinom TCalculator::CalcPostfix() {
	int i = 0;
	string c;
	int pr = 0;
	while (i < postfix.size())
	{
		int j = i;
		c = postfix[i];
		if (c == " ") { i++; continue; }
		pr = Priority(c);

		if ((pr == 0) && (c == "$")) {//if this is operation name
			string tmp = c;
			while (pr == 0) {
				if (j == postfix.size()) break;
				tmp += postfix[j];
				pr = Priority(tmp);
				j++;
			}
			if (pr == 0) j = 0;
			else {
				c = tmp;
				i = j;
			}
		}

		if (pr != 0) {
			if (c.size() == 1) {
				switch (c[0])
				{
				case'+': { st.Push(st.Pop() + st.Pop());  break; }
				case'-': { 
					TPolinom op2 = st.Pop();
					TPolinom op1 = st.Pop();
					st.Push(op1 - op2);
					break; 
				}
				case'*': { st.Push(st.Pop() * st.Pop()); break; }
				case'/': {
					TPolinom op2 = st.Pop();
					TPolinom op1 = st.Pop();
					st.Push(op1 / op2); 
					break; 
				}
				}
			}
			else {
				if (c == "$int_x") { st.Push( (st.Pop()).integral('X')); };
				if (c == "$int_y") { st.Push((st.Pop()).integral('Y')); };
				if (c == "$int_z") { st.Push((st.Pop()).integral('Z')); };
				if (c == "$der_x") { st.Push((st.Pop()).derivative('X')); };
				if (c == "$der_y") { st.Push((st.Pop()).derivative('Y')); };
				if (c == "$der_z") { st.Push((st.Pop()).derivative('Z')); };
				}
			}

		string tmp = c;
		string tmp2 = tmp;

		while ((postfix[j] != ' ') && (j != postfix.size())) {
			if (tb->PolinomExist(tmp)) tmp2 = tmp;
			tmp += postfix[j];
			j++;
		}
		if (tb->PolinomExist(tmp2)) {
			st.Push(*(tb->FindPolinom(tmp2).polinom));
			i = j;
			c = tmp2;
		}

		if ((c.size()==1)&&(c[0] >= '0') && (c[0] <= '9')) 
		{
				size_t inx;
				double tmp = stod(&postfix[i], &inx);
				TPolinom np;
				np.AddMonom(TMonom(tmp, 0, 0, 0));
				st.Push(np);
				i += inx;
				continue;
		}
		i++;
	}
	return st.Pop();
}
double TCalculator::Calc(double x, double y, double z) {
	ToPostfix();
	TPolinom ans = CalcPostfix();
	return ans.calculate(x,y,z);
	
}

