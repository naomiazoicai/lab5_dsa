#include "ListIterator.h"
#include <exception>
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList &list) : list(list) {
//    initStack();
    first();
}
void ListIterator::first() {
//    initStack();
//    if (stackTop >= 0) {
//        currentIndex = stack[stackTop];
//    } else {
//        currentIndex = -1;
//    }
this->currentIndex = 0;
}

//void ListIterator::next() {
//    if (!valid()) {
//        throw exception();
//    }
//    if (currentNode->right != -1) {
//        currentNode = &list.elements[currentNode->right];
//        while (currentNode->left != -1) {
//            nodeStack.push(currentNode);
//            currentNode = &list.elements[currentNode->left];
//        }
//    } else if (!nodeStack.empty()) {
//        currentNode = nodeStack.top();
//        nodeStack.pop();
//    } else {
//        currentNode = nullptr;
//    }
//}
void ListIterator::next() {
//    if (valid()) {
//        stackTop--;
//        if (valid())
//            currentIndex = stack[stackTop];
//        else
//            currentIndex = -1;
//    } else {
//        throw exception();
//    }

    if (!this->valid())
    {
        throw exception();
    }
    this->currentIndex++;
}

TComp ListIterator::getCurrent() const{
//    if (valid()) {
//        return list.elements[currentIndex].element;
//    } else {
//        throw std::exception();
//    }
    if (!this->valid())
    {
        throw exception();
    }
    return list.getElement(this->currentIndex);
}

bool ListIterator::valid() const {
    return this->currentIndex != -1 && this->currentIndex < list.sizeBST;
}




//ListIterator::~ListIterator() = default;

void ListIterator::initStack() {
    stackSize = list.sizeBST;
    stack = new int[stackSize];
    stackTop = -1;
    if (list.root != -1) {
        inOrderToStack(list.root);
    }}

void ListIterator::inOrderToStack(int nodeIndex) {
    if (nodeIndex == -1) {
        return;
    }

    inOrderToStack(list.elements[nodeIndex].left);

    stackTop++;
    stack[stackTop] = nodeIndex;

    inOrderToStack(list.elements[nodeIndex].right);
}

