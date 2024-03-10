#pragma once
#include <iostream>
#include <string>
struct TMonom
{
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)


	TMonom(double coef = 0, int degX = 0, int degY = 0, int degZ = 0);
	TMonom(string s);
	void SetCoef(int cval) { coef = cval; }
	double GetCoef(void) { return coef; }

	void SetIndex(int ival) { index = ival; }
	int GetIndex(void) { return index; }
	TMonom operator+(TMonom other);
	friend TMonom operator*(double c, TMonom other);
	friend TMonom operator/(double c, TMonom other);
	TMonom operator-(TMonom other);
	TMonom operator/(TMonom other);
	TMonom operator*(TMonom other);

	bool operator==(TMonom& other) { 
		return ((index == other.index) && (coef == other.coef));
	}

	bool operator==(const TMonom& other) {
		return ((index == other.index) && (coef == other.coef));
	}
	bool operator>(const TMonom& other);

	bool operator<(const TMonom& other);

	TMonom operator=(const TMonom& other);

	friend std::ostream& operator<<(std::ostream& os, const TMonom& obj) {
		if (&obj == nullptr) { return os; }
		os << obj.coef;
		int a = obj.index;
		if ((a / 100 != 0) && (a / 100 != 1)) { os<<"X^"; os<< std::to_string(a / 100); }
		if (a / 100 == 1)  os<<"X"; 
		a %= 100;
		//std::cout << a;
		if ((a / 10 != 0) && (a / 10 != 1)) { os << "Y^"; os << std::to_string(a / 10); }
		if (a / 10 == 1) os << "Y";
		a %= 10;
		if ((a != 0) && (a != 1)) { os << "Z^"; os << std::to_string(a); }
		if (a == 1) os << "Z"; 
		return os;
	}
};
TMonom::TMonom(double coef, int degX, int degY, int degZ) {
	this->coef = coef;
	this->index = (degX%10) * 100 + (degY%10) * 10 + (degZ%10);//just in case
}
TMonom::TMonom(string s) {
	if (s == "") {
		index = 0;
		coef = 0;
		return; }
	string str = s;
	int tmp = 0;
	for (int i = 0; i < s.size(); i++) {
		switch (s[i])
		{
		case 'x': { str[tmp++] = 'X'; break; }
		case 'y': { str[tmp++] = 'Y'; break; }
		case 'z': { str[tmp++] = 'Z'; break; }
		default:
		if (((s[i] >= '0') && (s[i] <= '9')) || (s[i] == 'X') || (s[i] == 'Y') || (s[i] == 'Z')) str[tmp++] = s[i]; 
		}
		}
	for (; tmp < s.size(); tmp++) str[tmp] = ' ';
	index = 0;
	coef = 1;
	int p = 1;//-coef or +
	int i = 0;
	int t = 0;
	char c = ' ';
	while (i < str.size()) {

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
			//std::cout <<"\nnumeric  "<< str[i] << "  " << i<<"   "<<a;
			if (t == 0) coef = (p * a);
			index += t * (a-1);
			i += d;
			continue;
		}
		if (c == 'X') { t = 100; index += 100; }
		if (c == 'Y') { t = 10; index += 10; }
		if (c == 'Z') { t = 1; index += 1; }
		i++;
	}

}

bool TMonom::operator>(const TMonom& other) {
	/*int s1 = 0, s2 = 0, tmp1 = index, tmp2 = other.index;
	while ((tmp1 != 0) || (tmp2 != 0)) {
		s1 += tmp1 % 10; tmp1 /= 10;
		s2 += tmp2 % 10; tmp2 /= 10;
	}
	if (s1>s2) return 1;
	if (s2 > s1) return 0;*/
	if (index > other.index) return 1;
	if (index < other.index) return 0;
	if (coef>other.coef) return 1;
	return 0;

}

bool TMonom::operator<(const TMonom& other) {
	if (*this == other) return 0;
	if (*this > other) return 0;
	return 1;
};
TMonom  TMonom::operator=(const TMonom& other) {
	if (*this == other) return *this;
	this->coef = other.coef;
	this->index = other.index;
	return *this;
};

TMonom TMonom::operator+(TMonom other) {
	if (index != other.index) throw "different degrees";
	TMonom ans;
	ans.SetCoef(coef + other.coef);
	ans.index = index;
	return ans;

};
TMonom TMonom::operator-(TMonom other) {
	if (index != other.index) throw "different degrees";
	TMonom ans;
	ans.SetCoef(coef - other.coef);
	ans.index = index;
	return ans;

};
TMonom TMonom::operator/(TMonom other) {
	TMonom ans;
	if (other.coef == 0) throw "division by 0";
	ans.SetCoef(coef/other.coef);
	ans.index = index-other.index;
	return ans;
};
TMonom TMonom::operator*(TMonom other) {
	TMonom ans;
	ans.SetCoef(coef * other.coef);
	ans.index = index + other.index;
	return ans;
};
TMonom operator*(double c, TMonom other) {
	TMonom ans;
	ans.SetCoef(other.coef*c);
	ans.index = other.index;
	return ans;
};
TMonom operator/(double c, TMonom other) {
	TMonom ans;
	ans.SetCoef(other.coef / c);
	ans.index = other.index;
	return ans;
};