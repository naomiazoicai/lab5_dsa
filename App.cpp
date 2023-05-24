#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}
//void SortedIndexedList::add(TComp e) {
//    if (this->firstFree == -1) {
//        throw std::exception(); // Throw an exception if there are no more free nodes
//    }
//
//    int newNode = this->firstFree;
//    this->firstFree = this->elements[newNode].right;
//
//    this->elements[newNode].element = e;
//    this->elements[newNode].left = -1;
//    this->elements[newNode].right = -1;
//
//    if (this->root == -1) {
//        this->root = newNode;
//        this->elements[newNode].leftSubtreeSize = 0;
//        return;
//    }
//
//    int currentNode = this->root;
//    int parent = -1;
//    while (currentNode != -1) {
//        parent = currentNode;
//        this->elements[parent].leftSubtreeSize++;
//
//        if (e < this->elements[currentNode].element) {
//            currentNode = this->elements[currentNode].left;
//        } else {
//            currentNode = this->elements[currentNode].right;
//        }
//    }
//
//    if (e < this->elements[parent].element) {
//        this->elements[parent].left = newNode;
//    } else {
//        this->elements[parent].right = newNode;
//    }
//
//    this->elements[newNode].leftSubtreeSize = 0;
//    this->sizeBST++;
//}

//
//TComp SortedIndexedList::remove(int i) {
//    if (i < 0 || i >= this->sizeBST) {
//        throw std::exception();
//    }
//
//    int current = this->root;
//    int parent = -1;
//    int position = 0;
//    while (current != -1) {
//        int currentLeftSubtreeSize = this->elements[current].leftSubtreeSize;
//        if (i == position + currentLeftSubtreeSize) {
//            break;
//        }
//        parent = current;
//        if (i < position + currentLeftSubtreeSize) {
//            current = this->elements[current].left;
//        } else {
//            position = position + currentLeftSubtreeSize + 1;
//            current = this->elements[current].right;
//        }
//    }
//
//    TComp deletedElement = this->elements[current].element;
//
//    if (this->elements[current].left == -1 && this->elements[current].right == -1) {
//        if (parent == -1) {
//            this->root = -1;
//        } else if (this->elements[parent].left == current) {
//            this->elements[parent].left = -1;
//        } else {
//            this->elements[parent].right = -1;
//        }
//        delete[] this->elements;
//        this->elements = nullptr;
//        this->sizeBST--;
//    } else if (this->elements[current].left == -1 || this->elements[current].right == -1) {
//        int descendant;
//        if (this->elements[current].left == -1) {
//            descendant = this->elements[current].right;
//        } else {
//            descendant = this->elements[current].left;
//        }
//
//        if (parent == -1) {
//            this->root = descendant;
//        } else if (this->elements[parent].left == current) {
//            this->elements[parent].left = descendant;
//        } else {
//            this->elements[parent].right = descendant;
//        }
//        delete[] this->elements;
//        this->elements = nullptr;
//        this->sizeBST--;
//    } else {
//        int successor = this->elements[current].right;
//        int successorParent = current;
//        while (this->elements[successor].left != -1) {
//            successorParent = successor;
//            successor = this->elements[successor].left;
//        }
//
//        this->elements[current].element = this->elements[successor].element;
//
//        if (this->elements[successorParent].left == successor) {
//            this->elements[successorParent].left = this->elements[successor].right;
//        } else {
//            this->elements[successorParent].right = this->elements[successor].right;
//        }
//
//        delete[] this->elements;
//        this->elements = nullptr;
//        this->sizeBST--;
//    }
//
//    return deletedElement;
//}