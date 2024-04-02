#include <iostream>
#include "HashTblCh.h"
#include "unorderedArrayTable.h"
#include "table_test.h"
using namespace std;
int main()
{
    unorderedArrayTable<int> t(20);
    t.Insert("name1", 3);
}