#pragma once
#include <iostream>
#include <string>
class TMonom 
{
public:
	double coef; // коэффициент монома
	int index; // индекс (свертка степеней)
	int x=0;
	int y=0;
	int z = 0;
	TMonom(double coef = 0, int degX = 0, int degY = 0, int degZ = 0);
	TMonom(std::string s);
	TMonom(TMonom& other);//если TMonom& то будет работать A m = k;

	void SetCoef(double cval) { coef = cval; }
	double GetCoef(void) { return coef; }
	void SetDeg(int X, int Y, int Z) { x = X; y = Y; z = Z; }

	void SetIndex(int ival) { index = ival; x = ival / 100; y = (ival / 10) % 10; z = ival % 10; }
	int GetIndex(void) { return index; }
	TMonom operator+(TMonom other);
	friend TMonom operator*(double c, TMonom other);
	friend TMonom operator/(double c, TMonom other);
	TMonom operator-(TMonom other);
	TMonom operator/(TMonom other);
	TMonom operator*(TMonom other);
	double calculate(double X=0, double Y = 0, double Z = 0);
	bool operator==(TMonom& other) { 
		return ((x==other.x)&&(y==other.y)&&(z==other.z) && (coef == other.coef));
	}
	bool CanSum(TMonom other) {

		return ((x == other.x) && (y == other.y) && (z == other.z));
	}
	bool operator==(const TMonom& other) {
		if (this == &other) return true;
		return ((x == other.x) && (y == other.y) && (z == other.z) && (coef == other.coef));
	}
	bool operator>(const TMonom& other);

	bool operator<(const TMonom& other);

	TMonom operator=(const TMonom& other);

	friend std::ostream& operator<<(std::ostream& os, const TMonom& obj) {
		if (&obj == nullptr) { return os; }
		if (obj.coef >= 0) os << "+";
		os << obj.coef;
		int a = obj.index;
		if ((obj.x != 0) && (obj.x != 1)) { os<<"X^"; os<< std::to_string(obj.x); }
		if (obj.x == 1)  os<<"X";

		if ((obj.y != 0) && (obj.y != 1)) { os << "Y^"; os << std::to_string(obj.y); }
		if (obj.y == 1)  os << "Y";
	
		if ((obj.z != 0) && (obj.z != 1)) { os << "Z^"; os << std::to_string(obj.z); }
		if (obj.z == 1)  os << "Z";
		return os;
	}

	TMonom derivative();
	friend void derivative(TMonom& other) { other = other.derivative(); }

	TMonom derivative(char md);
	friend void derivative(TMonom& other, char md) { other = other.derivative(md); }

	TMonom integral();
	friend void integral(TMonom& other) { other = other.integral(); }

	TMonom integral(char md);
	friend void integral(TMonom& other,char md) { other = other.integral(md); }

private:
	double St(int st, double c);
};

TMonom::TMonom(double coef, int degX, int degY, int degZ) {
	this->coef = coef;
	x = degX;
	y = degY;
	z = degZ;
	this->index = (degX%10) * 100 + (degY%10) * 10 + (degZ%10);//just in case
}
TMonom::TMonom(string s) {
	if (s == "") {
		index = 0;
		coef = 0;
		z = 0;
		y = 0;
		x = 0;
		return; }
	string str = s;
	for (int i = 0; i < str.size(); i++) str[i] = ' ';

	int tmp = 0;
	for (int i = 0; i < s.size(); i++) {
		switch (s[i])
		{
		case 'x': { str[tmp++] = 'X'; break; }
		case 'y': { str[tmp++] = 'Y'; break; }
		case 'z': { str[tmp++] = 'Z'; break; }
		case '-': { str[tmp++] = s[i]; break; }
		case '+': { str[tmp++] = s[i]; break; }
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

		if (c == 'X') { t = 100; index += 100; x+= 1; }
		if (c == 'Y') { t = 10; index += 10; y += 1; }
		if (c == 'Z') { t = 1; index += 1; z += 1; }

		if ((c >= '0') && (c <= '9')) {
			size_t d = 0;
			double a = stod(&str[i], &d);
			
			if (t == 0) { coef = (p * a); t = -1; i += d; p = 1; continue; }

			index += (a-1);
			if (t==100) x += a*p-1;
			if (t==10) y += a*p-1;
			if (t==1) z += a*p-1;
			p = 1;
			//std::cout << " MONOM" << x<<y<<z <<endl;
			i += d;
			continue;
		}
		i++;
	}

}

TMonom::TMonom(TMonom& other)
{
	coef = other.coef;
	index = other.index;
	x = other.x;
	y = other.y;
	z = other.z;

}

bool TMonom::operator>(const TMonom& other) {
	if (x != other.x) return(x > other.x);
	if (y != other.y) return(y > other.y);
	if (z != other.z) return(z > other.z);
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
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
};

TMonom TMonom::operator+(TMonom other) {
	if ((x!=other.x)||(y!=other.y)||(z!=other.z)) throw "different degrees";
	TMonom ans(*this);
	ans.SetCoef(coef + other.coef);
	return ans;

};
TMonom TMonom::operator-(TMonom other) {
	if ((x != other.x) || (y != other.y) || (z != other.z)) throw "different degrees";
	TMonom ans(*this);
	ans.SetCoef(coef - other.coef);
	return ans;

};
TMonom TMonom::operator/(TMonom other) {
	TMonom ans(*this);
	if (other.coef == 0) throw "division by 0";
	/*std::cout << "coef1 " << coef;
	std::cout << "coef2 " << other.coef;*/
	ans.coef = coef / other.coef; //std::cout << "coef " << ans.coef;
	ans.index -=other.index;
	ans.x -= other.x;
	ans.y -= other.y;
	ans.z -= other.z;
	return ans;
};
TMonom TMonom::operator*(TMonom other) {
	TMonom ans(*this);
	ans.SetCoef(coef * other.coef);
	ans.index = index + other.index;
	ans.x += other.x;
	ans.y += other.y;
	ans.z += other.z;
	return ans;
}
double TMonom::calculate(double X, double Y, double Z)
{
	if ((coef==0)||(X==0)||(Y==0)||(Z==0)) return 0.0;
	double ob=1;
	if (x!=0) ob *= St(x,X);
	if (y!=0) ob *= St(y, Y);
	if (z!=0) ob *= St(z, Z);
	ob *= coef;
	return ob;
}
TMonom operator*(double c, TMonom other) {
	TMonom ans;
	ans.SetCoef(other.coef*c);
	ans.index = other.index;
	ans.x = other.x;
	ans.y = other.y;
	ans.z = other.z;
	return ans;
};
TMonom operator/(double c, TMonom other) {
	TMonom ans;
	ans.SetCoef(other.coef / c);
	ans.index = other.index;
	ans.x = other.x;
	ans.y = other.y;
	ans.z = other.z;
	return ans;
};

double TMonom::St(int st, double c) {

	double p = 1;
	int r = (st<0);
	if (st < 0) st = -1 * st;
	for (int i = 0; i < st;) {
		if ((i * 2 < st) && (i != 0)) {
			p *= p;
			i *= 2;
		}
		else { p *= c; i++; }
	}
	if (r) p = r / p;
	return p;
}

TMonom TMonom::derivative() {
	double c= coef;
	int X = x, Y = y, Z = z;
	c *= X * Y * Z;
	X -= 1;
	Y -= 1;
	Z -= 1;
	TMonom n(c, X,Y,Z);
	return n;
}

TMonom TMonom::integral() {
	double c = coef;
	int X = x, Y=y, Z=z;
	X += 1;
	Y += 1;
	Z += 1;
	if (X == 0) {	X = -2; c *= 2;}
	if (Y == 0) {Y = -2; c *= 2;}
	if (Z == 0) {Z = -2; c *= 2;}

	c /= (X*Y*Z);
	TMonom n(c, X,Y,Z);
	return n;
};

TMonom TMonom::derivative(char md)
{

	double c = coef;
	int X=x, Y=y, Z=z;
	switch (md)
	{
	case 'x':
	case 'X':
	{
		c *= X;
		X-= 1;
		break;
	}
	case 'y':
	case 'Y':
	{
		c *= Y;
		Y -= 1;
		break;
	}
	case 'z':
	case 'Z':
	{
		c *= Z;
		Z -= 1;
		break;
	}
	default:
		break;
	}
	return TMonom(c,X,Y,Z);
}

TMonom TMonom::integral(char md)
{
	double c = coef;
	int X = x, Y = y, Z = z;
	switch (md)
	{
	case 'x':
	case 'X':
	{
		X += 1;
		if (X == 0) throw " ln (|x|)";
		c /= X;
		break;
	}
	case 'y':
	case 'Y':
	{
		Y += 1;
		c /= Y;
		if (Y== 0) throw " ln (|y|)";
		break;
	}
	case 'z':
	case 'Z':
	{
		Z += 1;
		if (Z == 0) throw " ln (|z|)";
		c /= Z;
		break;
	}
	default:
		break;
	}
	return TMonom(c,X,Y,Z);
}