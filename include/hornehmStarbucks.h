#include "Starbucks.h"
using namespace std;


/**
*@author: Heather Horne
*
*I decided to take to learn more from the homework and do a binary tree instead of the array
*	that I had selected in Phase 1.
*
*
*
*
*/

class node{
public:
	node* left;
	node* right; 
	Entry* data;

	node();
};

class hornehmStarbucks : public Starbucks{
public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
};