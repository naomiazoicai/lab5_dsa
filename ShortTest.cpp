#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testEquality() {
    SortedIndexedList list1(relation1);
    SortedIndexedList list2(relation1);

    list1.add(1);
    list1.add(2);
    list1.add(3);

    list2.add(1);
    list2.add(2);
    list2.add(3);

    assert(list1 == list2);
    cout<<"bravo1"<<endl;

    list2.remove(1);
    assert(!(list1 == list2));
    cout<<"bravo2"<<endl;

    list2.add(4);
    assert(!(list1 == list2));
    cout<<"bravo3"<<endl;


    SortedIndexedList list3(relation1);
    list3.add(1);
    list3.add(2);

    assert(!(list1 == list3));
    cout<<"bravo4"<<endl;
}
