#include "Starbucks.h"
using namespace std;


/**
*@author: Heather Horne
*
*I decided to take the harder route and try to build the binary tree.
*
*
*
*
*
*/
class hornehmStarbucks : public Starbucks{
public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
};