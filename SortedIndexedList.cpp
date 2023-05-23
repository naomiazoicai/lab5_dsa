#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

///constructor
SortedIndexedList::SortedIndexedList(Relation r) {
    capacity = 10;
    elements = new Node[capacity];
    root = -1;
    sizeBST = 0;
    this->r = r;

}

///returns the size of the list
int SortedIndexedList::size() const {
    return sizeBST;
}

///checks if the list is empty
bool SortedIndexedList::isEmpty() const {
	return sizeBST == 0;
}

///returns an element from a position
///throws exception if the position is not valid
TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= sizeBST)
    {
        throw exception();
    }

    int currentNode = root;
    while (currentNode != -1)
    {
        int currentPos = elements[currentNode].leftSubtreeSize;
        if (currentPos == i)
        {
            return elements[currentNode].element;
        }
        else if (i < currentPos)
        {
            currentNode = elements[currentNode].left;
        }
        else
        {
            currentNode = elements[currentNode].right;
            i -= currentPos + 1;
        }
    }
    throw exception();
}

///removes an element from a given position
///returns the removed element
///throws an exception if the position is not valid
TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= sizeBST)
        throw std::out_of_range("Invalid position");

    int currentNode = root;
    int parent = -1;
    while (currentNode != -1) {
        int currentPos = elements[currentNode].leftSubtreeSize;
        if (currentPos == i)
            break;
        else if (i < currentPos) {
            elements[currentNode].leftSubtreeSize--;
            parent = currentNode;
            currentNode = elements[currentNode].left;
        } else {
            currentNode = elements[currentNode].right;
            i -= currentPos + 1;
            parent = currentNode;
        }
    }

    TComp removedElement = elements[currentNode].element;

    if (elements[currentNode].left == -1 && elements[currentNode].right == -1) {
        // Node has no children
        if (parent == -1)
            root = -1;
        else if (elements[parent].left == currentNode)
            elements[parent].left = -1;
        else
            elements[parent].right = -1;
    } else if (elements[currentNode].left == -1) {
        // Node has only right child
        int rightChild = elements[currentNode].right;
        if (parent == -1)
            root = rightChild;
        else if (elements[parent].left == currentNode)
            elements[parent].left = rightChild;
        else
            elements[parent].right = rightChild;
    } else if (elements[currentNode].right == -1) {
        // Node has only left child
        int leftChild = elements[currentNode].left;
        if (parent == -1)
            root = leftChild;
        else if (elements[parent].left == currentNode)
            elements[parent].left = leftChild;
        else
            elements[parent].right = leftChild;
    } else {
        // Node has both left and right children
        int successor = elements[currentNode].right;
        int successorParent = currentNode;

        while (elements[successor].left != -1) {
            elements[successor].leftSubtreeSize--;
            successorParent = successor;
            successor = elements[successor].left;
        }

        elements[currentNode].element = elements[successor].element;

        if (successorParent == currentNode)
            elements[successorParent].right = elements[successor].right;
        else
            elements[successorParent].left = elements[successor].right;
    }

    sizeBST--;
    return removedElement;
}


///searches for an element and returns the first position where the element appears or -1 if the element is not in the list
int SortedIndexedList::search(TComp e) const {
	int currentNode = root;
    int position = 0;

    while (currentNode != -1)
    {
        if (r(e, elements[currentNode].element))
        {
            currentNode = elements[currentNode].left;
        }
        else if (r(elements[currentNode].element, e))
        {
            position += (elements[currentNode].leftSubtreeSize + 1);
            currentNode = elements[currentNode].right;
        }
        else
        {
           position += + elements[currentNode].leftSubtreeSize;
           return position+1;
        }
    }
    return -1;
}

///adds an element to a given position
///throws an exception if the position is not valid
void SortedIndexedList::add(TComp e) {
    if (sizeBST == capacity) {
        // Resize the elements array if it is full
        capacity *= 2;
        Node* newElements = new Node[capacity];
        for (int i = 0; i < sizeBST; i++)
            newElements[i] = elements[i];
        delete[] elements;
        elements = newElements;
    }

    int newNode = sizeBST;
    elements[newNode].element = e;
    elements[newNode].left = -1;
    elements[newNode].right = -1;
    elements[newNode].leftSubtreeSize = 0;

    if (root == -1)
        root = newNode;
    else {
        int currentNode = root;
        int parent = -1;
        while (currentNode != -1) {
            parent = currentNode;
            if (r(e, elements[currentNode].element)) {
                elements[currentNode].leftSubtreeSize++;
                currentNode = elements[currentNode].left;
            } else {
                currentNode = elements[currentNode].right;
            }
        }

        if (r(e, elements[parent].element))
            elements[parent].left = newNode;
        else
            elements[parent].right = newNode;
    }

    sizeBST++;
}


///returns an iterator set to the first element of the list or invalid if the list is empty
ListIterator SortedIndexedList::iterator()
{
	return ListIterator(*this);
}

///destructor
SortedIndexedList::~SortedIndexedList()
{
    destroyTree(root);
	delete [] elements;
}

void SortedIndexedList::destroyTree( int node)
{
    if (node != -1)
    {
        destroyTree(elements[node].left);
        destroyTree(elements[node].right);
        elements[node].left = -1;
        elements[node].right = -1;

    }
}
