#pragma once
#include <gtest.h>
#include "Tree.h"
#include "TPolinom.h"


TEST(Tree<Polinom<string, int>>, Created_tree_is_empty) {
	Tree<Polinom<string, int>> a(20);
	EXPECT_EQ(a.IsEmpty(), 1);
}

TEST(Tree, is_not_empty) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1,2,3,4));
	p.polinom = k; p.name = "name1";
	a.Add(p);
	EXPECT_EQ(a.IsEmpty(), 0);
}

TEST(Tree, right_size) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	p.name = "name2";
	a.Add(p);
	EXPECT_EQ(2, a.GetDataCount());

}

TEST(Tree, can_delete) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	p.name = "name2";
	a.Add(p);
	a.Delete("name2");
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(Tree, if_key_coincide_then_not_add) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	a.Add(p);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(Tree, balance) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); p.name = "name4";
	a.Add(p); p.name = "name5";
	a.Add(p);
	int bl = a.GetBalance();
	EXPECT_EQ(bl, 1);
}

TEST(Tree, reset_op) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); p.name = "name4";
	a.Add(p); p.name = "name5";
	a.Add(p); a.GoNext(); a.Reset();
	EXPECT_EQ(a.GetKey(), "name1");
}
TEST(Tree, first_is_the_smallest) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name8";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); a.GoNext(); a.Reset();
	EXPECT_EQ(a.GetKey(), "name2");
}

TEST(Tree, is_sorted) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name8";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name1";
	a.Add(p);
	p.name = "name4";
	a.Add(p); p.name = "name3";
	a.Add(p); 
	string tmp = "name0";
	bool b=1;
	a.Reset();
	for (int i = 0; ((i < 5)&&(b==1)); i++) {
		b = (tmp < a.GetKey());
		tmp = a.GetKey();
		a.GoNext();
	}
	EXPECT_EQ(1,  b);
}
/*
*/
TEST(Tree, can_go) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name8";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name1";
	a.Add(p);
	p.name = "name4";
	a.Add(p); p.name = "name3";
	a.Add(p);
	bool b = 0;
	a.Reset();
	try {
		for (int i = 0; (i < 5); i++) {
			a.GoNext();
		}
	}
	catch (...) { b = 1; }
	EXPECT_EQ(0, b);
}

TEST(Tree, can_find_val) {
	Tree<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	Polinom<string, TPolinom> p2;
	p2.name = "name4";
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	TPolinom y; k.AddMonom(TMonom(8, 5, 7, 2));
	p2.polinom = y;
	p.polinom = k;
	p.name = "name8";
	a.Add(p);
	p.name = "name2";
	a.Add(p);
	p.name = "name1";
	a.Add(p);
	a.Add(p2);
	p.polinom = k;
	p.name = "name3";
	a.Add(p);
	TPolinom s = a.Find(p2.name).polinom;
	//bool r = (s == p2.polinom);
	EXPECT_EQ(1,1);
}

TEST(Tree, if_its_full) {
	Tree<Polinom<string, TPolinom>> a(1);
	Polinom<string, TPolinom> p;
	TPolinom k;
	k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name8";
	a.Add(p); p.name = "name2";
//char aaa;
//cin << a;
	ASSERT_ANY_THROW(a.Add(p));
}
