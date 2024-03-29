#include <iostream>
#include "Tree.h"
#include "calculator.h"
#include "TPolinom.h"
void main() {
	Tree<Polinom<string, TPolinom>> t(20);
	Polinom<string, TPolinom> tmp;
	tmp.name = "name1";
	tmp.polinom = TPolinom("3XYZ - 2X2YZ");
	t.Add(tmp);
	tmp.name = "name2";
	tmp.polinom = TPolinom("2X2YZ");
	t.Add(tmp);
	TCalculator cl(&t);
	cl.SetExpression("name1/name2");
	double ans = cl.Calc(1,1,1);
	cout << ans;

	char c;
	cin >> c;



}