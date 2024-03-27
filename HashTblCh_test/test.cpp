#include <iostream>

#include "pch.h"
#include "../table/HashTblCh.h"
#include "../polinom/TPolinom.h"

TEST(HashTblCh, Created_table_is_empty) {
	HashTblCh<Polinom<string, int>> a(20);
	EXPECT_EQ(a.IsEmpty(), 1);
}

TEST(HashTblCh, table_is_not_empty) {
	HashTblCh<Polinom<string, int>> a(20);
	Polinom<string, int> p;
	p.polinom = 10; p.name = "name1";
	a.Add(p);
	EXPECT_EQ(a.IsEmpty(), 0);
}

TEST(HashTblCh, right_size) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	p.name = "name2";
	a.Add(p);
	EXPECT_EQ(2, a.GetDataCount());

}

TEST(HashTblCh, can_delete) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	p.name = "name2";
	a.Add(p);
	a.Delete("name2");
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(HashTblCh, if_key_coincide_then_not_add) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p);
	a.Add(p);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(HashTblCh, can_be_full) {
	HashTblCh<Polinom<string, TPolinom>> a(2);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p); p.name = "name2";
	a.Add(p);
	EXPECT_EQ(a.IsFull(), 1);
}

TEST(HashTblCh, reset_op) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
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
TEST(HashTblCh, can_find) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p, p2;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k; 
	k.AddMonom(TMonom(3, 3, 3, 3)); 
	p2.name = "name10";
	p2.polinom = k;
	a.Add(p2);
	p.name = "name8";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); a.GoNext();
	p = a.Find("name10");
	bool b = (p.polinom == p2.polinom);
	EXPECT_EQ(b,1);
}

TEST(HashTblCh, can_go) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
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
	string s1 = a.GetKey(),s2;
	try {
		for (int i = 0; (i < 5); i++) {
			a.GoNext();
			s2 = a.GetKey();
			if (s1 == s2) { b = 1; break; }
			s1 = s2;
		}
	}
	catch (...) { b = 1; }
	EXPECT_EQ(0, b);
}

TEST(HashTblCh, copy_has_own_memory) {
	HashTblCh<Polinom<string, TPolinom>> a(20);
	Polinom<string, TPolinom> p;
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	p.polinom = k;  p.name = "name1";
	a.Add(p); p.name = "name2";
	a.Add(p); p.name = "name3";
	a.Add(p); p.name = "name4";
	a.Add(p); p.name = "name5";
	a.Add(p);
	HashTblCh<Polinom<string, TPolinom>> t = a;
	p.name = "name6"; 
	a.Add(p);

	bool b = (t == a);
	EXPECT_EQ(b,0);
}