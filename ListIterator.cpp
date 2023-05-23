//#include "ListIterator.h"
//#include "SortedIndexedList.h"
//#include <iostream>
//
//using namespace std;
//
//ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
//	currentIndex = 0;
//}
//
//void ListIterator::first(){
//	currentIndex = 0;
//}
//
//void ListIterator::next(){
//	if (!valid())
//    {
//        throw exception();
//    }
//    currentIndex++;
//}
//
//bool ListIterator::valid() const{
//	return currentIndex < list.size();
//}
//
//TComp ListIterator::getCurrent() const{
//    if (!valid())
//    {
//        throw exception();
//    }
//    return list.getElement(currentIndex);
//}
//
//
#include "ListIterator.h"
#include "SortedIndexedList.h"
#include "stack"

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    stack<Node*> nodeStack;
    currentNode = list.elements[list.root];
    while (currentNode != nullptr) {
        nodeStack.push(currentNode);
        currentNode = list.elements[currentNode->left];
    }
    if (!nodeStack.empty()) {
        currentNode = nodeStack.top();
        nodeStack.pop();
    }
    this->nodeStack = nodeStack;
}

void ListIterator::first() {
    stack<Node*> emptyStack;
    swap(nodeStack, emptyStack);
    currentNode = list.elements[list.root];
    while (currentNode != nullptr) {
        nodeStack.push(currentNode);
        currentNode = list.elements[currentNode->left];
    }
    if (!nodeStack.empty()) {
        currentNode = nodeStack.top();
        nodeStack.pop();
    }
}

void ListIterator::next() {
    if (!valid()) {
        throw exception();
    }
    if (currentNode->right != -1) {
        currentNode = list.elements[currentNode->right];
        while (currentNode != nullptr) {
            nodeStack.push(currentNode);
            currentNode = list.elements[currentNode->left];
        }
    }
    if (!nodeStack.empty()) {
        currentNode = nodeStack.top();
        nodeStack.pop();
    }
}

bool ListIterator::valid() const {
    return currentNode != nullptr;
}

TComp ListIterator::getCurrent() const {
    if (!valid()) {
        throw exception();
    }
    return currentNode->element;
}
