#include "ListIterator.h"
#include "SortedIndexedList.h"
using namespace std;
#include <exception>

/// constructor
/// O(n)
SortedIndexedList::SortedIndexedList(Relation r) {
    this->rel = r;
    this->root = -1;
    this->sizeBST = 0;
    this->firstEmpty = 0;
    this->capacity = 8;
    this->tree = new Node[8];

    // use the left array to create a singly linked list of empty positions
    for (int i = 0; i < capacity - 1; i++)
        this->tree[i].leftPos = i + 1;
    this->tree[capacity - 1].leftPos = -1;
}

/// returns the size of the list
/// Theta(1)
int SortedIndexedList::size() const {
    return this->sizeBST;
}

///checks if the list is empty
/// Theta(1)
bool SortedIndexedList::isEmpty() const {
    return this->sizeBST == 0;
}

/// returns an element from a position
///throws exception if the position is not valid
/// O(n) - n the length of tree
TComp SortedIndexedList::getElement(int i) const{
    if (i < 0 || i >= this->sizeBST)
        throw exception();
    int current = this->root;

    //performing a search through the tree array using the leftSubtreeSize values to navigate to the desired position
    while (this->tree[current].leftSubtreeSize != i)
    {
        //the position we are searching is smaller than the position of the root, so we go in the left subtree
        if (i < this->tree[current].leftSubtreeSize)
            current = this->tree[current].leftPos;
        else
        {
            //the position we are searching is greater than the position of the root, so we go in the right subtree
            i -= (this->tree[current].leftSubtreeSize + 1);
            current = this->tree[current].rightPos;
        }
    }
    return this->tree[current].element;
}

///removes an element from a given position
///returns the removed element
///throws an exception if the position is not valid
/// O(n)
TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= this->sizeBST)
        throw exception();
    int current = this->root;
    int parent = -1; //keep track of the parent of the current node during traversal

    //find the node to delete
    while (this->tree[current].leftSubtreeSize != i)
    {
        parent = current;
        //if the  position is less than leftSubtreeSize, the position is in the left subtree
        if (i < this->tree[current].leftSubtreeSize)
        {
            //decrement the number of nodes from the left subtree
            this->tree[current].leftSubtreeSize--;
            current = this->tree[current].leftPos;
        }
        else
        //if the  position is greater than leftSubtreeSize, the position is in the right subtree

        {
            //adjust the position relative to the right subtree
            i -= (this->tree[current].leftSubtreeSize + 1);
            current = this->tree[current].rightPos;
        }
    }
    //the element which will be removed
    TComp removedElement = this->tree[current].element;

    // Fall 1: the node has no descendant
    if (this->tree[current].leftPos == -1 && this->tree[current].rightPos == -1)
    {
        this->removeNode(current, parent, -1);
    }

    // Fall 2: the node has only one descendant on left
    else if (this->tree[current].rightPos == -1)
    {
        this->removeNode(current, parent, this->tree[current].leftPos);
    }

    // Fall 3: the node has only one descendant on right
    else if (this->tree[current].leftPos == -1)
    {
        this->removeNode(current, parent, this->tree[current].rightPos);
    }
    else
    // Fall 4: the node has 2 descendants
    {
        // find the minimum of the right subtree, move it to the node to be deleted, and delete the minimum

        // find the minimum of the right subtree by traversing the left children of the right subtree until we reach the leftmost node
        int minPos = this->tree[current].rightPos, minParent = current;
        this->tree[minPos].leftSubtreeSize--;
        while (this->tree[minPos].leftPos != -1)
        {
            minParent = minPos;
            minPos = this->tree[minPos].leftPos;
            this->tree[minPos].leftSubtreeSize--;
        }
        this->tree[current].element = this->tree[minPos].element; // we copy the element of the minimum node to the node to be removed
        this->removeNode(minPos, minParent, this->tree[minPos].rightPos); // delete the minimum
    }
    this->sizeBST--;
    return removedElement;
}

/// Theta(1)
void SortedIndexedList::removeNode(int nodePos, int parentPos, int nodeChildPos)
{
    //nodePos = index of the node to be removed
    //parentPos = position of the parent node of the node to be removed
    //nodeChildPos = position of the child node that will replace the node to be removed
    if (nodePos == this->root)
        this->root = nodeChildPos;  //the child node becomes the new root

        //if the node to be removed is not the root, we check if it is the left child of its parent
    else if (nodePos == this->tree[parentPos].leftPos)
        //if it is, the left child pointer of the parent is updated to nodeChildPos
        this->tree[parentPos].leftPos = nodeChildPos;
    else
        //if it isn't, the right child pointer of the parent is updated to nodeChildPos
        this->tree[parentPos].rightPos = nodeChildPos;

    //the removed node is now the first node in the linked list of empty positions
    this->tree[nodePos].leftPos = this->firstEmpty;
    this->firstEmpty = nodePos;
}


/// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
/// O(n) - n the length of tree
int SortedIndexedList::search(TComp e) const {
    if (this->root == -1) return -1;
    int foundPosition = -1, listPosition = 0;
    int current = this->root;
    while (current != -1)
    {
        if (this->tree[current].element == e)
            foundPosition = listPosition + this->tree[current].leftSubtreeSize;
        if (this->rel(e, tree[current].element))
            current = this->tree[current].leftPos;
        else
        {
            listPosition += this->tree[current].leftSubtreeSize + 1;
            current = this->tree[current].rightPos;
        }
    }
    return foundPosition;
}

/// adds an element in the sortedList (to the corresponding position)
/// O(n)
void SortedIndexedList::add(TComp e) {
    if (this->firstEmpty == -1)
        this->resizeTreeArray();

    int current = this->root, parent = -1;

    // find where to insert the node
    while (current != -1)
    {
        parent = current;
        if (this->rel(e, tree[current].element))
        {
            this->tree[current].leftSubtreeSize++;
            current = this->tree[current].leftPos;
        }
        else
            current = this->tree[current].rightPos;
    }

    int newPosition = this->firstEmpty;

    // there was no node in the tree, so add the root
    if (current == this->root)
        this->root = newPosition;
    else if (rel(e, tree[parent].element))
        this->tree[parent].leftPos = newPosition;
    else
        this->tree[parent].rightPos = newPosition;

    // get new firstEmpty position
    this->firstEmpty = this->tree[firstEmpty].leftPos;

    this->tree[newPosition].element = e;
    this->tree[newPosition].leftSubtreeSize = 0;

    // new node does not have children
    this->tree[newPosition].leftPos = -1;
    this->tree[newPosition].rightPos = -1;

    this->sizeBST++;
}

/// Theta(1)
ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}


///destructor
/// Theta(1)
SortedIndexedList::~SortedIndexedList() {
    delete[] this->tree;
}


void SortedIndexedList::resizeTreeArray()
{

    Node* newTree = new Node[capacity * 2];
    for (int i = 0; i < capacity; i++)
        newTree[i] = this->tree[i];

    for (int i = capacity; i < capacity * 2 - 1; i++)
        newTree[i].leftPos = i + 1;
    newTree[capacity * 2 - 1].leftPos = -1;
    delete this->tree;
    this->tree = newTree;
    this->firstEmpty = capacity;
    this->capacity *= 2;
}

void SortedIndexedList::removeBetween(int start, int end) {
    if(start < 0 || end < 0 || start > this->sizeBST || end > this->sizeBST)
        throw exception();

    for(int i = start; i < end; i++)
        this->remove(i);
}
/// O(n)