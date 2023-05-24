#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

///constructor
SortedIndexedList::SortedIndexedList(Relation r) {
    this -> capacity = 10;
    this -> elements = new Node[capacity];
    this -> root = -1;
    this -> sizeBST = 0;
    this -> r = r;
    this->firstFree = 0;


}

///returns the size of the list
int SortedIndexedList::size() const {
    if (root == -1)
    {
        return 0;
    }
    return  this -> sizeBST;
}

///checks if the list is empty
bool SortedIndexedList::isEmpty() const {
	return  this -> sizeBST == 0;
}

///returns an element from a position
///throws exception if the position is not valid
TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >=  this -> sizeBST)
    {
        throw exception();
    }

    int current = this->root;
    int position = 0;
    while (current != -1) {
        int currentLeftSubtreeSize = this->elements[current].leftSubtreeSize;
        if (i == position + currentLeftSubtreeSize) {
            return this->elements[current].element;
        }
        if (i < position + currentLeftSubtreeSize) {
            current = this->elements[current].left;
        } else {
            position = position + currentLeftSubtreeSize + 1;
            current = this->elements[current].right;
        }
    }

    throw exception();
}

///removes an element from a given position
///returns the removed element
///throws an exception if the position is not valid
//
//TComp SortedIndexedList::remove(int pos) {
//    if (pos < 0 || pos >= this->sizeBST) {
//        throw exception(); // Throw an exception if the position is not valid
//    }
//
//    int currentNode = this->root;
//    int prevNode = -1;
//    while (currentNode != -1 && pos != this->elements[currentNode].leftSubtreeSize) {
//        prevNode = currentNode;
//        if (pos < this->elements[currentNode].leftSubtreeSize) {
//            currentNode = this->elements[currentNode].left;
//        } else {
//            pos = pos - this->elements[currentNode].leftSubtreeSize - 1;    //+1
//            currentNode = this->elements[currentNode].right;
//        }
//    }
//
//    TComp removedElement = this->elements[currentNode].element;
//
//    if (this->elements[currentNode].left == -1 && this->elements[currentNode].right == -1) {
//        // Case 1: Removing a leaf node
//        if (prevNode == -1) {
//            this->root = -1;
//        } else if (this->elements[prevNode].left == currentNode) {
//            this->elements[prevNode].left = -1;
//        } else {
//            this->elements[prevNode].right = -1;
//        }
//        this->elements[currentNode].right = this->firstFree;
//        this->firstFree = currentNode;
//    } else if (this->elements[currentNode].left != -1 && this->elements[currentNode].right == -1) {
//        // Case 2: Removing a node with only left child
//        int leftChild = this->elements[currentNode].left;
//        if (prevNode == -1) {
//            this->root = leftChild;
//        } else if (this->elements[prevNode].left == currentNode) {
//            this->elements[prevNode].left = leftChild;
//        } else {
//            this->elements[prevNode].right = leftChild;
//        }
//        this->elements[currentNode].right = this->firstFree;
//        this->firstFree = currentNode;
//    } else if (this->elements[currentNode].left == -1 && this->elements[currentNode].right != -1) {
//        // Case 3: Removing a node with only right child
//        int rightChild = this->elements[currentNode].right;
//        if (prevNode == -1) {
//            this->root = rightChild;
//        } else if (this->elements[prevNode].left == currentNode) {
//            this->elements[prevNode].left = rightChild;
//        } else {
//            this->elements[prevNode].right = rightChild;
//        }
//        this->elements[currentNode].right = this->firstFree;
//        this->firstFree = currentNode;
//    } else {
//        // Case 4: Removing a node with both left and right children
//        int successorNode = this->elements[currentNode].right;
//        int successorParent = currentNode;
//        while (this->elements[successorNode].left != -1) {
//            successorParent = successorNode;
//            successorNode = this->elements[successorNode].left;
//        }
//        this->elements[currentNode].element = this->elements[successorNode].element;
//        if (successorParent == currentNode) {
//            this->elements[currentNode].right = this->elements[successorNode].right;
//        } else {
//            this->elements[successorParent].left = this->elements[successorNode].right;
//        }
//        this->elements[successorNode].right = this->firstFree;
//        this->firstFree = successorNode;
//    }
//
//    this->sizeBST--;
//    return removedElement;
//}
TComp SortedIndexedList::remove(int pos) {
    if (pos < 0 || pos >= sizeBST) {
        throw exception();
    }

    int currentNode = root;
    int prevNode = -1;
    int position = 0;
    while (currentNode != -1) {
        if (pos == (position + elements[currentNode].leftSubtreeSize)) {
            break;
        }
        if (pos < (position + elements[currentNode].leftSubtreeSize)) {
            prevNode = currentNode;
            currentNode = elements[currentNode].left;
        } else {
            prevNode = currentNode;
            position = position + elements[currentNode].leftSubtreeSize + 1;
            currentNode = elements[currentNode].right;
        }
    }

    int deleted = elements[currentNode].element;
    if (elements[currentNode].left == -1 && elements[currentNode].right == -1) {
        decrease(prevNode, pos);
        if (prevNode == -1) {
            root = -1;
        } else {
            if (pos < (position + elements[prevNode].leftSubtreeSize)) {
                elements[prevNode].left = -1;
            } else {
                elements[prevNode].right = -1;
            }
        }
        sizeBST--;
    } else {
        if (elements[currentNode].left == -1 || elements[currentNode].right == -1) {
            decrease(prevNode, pos);

            int descendant;
            if (elements[currentNode].left == -1) {
                descendant = elements[currentNode].right;
            } else {
                descendant = elements[currentNode].left;
            }

            if (prevNode == -1) {
                root = descendant;
            } else {
                if (pos < (position + elements[prevNode].leftSubtreeSize)) {
                    elements[prevNode].left = descendant;
                } else {
                    elements[prevNode].right = descendant;
                }
            }

            sizeBST--;
        } else {
            TComp n_successor = successor(elements[currentNode].element);
            int index = search(n_successor);
            remove(index);

            // Handle multiple occurrences of the value
            while (elements[currentNode].element == deleted) {
                if (elements[currentNode].right != -1) {
                    currentNode = elements[currentNode].right;
                    while (elements[currentNode].left != -1) {
                        currentNode = elements[currentNode].left;
                    }
                } else {
                    int parent = get_parent(deleted);
                    int parentNode = root;

                    while (parentNode != -1 && elements[parentNode].element != parent) {
                        if (r(parent, elements[parentNode].element)) {
                            parentNode = elements[parentNode].left;
                        } else {
                            parentNode = elements[parentNode].right;
                        }
                    }

                    while (parentNode != -1 && elements[parentNode].left != currentNode) {
                        currentNode = parentNode;
                        int n_parent = get_parent(elements[currentNode].element);
                        int n_parentNode = root;

                        while (n_parentNode != -1 && elements[n_parentNode].element != n_parent) {
                            if (r(n_parent, elements[n_parentNode].element)) {
                                n_parentNode = elements[n_parentNode].left;
                            } else {
                                n_parentNode = elements[n_parentNode].right;
                            }
                        }

                        parentNode = n_parentNode;
                    }

                    if (parentNode != -1) {
                        currentNode = parentNode;
                    } else {
                        break;  // No more occurrences of the value
                    }
                }
            }
        }
    }

    return deleted;
}

void SortedIndexedList::decrease(int prevNode, int pos) const {
    if (pos >= sizeBST || pos < 0) {
        throw exception();
    }

    int currentNode = root;
    int position = 0;
    while (currentNode != -1) {
        if (pos == (position + elements[currentNode].leftSubtreeSize)) {
            return;
        }
        if (pos < (position + elements[currentNode].leftSubtreeSize)) {
            elements[currentNode].leftSubtreeSize--;
            currentNode = elements[currentNode].left;
        } else {
            position += elements[currentNode].leftSubtreeSize + 1;
            currentNode = elements[currentNode].right;
        }
    }

    if (prevNode != -1) {
        int prevPosition = 0;
        while (prevNode != -1) {
            if (position < (prevPosition + elements[prevNode].leftSubtreeSize)) {
                elements[prevNode].leftSubtreeSize--;
                prevNode = elements[prevNode].left;
            } else {
                prevPosition += elements[prevNode].leftSubtreeSize + 1;
                prevNode = elements[prevNode].right;
            }
        }
    }
}

//void SortedIndexedList::decrease(int pos) const {
//    if (pos >= sizeBST || pos < 0) {
//        throw exception();
//    }
//
//    int currentNode = root;
//    int position = 0;
//    while (currentNode != -1) {
//        if (pos == (position + elements[currentNode].leftSubtreeSize)) {
//            return;
//        }
//        if (pos < (position + elements[currentNode].leftSubtreeSize)) {
//            elements[currentNode].leftSubtreeSize--;
//            currentNode = elements[currentNode].left;
//        } else {
//            position += elements[currentNode].leftSubtreeSize + 1;
//            currentNode = elements[currentNode].right;
//        }
//    }
//}

TComp SortedIndexedList::successor(TComp e) {
    int currentNode = root;
    while (currentNode != -1 && elements[currentNode].element != e) {
        if (r(e, elements[currentNode].element)) {
            currentNode = elements[currentNode].left;
        } else {
            currentNode = elements[currentNode].right;
        }
    }

    if (currentNode != -1 && elements[currentNode].right != -1) {
        currentNode = elements[currentNode].right;
        while (elements[currentNode].left != -1) {
            currentNode = elements[currentNode].left;
        }
        return elements[currentNode].element;
    } else {
        int parent = get_parent(e);
        int parentNode = root;

        while (parentNode != -1 && elements[parentNode].element != parent) {
            if (r(parent, elements[parentNode].element)) {
                parentNode = elements[parentNode].left;
            } else {
                parentNode = elements[parentNode].right;
            }
        }

        while (parentNode != -1 && elements[parentNode].left != currentNode) {
            currentNode = parentNode;
            int n_parent = get_parent(elements[currentNode].element);
            int n_parentNode = root;

            while (n_parentNode != -1 && elements[n_parentNode].element != n_parent) {
                if (r(n_parent, elements[n_parentNode].element)) {
                    n_parentNode = elements[n_parentNode].left;
                } else {
                    n_parentNode = elements[n_parentNode].right;
                }
            }

            parentNode = n_parentNode;
        }

        if (parentNode != -1) {
            return elements[parentNode].element;
        }
    }

    throw exception();
}
int SortedIndexedList::get_parent(TComp e) {
    int currentNode = root;
    int parent = -1;

    while (currentNode != -1 && elements[currentNode].element != e) {
        parent = currentNode;
        if (r(e, elements[currentNode].element)) {
            currentNode = elements[currentNode].left;
        } else {
            currentNode = elements[currentNode].right;
        }
    }

    if (currentNode != -1) {
        return elements[parent].element;
    } else {
        throw exception();
    }
}



///searches for an element and returns the first position where the element appears or -1 if the element is not in the list
int SortedIndexedList::search(TComp e) const {
    int current = this->root;
    while (current != -1) {
        if (e == this->elements[current].element) {
            return current;
        }
        if (this->r(e, this->elements[current].element)) {
            current = this->elements[current].left;
        } else {
            current = this->elements[current].right;
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
            if (this->r(e, elements[currentNode].element)) {
                elements[currentNode].leftSubtreeSize++;
                if (elements[currentNode].left == -1) {
                    elements[currentNode].left = newNode;
                    currentNode = -1;
                } else {
                    currentNode = elements[currentNode].left;
                }
            } else {
                if (elements[currentNode].right == -1) {
                    elements[currentNode].right = newNode;
                    currentNode = -1;
                } else {
                    currentNode = elements[currentNode].right;
                }
            }
        }
    }

//        if (r(e, elements[parent].element))
//            elements[parent].left = newNode;
//        else
//            elements[parent].right = newNode;
//        if (r(e, elements[parent].element)) {
//            elements[parent].left = newNode;
//            elements[newNode].leftSubtreeSize = elements[parent].leftSubtreeSize;
//        }
//        else {
//            elements[parent].right = newNode;
//            elements[newNode].leftSubtreeSize = elements[parent].leftSubtreeSize + 1;
//        }
//    }
//    // Update leftSubtreeSize for all nodes on the path from root to newNode
//    int current = root;
//    while (current != newNode) {
//        if (r(e, elements[current].element)) {
//            current = elements[current].left;
//        } else {
//            elements[current].leftSubtreeSize++; // Increment leftSubtreeSize for nodes on the right path
//            current = elements[current].right;
//        }
//    }


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
    while(!this ->isEmpty())
    {
        destroyTree(root);
        delete[] elements;
    }
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
