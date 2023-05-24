#pragma once
#include "SortedIndexedList.h"



//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	int currentIndex;
    int* stack;
    int stackTop;
    int stackSize;

    void initStack();
    void inOrderToStack(int nodeIndex);

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;


};


