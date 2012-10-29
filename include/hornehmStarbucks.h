#include "Starbucks.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;


/**
*@author: Heather Horne
*
*I decided to take to learn more from the homework and do a binary tree instead of the array
*	that I had selected in Phase 1. 
*
*The binary tree is sorted on x, however, I realized the way I have it set up will make the tree higher than I would
* like it to be.
*
*/
/*
*Node class
*
*The nodes make up the binary tree with a left and right pointer, and data
* for the entry. There are also two constructors.
*/
class node{
public:
	node* left;
	node* right; 
	Entry* data;

	node(Entry* e);
	node();
};

/*
*This class is used to build the binary tree using the array of entries.
*/
class hornehmStarbucks : public Starbucks{
public:
	node* insert(Entry* e, node* r);
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	double distance(double x, double y, double x2, double y2);
	Entry* find(double x, double y, node* current, node* closest);
	node* root;//root node
	
};