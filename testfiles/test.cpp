#include <iostream>
#include "../gtest/gtest.h"
#include "Tree.h"
#include "HashTblCh.h"
#include "TPolinom.h"

using namespace std;

TEST(Tree, Created_tree_is_empty) {
	Tree<int> a(20);
	EXPECT_EQ(a.IsEmpty(), 1);
}

TEST(Tree, is_not_empty) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1", k);
	EXPECT_EQ(a.IsEmpty(), 0);
}

TEST(Tree, right_size) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1", k);
	a.Insert("name2",k);
	EXPECT_EQ(2, a.GetDataCount());

}

TEST(Tree, can_delete) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1",k);
	a.Insert("name2",k);
	a.Delete("name2");
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(Tree, if_key_coincide_then_not_add) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1", k);
	a.Insert("name1", k);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(Tree, balance) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1",k); 
	a.Insert("name2", k);
	a.Insert("name3", k);
	a.Insert("name4", k);
	a.Insert("name5", k);
	int bl = a.GetBalance();
	EXPECT_EQ(bl, 1);
}

TEST(Tree, reset_op) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name1", k);
	a.Insert("name2", k);
	a.Insert("name3", k);
	a.Insert("name4", k);
	a.Insert("name5", k);
	 a.GoNext(); a.Reset();
	EXPECT_EQ(a.GetKey(), "name1");
}
TEST(Tree, first_is_the_smallest) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name8",k);
	a.Insert("name2", k); 
	a.Insert("name3", k); a.GoNext(); a.Reset();
	EXPECT_EQ(a.GetKey(), "name2");
}

TEST(Tree, is_sorted) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name8",k); 
	a.Insert("name2", k); 
	a.Insert("name1", k);
	a.Insert("name4", k); 
	a.Insert("name3", k);
	string tmp = "name0";
	bool b = 1;
	a.Reset();

	for (int i = 0; ((i < 5) && (b == 1)); i++) {
		b = (tmp < a.GetKey());
		tmp = a.GetKey();
		a.GoNext();
	}
	EXPECT_EQ(1, b);
}
/*
*/
TEST(Tree, can_go) {
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name8",k); 
	a.Insert("name2", k); 
	a.Insert("name1", k);
	a.Insert("name4", k); 
	a.Insert("name3", k);
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
	Tree<TPolinom> a(20);
	TPolinom k; k.AddMonom(TMonom(1, 2, 3, 4));
	TPolinom y; k.AddMonom(TMonom(8, 5, 7, 2));
	a.Insert("name8", k);
	a.Insert("name2", k);
	a.Insert("name1", k);
	a.Insert("name4", y);
	a.Insert("name3", k);
	TPolinom s = a.Find("name4");
	bool r = (s == y);
	EXPECT_EQ(1, 1);
}

TEST(Tree, if_its_full) {
	Tree< TPolinom> a(1);
	TPolinom k;
	k.AddMonom(TMonom(1, 2, 3, 4));
	a.Insert("name8", k);
	ASSERT_ANY_THROW(a.Insert("name2", k));
}



TEST(HashTblCh, Created_table_is_empty) {
	HashTblCh<int> a(20);
	EXPECT_EQ(a.IsEmpty(), 1);
}

TEST(HashTblCh, table_is_not_empty) {
	HashTblCh<int> a(20);
	a.Insert("name1",10);
	EXPECT_EQ(a.IsEmpty(), 0);
}

TEST(HashTblCh, right_size) {
	HashTblCh<int> a(20);
	a.Insert("name1", 1);
	a.Insert("name2", 2);
	EXPECT_EQ(2, a.GetDataCount());

}

TEST(HashTblCh, can_delete) {
	HashTblCh<int> a(20);
	a.Insert("name1", 10);
	a.Insert("name2", 2);
	a.Delete("name2");
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(HashTblCh, if_key_coincide_then_not_add) {
	HashTblCh<int> a(20);
	a.Insert("name1", 1);
	a.Insert("name1", 1);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(HashTblCh, can_be_full) {
	HashTblCh<int> a(2);
	a.Insert("name1", 1); 
	a.Insert("name2", 2);
	EXPECT_EQ(a.IsFull(), 1);
}

TEST(HashTblCh, reset_op) {
	HashTblCh<int> a(20);
	a.Insert("name1", 17);
	a.Insert("name2", 17);
	a.Insert("name3", 11);
	a.Insert("name4", 12);
	a.Insert("name5", 1);
	a.GoNext(); a.Reset();
	EXPECT_EQ(a.GetKey(), "name1");
}
TEST(HashTblCh, can_find) {
	HashTblCh<int> a(20);
	a.Insert("name1", 0);
	a.Insert("name2", 0);
	a.Insert("name3", 0);
	a.Insert("name4", 1);
	a.Insert("name5", 0);
	bool b = a.Find("name4");
	EXPECT_EQ(b, 1);
}

TEST(HashTblCh, can_go) {
	HashTblCh<int> a(20);
	a.Insert("name1", 0);
	a.Insert("name2", 0);
	a.Insert("name3", 0);
	a.Insert("name4", 1);
	a.Insert("name5", 0);
	a.Reset();
	string s1 = a.GetKey(), s2;
	bool b = 0;
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
	HashTblCh<int> a(20);
	a.Insert("name1", 0);
	a.Insert("name2", 0);
	a.Insert("name3", 0);
	a.Insert("name4", 1);
	a.Insert("name5", 0);
	HashTblCh<int> t = a;
	a.Insert("name6", 0);

	bool b = (t == a);
	EXPECT_EQ(b, 0);
	char aaa;
	std::cin >> aaa;
}