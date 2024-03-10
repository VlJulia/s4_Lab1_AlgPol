#pragma once
#include <iostream>
#include "THeadList.h"
#include "TMonom.h"

const int nonDisplayedZeros = 4; // ���������� �������������� ����� ��� ������ ������������ ��������
								 // ���-�� �������� ����� ������� = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(std::string str);
	void AddMonom(TMonom newMonom); // ���������� ������
	string ToString(); // ������� � ������

	// �������������� ��������:
	TPolinom MultMonom(TMonom monom); // ��������� �������
	TPolinom DivMonom(TMonom monom);//������� ������� 
	TPolinom AddPolinom(TPolinom& other); // ���������� ��������
	TPolinom SubPolinom (TPolinom& other); //  ��������� ��������
	TPolinom SubMonom(TMonom monom); // ��������� ������
	TPolinom Division(TPolinom& other,TPolinom& ost); // ������� ��������� � ��������



	//              ���������:
	bool operator==(TPolinom& other); // ��������� ��������� �� ���������
	TPolinom& operator=(TPolinom& other); // ������������

	TPolinom& operator+(TPolinom& q); // �������� ���������

	TPolinom operator*(double c); // ��������� �������� �� �����
	TPolinom operator* (TPolinom& other); // ��������� ���������
	TPolinom operator* (TMonom monom); // ��������� �� �����

	TPolinom operator- (TMonom monom); //  ��������� ������
	TPolinom operator- (TPolinom& other); //  ��������� ��������
	TPolinom operator/ (TPolinom& other); // ������� ��������� ��� ������� (���� ��������, �� ����� ���������� )

	TPolinom operator/ (TMonom& other);
	TPolinom operator/(double c); // ������� �������� �� �����
	TPolinom& operator+(TMonom& q); // �������� c �������
};

TPolinom::TPolinom() :THeadList<TMonom>::THeadList()
{

}

TPolinom::TPolinom(TPolinom& other):THeadList<TMonom>::THeadList()
{
	if (other.IsEmpty()) return;
	
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

		/*
		bool st = 0;
		char c;
		int i = 0;
		TMonom m;

		int* mon_ind = new int[3];
		mon_ind[0] = 0; mon_ind[1] = 0; mon_ind[2] = 0;
		int w = 0;
		int p = 1;//-coef or +
		while ( i < str.size()) {
			c = str[i];
			if (c == ' ') { i++; continue; }
			if ((c == '-') || (c == '+')) {
				if (c == '+') p = 1;
				else p = -1;
				i++;
				continue;
			}

			if ((c >= '0') && (c <= '9')) {
				size_t d = 0;
				double a = stod(&str[i], &d);
				if (!st) m.SetCoef(p*a);
				i += d;
				continue;
			}
			if ((c == 'X')) {
				//std::cout << "i= " << i;
				if ((i + 1 < str.size()) && (str[i + 1] != 'Y')) w++;
				if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
					i += 2;
					size_t d = 0;
					int a = stoi(&str[i], &d);
					i += d;
					mon_ind[0] = a;
				}
				else { mon_ind[0] = 1; i++; }
				w++;
				c = str[i];
			}
			//std::cout << c;
			if (c == 'Y') {
				if ((i + 1 < str.size()) && (str[i + 1] != 'Z')) w++;
				if ((i + 1 < str.size()) && (str[i + 1] == '^')) {
					i += 2;
					size_t d = 0;
					int a = stoi(&str[i], &d);
					i += d;
					mon_ind[1] = a;
				}
				else { mon_ind[1] = 1; i++; }
				w++;
				c = str[i];
			}
			if (c == 'Z') {
				if ((i+1<str.size())&&(str[i + 1] == '^')) {
					i += 2;
					size_t d = 0;
					int a = stoi(&str[i], &d);
					i += d;
					mon_ind[2] = a;
				}
				else { mon_ind[2] = 1; i++; }
				w++;
				c = str[i];
			}
			//std::cout << c;
			if (w >= 3) {
				m.SetIndex(mon_ind[0] * 100 + mon_ind[1] * 10 + mon_ind[2]);
				mon_ind[0] = 0;
				mon_ind[1] = 0;
				mon_ind[2] = 0;
				AddMonom(m);
				//std::cout << m<<" ";
				m.coef = 0;
				w=0;
			i++;
			continue;
			}
			i++;
		}
		//AddMonom(m);
		*/
}

TPolinom& TPolinom::operator=(TPolinom& other)
{
	//std::cout << "-----1----" << endl;
	Clear();
	if (other.IsEmpty()) return *this;
	TNode<TMonom>* st = other.pCurrent;
	TMonom tmp;
	other.Reset();
	while (!other.IsEnd()) {
		tmp = other.pCurrent->value;
		InsertLast(tmp);
		other.GoNext();
	}
	tmp = other.pCurrent->value;
	InsertLast(tmp);
	other.GoNext();
	while (other.pCurrent != st) { other.GoNext(); GoNext(); }
	length = other.length;
	st = nullptr;
	return *this;
}

void TPolinom::AddMonom(TMonom m)
{
	//std::cout << "\nADD MONOM STATUS\n" << *this<<endl<<"MONOM IS"<<m<<endl;
	
	if (m.GetCoef() == 0) return;

	if (IsEmpty()) { InsertFirst(m);  return; }
	Reset();
	for (int i = 0; i < length; i++) {
		
		if (GetCurrentItem().index < m.index) { 
			if (IsEnd()) { InsertLast(m); return; }
			GoNext();
			continue;
		}
		if (GetCurrentItem().index == m.index) {
			int newcoef = m.coef + GetCurrentItem().coef;
			if (newcoef == 0) {
				DeleteCurrent();
				return;
			}
			pCurrent->value.coef = newcoef;
			return;
		}
		if (GetCurrentItem().index > m.index) {

			InsertCurrent(m);
			
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

TPolinom& TPolinom::operator+(TPolinom& other)
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

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	*this = *this + other;
	return *this;
}

TPolinom TPolinom::operator*(double c)
{
	Reset();
	if (IsEmpty()) return *this;
	if (c == 0) { TPolinom* tmp = new TPolinom(); return *tmp; }
	TPolinom* tmp = new TPolinom(*this);
	tmp->Reset();
	while (!tmp->IsEnd()) {
		tmp-> pCurrent->value.coef *= c;
		tmp->GoNext();
	}
	tmp->pCurrent->value.coef *= c;
	//std::cout <<"TMP"<< *tmp<<"hh";
	return *tmp;
}

TPolinom TPolinom::operator*(TPolinom& other)
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

bool TPolinom::operator==(TPolinom& other)
{
	if (length != other.length) return false;
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
TPolinom TPolinom::operator* (TMonom monom) {
	TPolinom p(*this);
	p.MultMonom(monom);
	return p;
}; // ��������� �� �����

TPolinom TPolinom::operator-(TMonom monom){
	int a = monom.coef;
	a *= -1;
	monom.SetCoef(a);
	TPolinom p(*this);
	p.AddMonom(monom);
	return p;

}

TPolinom TPolinom::SubMonom(TMonom monom) {
	
	int a = monom.coef;
	a *= -1;
	monom.SetCoef(a);
	this->AddMonom(monom);
	
	return *this;
};
// ��������� ������
TPolinom TPolinom::operator- (TPolinom& other) {
	other.Reset();
	TPolinom p(*this);
	while (!other.IsEnd())
	{
		p.SubMonom(other.GetCurrentItem());
		other.GoNext();
	}
	p.SubMonom(other.GetCurrentItem());
	return p;
}; //  ��������� ��������

TPolinom TPolinom::SubPolinom(TPolinom& other) {

	other.Reset();
	
	while (!other.IsEnd())
	{
		SubMonom(other.GetCurrentItem());
		other.GoNext();
	}
	SubMonom(other.GetCurrentItem());

	return *this;
}; //  ��������� ��������

TPolinom TPolinom::operator/(TPolinom& other)
{

	TPolinom tmp;
	TPolinom ans(*this);
	ans.Division(other, tmp);
	if (!tmp.IsEmpty()) throw "impossible division operation without remainder";
	return ans;
}

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
		factor = (cp.GetCurrentItem() / fmn);
		
		ans.AddMonom(factor);

		tmp.MultMonom(factor);
		cp.SubPolinom(tmp);
		tmp = other;
		oper++;
		if (oper > (other.length+5)) break;
	}
	ost = cp;
	return ans;

}