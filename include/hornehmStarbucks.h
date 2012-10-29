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
};

class hornehmStarbucks : public Starbucks{
public:
	node* insert(Entry* e, node* r);
	virtual void build(Entry* e, int n);
	virtual Entry* getNearest(double x, double y);
private:
	node* root;
};