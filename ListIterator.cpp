#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;


///constructor
///complexity: Θ(n) worst, average and best
ListIterator::ListIterator(const SortedIndexedList& list) : list(list)
{
    this->currentValue = NULL_TCOMP;
    this->stackSize = 0;
    this->stack = new Node[list.sizeBST];
    int current = list.root;
    while (current != -1)
    {
        //in-order traversal
        this->stack[stackSize++] = list.tree[current];  //pushing the nodes onto the stack array
        current = list.tree[current].leftPos;   // iteratively going to the leftmost child of each node until reaching a leaf node
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize-1].element;    //top node of the stack, represents the first element in the sorted order
}

///the first element
///complexity: Θ(n) worst, average and best
void ListIterator::first()
{
    this->currentValue = NULL_TCOMP;
    this->stackSize = 0;
    int current = list.root;
    while (current != -1)
    {
        //in-order traversal
        this->stack[stackSize++] = list.tree[current];
        current = list.tree[current].leftPos;
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize - 1].element;  //top node of the stack, represents the first element in the sorted order

}

///the next element
///complexity: total: Θ(n), worst case Θ(n), average case Θ(log n), best case: Θ(1)
void ListIterator::next()
{
    if (!valid())
        throw exception();

    this->stackSize--;  //pop
    Node node = this->stack[stackSize]; //popped node

    if (node.rightPos != -1)    //if the popped node has a right child = there are additional elements in the sorted order to explore
    {
        int current = node.rightPos;
        while (current != -1)       //in-order traversal starting from the right child of the popped node until there are no more left children to explore
        {
            this->stack[stackSize++] = list.tree[current];  //push current node onto stack
            current = list.tree[current].leftPos;   //current becomes the left child
        }
    }
    if (this->stackSize)
        this->currentValue = stack[stackSize - 1].element;  //the element on top of the stack is the next element in the sorted order
    else
        this->currentValue = NULL_TCOMP;
}

///check if valid
///complexity: Θ(1) worst, average and best
bool ListIterator::valid() const
{
    return this->currentValue != NULL_TCOMP;
}

///current
///complexity: Θ(1) worst, average and best
TComp ListIterator::getCurrent() const
{

    return this->currentValue;
}
