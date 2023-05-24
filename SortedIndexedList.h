#pragma once
//DO NOT INCLUDE LISTITERATOR
//18. ADT SortedList – repräsentiert mithilfe eines BST mit einer verketteten Repräsentierung
//auf Arrays, wobei für jeden Knoten man auch die Anzahl der Elemente, die sich links des
//Knoten befinden speichert (siehe Vorlesung)
//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111
struct Node {
    TComp element;
    int left;
    int right;
    int leftSubtreeSize;
};
class SortedIndexedList {
private:
	friend class ListIterator;
private:

    int root;
    Node* elements;
    int capacity;
    int sizeBST;
    Relation r;

    int firstFree;
public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element to a given position
	//throws an exception if the position is not valid
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

    void destroyTree(int node);


    void freeNode(int node);

    int get_parent(TComp e);

    TComp successor(TComp e);

    void decrease(int pos) const;

    void decrease(int prevNode, int pos) const;
};