#pragma once
#include <iostream>
#include "THeadList.h"
#include "TMonom.h"

const int nonDisplayedZeros = 4; // Количество неотображаемых нулей при выводе коэффициента полинома
								 // Кол-во символов после запятой = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(const TPolinom& other);
	TPolinom(string str);
	void AddMonom(TMonom monom); // добавление монома
	string ToString(); // перевод в строку

	// МАТЕМАТИЧЕСКИЕ ОПЕРАЦИИ:
	TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom DivMonom(TMonom monom);//деление мономов 
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom SubPolinom (TPolinom& other); //  вычитание полинома
	TPolinom SubMonom(TMonom monom); // вычитание монома
	TPolinom Division(TPolinom& other,TPolinom& ost); // Деление полиномов с остатком
	double calculate(double X = 0, double Y = 0, double Z = 0);


	//              ОПЕРАТОРЫ:

	TPolinom operator=(TPolinom other);
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	//TPolinom& operator=(TPolinom& other); // присваивание

	TPolinom operator+(TPolinom other); // сложение полиномов
	TPolinom operator+(TMonom monom); // сложение c мономом

	TPolinom operator- (TPolinom other); //  вычитание полинома
	TPolinom operator- (TMonom monom); //  вычитание монома

	TPolinom operator*(double c); // умножение полинома на число
	TPolinom operator* (TPolinom other); // умножение полиномов
	TPolinom operator* (TMonom monom); // умножение на моном

	TPolinom operator/ (TPolinom other); // Деление полиномов без остатка (если отстаток, то будет исключение )
	TPolinom operator/ (TMonom monom);
	TPolinom operator/(double c); // деление полинома на число

	TPolinom derivative();//по всем переменным
	friend void derivative(TPolinom& other) { other = other.derivative(); }//по всем переменным
	TPolinom derivative(char md);
	friend void derivative(TPolinom& other, char md) { other = other.derivative(md); }

	TPolinom integral();//по всем переменным
	friend void integral(TPolinom& other) { other = other.integral(); }//по всем переменным
	TPolinom integral(char md);
	friend void integral(TPolinom& other, char md) { other = other.integral(md); }
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
{

}

TPolinom::TPolinom(const TPolinom& other):THeadList<TMonom>::THeadList()
{
	if (other.length==0) return;
	TMonom tmp;
	TNode<TMonom>* st = other.pFirst;
	for (int i = 0; i < other.length; i++) {
		
		InsertLast(st->value);
		if (st == other.pPrevious) pPrevious = pLast;
		if (st == other.pCurrent) pCurrent = pLast;
		st= st->pNext;
	}
	pHead->pNext = pFirst;
	if (other.pHead == other.pPrevious) pPrevious = pHead;
	pLast->pNext = pHead;
	st = nullptr;
	return;
}

TPolinom::TPolinom(string str)
{
	int i = 0;
	string s="";
	while (i!=str.size()) {
		//std::cout << s<<endl;
		if ((str[i] == '-') || (str[i] == '+')) {
			if (s != "") { 
				//std::cout << "monom " << s << endl;
				AddMonom(TMonom(s));
				s = str[i];
				i++; 
				continue;
			}
		}
		s += str[i++];
	}
	if (s != "") AddMonom(TMonom(s));

}


void TPolinom::AddMonom(TMonom monom)
{
	//std::cout << "\nADD MONOM STATUS\n" << *this<<endl<<"MONOM IS"<<m<<endl;
	
	if (monom.GetCoef() == 0) return;

	if (IsEmpty()) { InsertFirst(monom);  return; }
	Reset();
	for (int i = 0; i < length; i++) {
		
		if (GetCurrentItem().index < monom.index) {
			if (IsEnd()) { InsertLast(monom); return; }
			GoNext();
			continue;
		}
		if (GetCurrentItem().index == monom.index) {
			int newcoef = monom.coef + GetCurrentItem().coef;
			if (newcoef == 0) {
				DeleteCurrent();
				return;
			}
			pCurrent->value.coef = newcoef;
			return;
		}
		if (GetCurrentItem().index > monom.index) {

			InsertCurrent(monom);
			
			return;
		}
	}

	/*
	if (((length == 1) && (pFirst->value.index < m.index))) { InsertLast(m);  
	return; }
	if (((length == 1) && (pFirst->value.index > m.index))) {
		InsertFirst(m);
		return;
	}

	Reset();

	while ((GetCurrentItem().index < m.index)&&( !IsEnd())) { GoNext(); }

	if (GetCurrentItem().index == m.index) {
		pCurrent->value.coef += m.coef;
		if (pCurrent->value.coef == 0) {
			DeleteCurrent(); length++;  
			//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this; 
			return;
		}
		//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this;
		return;
	}
	if (GetCurrentItem().index < m.index) {
		InsertLast(m); return;
	}
	if (GetCurrentItem().index > m.index) {
		InsertCurrent(m); return;
	}
	//std::cout << "  2   MONOM =" << m << " Polinom is  " << *this;
	*/
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	Reset();
	if (IsEmpty()) return *this;
	if (monom.coef == 0) { Clear(); return *this; }
	TMonom m;
	while (!IsEnd())
	{
		m.SetCoef(pCurrent->value.GetCoef() * monom.GetCoef());
		m.SetIndex(pCurrent->value.index + monom.GetIndex());
		SetCurrentItem(m);
		GoNext();
	}
		m.SetCoef(pCurrent->value.coef * monom.GetCoef());
		m.SetIndex(pCurrent->value.index + monom.GetIndex());
		SetCurrentItem(m);
	return *this;
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	*this = *this + other;
	return *this;
}

string TPolinom::ToString()
{
	string result="";
	if (IsEmpty()) return result;
	Reset();
	TMonom tmp;
	while (!IsEnd())
	{
		tmp = GetCurrentItem();
		if (tmp.GetCoef() > 0) result += '+';
		string stmp = std::to_string(tmp.GetCoef());
		bool u = false;
		for (int i = 0; i < stmp.size(); i++) {
			if (u) {
				if (stmp[i] != '0') result += stmp[i];
				else if ((i > 0) && (stmp[i - 1] == ',')) result += stmp[i];
			}
			else  result += stmp[i];
			if ((!u) && (stmp[i] == ',')) u = true;
		}
		int a = tmp.GetIndex();
		if ((a / 100 != 0)&& (a / 100 != 1)) { result += "X^"; result += std::to_string(a / 100); }
		if (a / 100 == 1) { result += "X"; }
		a %= 100;
		//std::cout << a;
		if ((a / 10 != 0)&& (a / 10 != 1)) { result += "Y^"; result += std::to_string( a / 10); }
		if (a / 10 == 1) { result += "Y";}
		a %= 10;
		if ((a != 0)&& (a != 1)) { result += "Z^"; result += std::to_string(a); }
		if (a == 1) { result += "Z";}
		result += ' ';
		GoNext();
	}

	tmp = GetCurrentItem();
	if (tmp.GetCoef() > 0) result += '+';
	string stmp = std::to_string(tmp.GetCoef());
	bool u = false;
	for (int i = 0; i < stmp.size(); i++) {
		if (u) {
			if (stmp[i] != '0') result += stmp[i];
			else if ((i > 0) && (stmp[i - 1] == ',')) result += stmp[i];
		}
		else  result += stmp[i];
		if ((!u) && (stmp[i] == ',')) u = true;
	}
	int a = tmp.GetIndex();
	if ((a / 100 != 0) && (a / 100 != 1)) { result += "X^"; result += std::to_string(a / 100); }
	if (a / 100 == 1) { result += "X"; }
	a %= 100;
	//std::cout << a;
	if ((a / 10 != 0) && (a / 10 != 1)) { result += "Y^"; result += std::to_string(a / 10); }
	if (a / 10 == 1) { result += "Y"; }
	a %= 10;
	if ((a != 0) && (a != 1)) { result += "Z^"; result += std::to_string(a); }
	if (a == 1) { result += "Z"; }
	return result;
}

TPolinom TPolinom::DivMonom(TMonom monom) {
	

	if (IsEmpty()) return *this;
	if (monom.coef == 0) { Clear(); throw "division by 0";}
	Reset();
	TMonom m;
	while (!IsEnd())
	{
		m = GetCurrentItem() / monom;
		SetCurrentItem(m);
		GoNext();
	}
	m = GetCurrentItem() / monom;
	SetCurrentItem(m);
	GoNext();
	return *this;
}

TPolinom TPolinom::SubPolinom(TPolinom& other) {

	other.Reset();
	
	while (!other.IsEnd())
	{
		SubMonom(other.GetCurrentItem());
		other.GoNext();
	}
	SubMonom(other.GetCurrentItem());

	return *this;
}; //  вычитание полинома

TPolinom  TPolinom::Division(TPolinom& other, TPolinom& ost) {

	
	if (other.IsEmpty()) return other;
	if (IsEmpty()) return *this;

	TPolinom tmp(other);
	TPolinom cp(*this);
	//std::cout << "cp is \n" << cp << endl;
	TMonom factor;
	TMonom fmn(other.pFirst->value);
	TPolinom ans;
	other.Reset();
	cp.Reset();
	int oper = 0;


	while (!cp.IsEmpty()) {//    this/other

	    std::cout << " DIVISION \n";
		factor = (cp.GetCurrentItem() / fmn);
		
		ans.AddMonom(factor);

		//cout << "\nafter operator cp\n" << cp << endl;
		//cout << "\nfactor\n" << factor << endl;

		tmp.MultMonom(factor);
		std::cout << "ssss  "<<factor<<endl;
		std::cout << tmp .length<< endl;
		cp.SubPolinom(tmp);

		tmp = other;
		//cout << "\noperator tmp\n" << tmp << endl;
		oper++;
		if (oper > (other.length+5)) break;
	}


	ost = cp;
	return ans;

}

double TPolinom::calculate(double X, double Y, double Z)
{
	if (IsEmpty())	return 0.0;
	double s = 0;
	for (int i = 0; i < length; i++) {
		s += GetCurrentItem().calculate(X, Y, Z);
		GoNext();
	}
	return s;
}

TPolinom TPolinom::SubMonom(TMonom monom) {
	
	int a = monom.coef;
	a *= -1;
	monom.SetCoef(a);
	this->AddMonom(monom);
	
	return *this;
};

TPolinom TPolinom::operator/(TPolinom other)
{

	TPolinom tmp;
	TPolinom ans(*this);
	
	ans.Division(other, tmp);
	if (!tmp.IsEmpty()) {
		throw "impossible division operation without remainder";
	}
	return ans;
}

TPolinom TPolinom::operator/(TMonom monom)
{

	TPolinom p(*this);
	p.DivMonom(monom);
	return p;
}

TPolinom TPolinom::operator/(double c)
{
	Reset();
	if (IsEmpty()) return *this;
	if (c == 0) { throw "Division by 0"; }
	TPolinom* tmp = new TPolinom(*this);
	tmp->Reset();
	while (!tmp->IsEnd()) {
		tmp->pCurrent->value.coef /= c;
		tmp->GoNext();
	}
	tmp->pCurrent->value.coef /= c;
	//std::cout <<"TMP"<< *tmp<<"hh";
	return *tmp;
}

TPolinom TPolinom::derivative()
{
	TPolinom p;
	for (int i = 0; i < length; i++) {
		p.AddMonom(GetCurrentItem().derivative());
		cout << GetCurrentItem()<<"  "<< GetCurrentItem().derivative() << endl;
		GoNext();
	}
	return p;
}

TPolinom TPolinom::derivative(char md)
{
	TPolinom p;
	for (int i = 0; i < length; i++) {
		p.AddMonom(GetCurrentItem().derivative(md));
		cout << GetCurrentItem() << "  " << GetCurrentItem().derivative(md) << endl;
		GoNext();
	}
	return p;
}

TPolinom TPolinom::integral(char md)
{
	TPolinom p;
	for (int i = 0; i < length; i++) {
		p.AddMonom(GetCurrentItem().integral(md));
		GoNext();
	}
	return p;
}

TPolinom TPolinom::integral()
{
	TPolinom p;
	for (int i = 0; i < length; i++) {
		p.AddMonom(GetCurrentItem().integral());
		GoNext();
	}
	return p;
}

TPolinom TPolinom::operator+(TPolinom other)
{
	if (other.IsEmpty()) return *this;
	//std::cout << "Other " << other<<endl;
	if (this->IsEmpty()) return other;

	if (length >= other.length) {
		TPolinom* tmp = new TPolinom(*this);
		//std::cout << "   +  tmp 1  " << *tmp ;
	other.Reset();
	while (!other.IsEnd()) {
		tmp->AddMonom(other.GetCurrentItem());
		//std::cout << "   +  tmp "  << *tmp ;
		other.GoNext();
	}
	tmp->AddMonom(other.GetCurrentItem());
	//std::cout << "   +  tmp r  " << *tmp;
	return *tmp;
	}
	else return (other + *this);
}

TPolinom TPolinom::operator+(TMonom monom)
{
	if (monom.coef == 0) return *this;
	AddMonom(monom);
	return *this;
}

TPolinom TPolinom::operator*(double c)
{

	if (IsEmpty()) return *this;
	if (c == 0) { TPolinom tmp; return tmp; }
	TPolinom tmp(*this);
	for (int i = 0; i < tmp.length; i++) {

		tmp.pCurrent->value.coef *= c;
		tmp.GoNext();
	}
	return tmp;
}

TPolinom TPolinom::operator*(TPolinom other)
{

	if (other.IsEmpty()) return other;
	if (IsEmpty()) return *this;
	TPolinom* tmp = new TPolinom(*this);
	TPolinom* ans = new TPolinom();
	other.Reset();
	Reset();
	while (!other.IsEnd()) {
		tmp->MultMonom(other.GetCurrentItem());
	    //std::cout << "TMP" << *tmp;
		ans->AddPolinom(*tmp);
		//std::cout << "ans" << *ans;
		tmp = this;
		other.GoNext();
	}
	tmp->MultMonom(other.GetCurrentItem());
	ans->AddPolinom(*tmp);
	return *ans;
}

TPolinom TPolinom::operator* (TMonom monom) {
	TPolinom p(*this);
	p.MultMonom(monom);
	return p;
}; // умножение на моном

TPolinom TPolinom::operator-(TMonom monom){
	int a = monom.coef;
	a *= -1;
	monom.SetCoef(a);
	TPolinom p(*this);
	p.AddMonom(monom);
	return p;

}

TPolinom TPolinom::operator- (TPolinom other) {
	other.Reset();
	TPolinom p(*this);
	while (!other.IsEnd())
	{
		p.SubMonom(other.GetCurrentItem());
		other.GoNext();
	}
	p.SubMonom(other.GetCurrentItem());
	return p;
}; //  вычитание полинома

TPolinom TPolinom::operator=(TPolinom other)
{
	THeadList<TMonom>::operator=(other);
	return *this;
}

bool TPolinom::operator==(TPolinom& other)
{
	if (length != other.length) return false;
	if (this == &other) return true;
	Reset();
	other.Reset();
	for (int i = 0; i < length; i++) {
		TMonom a, b;
		a = other.GetCurrentItem();
		b = GetCurrentItem();
		GoNext();
		other.GoNext();
		
		if (!(a == b)) { return false; }
	}
	return true;
}
