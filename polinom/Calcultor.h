#include <iostream>
#include <cmath>
#include <string>
#include "stack.h"

//define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
using namespace std;

class TCalculator
{
protected:
	string infix;
	string postfix;
	TStack<double> st;
	TStack<char> stc;
public:
	TCalculator() :st(50), stc(50)
	{
		infix = "";
		postfix = "";
	}
	string GetExpression() { return infix; }
	void SetExpression(string ex) { infix = ex; }
	string GetPostfix() { return postfix; }
	int Priority(char c);
	void ToPostfix();
	double CalcPostfix();
	double Calc();
};

int TCalculator::Priority(char c) {
	switch (c)
	{
	case ')':
	case '(': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	default: throw "unknow elem " + c;
	}
}

void TCalculator::ToPostfix() {
	int i = 0;
	char c;
	bool flag = true;
	while (i < infix.size())
	{
		c = infix[i];
		//std::cout << stc << endl << postfix << endl;

		if ((c == ' ')) { i++; continue; }
		if ((c >= '0') && (c <= '9')) 
		{
			size_t inx=0;
			double tmp = stod(&infix[i], &inx);
			//std::cout <<"\nSTOD inx "<< inx << endl;
			postfix += to_string(tmp)+" ";
			i += inx;
			continue;
		}

		if ((c == '+') || (c == '-') || (c == '/') || (c == '*')||(c=='(')) {
			flag = false;
			if (c == '(') {
				stc.Push(c); 
				i++;
				continue;
			}
			if (stc.IsEmpty()) { stc.Push(c); i++; continue; }
			char tmp = stc.TopView();
			if (Priority(tmp) < Priority(c)) { stc.Push(c);}
			else {
				while ((Priority(tmp) >= Priority(c))&&(!stc.IsEmpty())) {
					//std::cout << stc << endl << postfix << endl;
					postfix += stc.Pop();
					//std::cout << "\n"<<postfix<<endl;
					postfix += " ";
					if (stc.IsEmpty()) { break; }
				}
				stc.Push(c);
			}
			i++;
			continue;
		}
		if (c == ')') {
			flag = false;
			char tmp = stc.Pop();
			while (tmp != '(')
			{
				postfix += tmp;
				tmp = stc.Pop();
			}
		}
		i++;
		if (flag) throw "unknow elem " + c;
	}
	

	while (!(stc.IsEmpty())) { postfix += stc.Pop(); }
	
};

double TCalculator::CalcPostfix() {
	int i = 0;
	char c;
	while (i < postfix.size())
	{
		c = postfix[i];
		if (c == ' ') { i++; continue; }

		if ((c >= '0') && (c <= '9')) {
			size_t inx;
			double tmp = stod(&postfix[i], &inx);
			st.Push(tmp);

			i += inx;
			continue;
		}

		double op2 = st.Pop();
		double op1 = st.Pop();
		switch (c)
		{
		case'+': { st.Push(op1 + op2);  break; }
		case'-': { st.Push(op1 - op2); break; }
		case'*': { st.Push(op1 * op2); break; }
		case'/': { st.Push(op1 / op2); break; }
		default: throw "unknow elem " + c;
		}
		i++;
	}
	return st.Pop();
}

double TCalculator::Calc() {
	ToPostfix();
	return CalcPostfix();
	
}

