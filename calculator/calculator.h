#include <iostream>
#include <cmath>
#include <string>
#include "stack.h"
#include "TPolinom.h"
#include "Table.h"

//define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
using namespace std;
template <class T = TPolinom >
class TCalculator
{
protected:
	string infix;
	string postfix;
	TStack<T> st;
	TStack<string> sts;
	Table<T>* tb;
public:
	TCalculator(Table<T>* a= nullptr) :st(50), sts(50)
	{
		tb = a;
		infix = "";
		postfix = "";
	}
	void SetData(Table<T>* a) {
		tb = a;
	}
	string GetExpression() { return infix; }
	void SetExpression(string ex) { infix = ex+" "; }
	string GetPostfix() { return postfix; }
	void ToPostfix();
	T CalcPostfix(double x = 0, double y = 0, double z = 0);
	double Calc(T& obj, double x=0,double y=0, double z=0);
	T Calc(double x = 0, double y = 0, double z = 0);
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
template <class T>
int TCalculator<T>::Priority(string c) { 

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
template <class T >
void TCalculator<T>::ToPostfix() {
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

		if (c == ")")
		{
			flag = false;
			string tmp= sts.Pop();
			while ((tmp.size()!=1)||  ((tmp.size()==1)&&(tmp[0] != '('))  )
			{
				postfix += tmp;
				tmp = sts.Pop();
			}
			i++;
			continue;
		}

		pr = Priority(c);

		if ((pr == 0)&&(c=="$")) {//if this is operation name

			string tmp = c;
			while (pr == 0) {
				j++;
				if (j == infix.size()) break;
				tmp += infix[j];
				pr = Priority(tmp);
			}
			if (pr == 0) j = i;
			else { c = tmp;  i = j; }
			//std::cout << "  $ is " << tmp << endl;
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



		string tmp = c;
		string tmp2 = tmp;
		int dk = j;
		while ((infix[j] != ' ')&&(j < infix.size()-1)) {
			j++;
			if (tb->Exist(tmp)) { tmp2 = tmp; dk = j-1; }
			tmp += infix[j];
		}
		if (tb->Exist(tmp2)) {
			flag = false;
			i = dk;
			postfix += tmp2+" ";
			c = tmp2;
			i++;
			continue;
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
template <class T >
T TCalculator<T>::CalcPostfix(double x=0, double y=0, double z=0) {
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
				j++;
				if (j == postfix.size()) break;
				tmp += postfix[j];
				pr = Priority(tmp);
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
					TPolinom ost;
					op1 = op1.Division(op2, ost);
					if (!ost.IsEmpty()) {
						double tmp1 = ost.calculate(x, y, z), tmp2 = op2.calculate(x,y,z);
						tmp1 = tmp1 / tmp2;
						op1.AddMonom(TMonom(tmp1,0,0,0));
					}
					st.Push(op1); 
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

		while ((postfix[j] != ' ') && (j < postfix.size() - 1)) {
			j++;
			if (tb->Exist(tmp)) { tmp2 = tmp; }
			tmp += postfix[j];
		}
		if (tb->Exist(tmp2)) {
			st.Push((tb->Find(tmp2)));
			i = j;
			c = tmp2;
			continue;
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
template <class T >
double TCalculator<T>::Calc(T& obj,double x, double y, double z) {
	if (tb == nullptr) throw "no data tbl";
	ToPostfix();
	obj = CalcPostfix(x, y, z);
	return obj.calculate(x, y, z);
}
template <class T >
T TCalculator<T>::Calc(double x, double y, double z) {
	if (tb == nullptr) throw "no data tbl";
	ToPostfix();
	T ans = CalcPostfix(x, y, z);
	return ans;
}