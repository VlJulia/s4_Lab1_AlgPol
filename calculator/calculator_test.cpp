#include <iostream>
#include "unorderedArrayTable.h"
#include "calculator.h"
#include "TPolinom.h"
void main() {
	unorderedArrayTable<TPolinom> t;
	t.Insert("nm1", TPolinom("XYZ -2XYZ^6"));
	t.Insert("nm2", TPolinom("2XYZ^2 - 2X^2YZ"));
	t.Insert("nm3", TPolinom("4X^3YZ - 2X^3YZ"));
	TCalculator<TPolinom> a(&t);
	cout << t.Find("nm1")<<endl;
	cout << t.Find("nm2")<<endl;
	cout << t.Find("nm1") + t.Find("nm2") << endl;
	cout << t.Find("nm2").derivative('X')<<endl;
	TPolinom ost;
	TPolinom tmp = t.Find("nm3").Division(t.Find("nm2").derivative('X'), ost);
	cout << " hkdfdfkj  " << tmp << "+ "<<ost << endl;
	a.SetExpression(" (nm3 / $der_x(nm2)) + nm1*3 ");

	cout << endl << endl << endl;
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	a.ToPostfix();
	cout << "   POSTF " << a.GetPostfix()<<endl;
	TPolinom yyy;
	double ans = a.Calc(yyy,1,2,1);
	cout << yyy << " = ";
	cout << ans;
	cin >> ans;
}