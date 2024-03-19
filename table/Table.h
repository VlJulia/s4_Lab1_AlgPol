#pragma once
#include <iostream>
#include "..\polinom\TPolinom.h"
template <class Tn, class Tp>
struct  Polinom
{
	Tn name;
	Tp* polinom;
};

template <class Tn, class Tp>
class Table
{
protected: unsigned int size=0;
public:
	virtual bool AddPolinom(Polinom<Tn,Tp> pol);
	virtual bool DelPolinom(std::string polinom_name);
	virtual Polinom<Tn,Tp> FindPolinom(std::string polinom_name);
	virtual bool PolinomExist(std::string polinom_name);
};

