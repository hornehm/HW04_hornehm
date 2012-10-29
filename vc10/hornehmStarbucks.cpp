#include "hornehmStarbucks.h"

/**
*Node Constructor with a data input for an entry
**/
node::node(Entry* e){
	data = e;
	left = NULL;
	right = NULL;
}

/**
*Default node constructor sets everything to NULL
**/
node::node(){
	data = NULL;
	left = NULL;
	right = NULL;
}

/**
*Inserts the entry into the tree
*@param e - entry data in the array
*@param r - root node (or parent node)
*/
node* hornehmStarbucks::insert(Entry* e, node* r){

	if(r == NULL){
		return new node(e);//returns new node with e data if it reaches the end of the tree
	}
	if(abs(e->x - r->data->x)<= 0.00001 && abs(e->y - r->data->y)<= 0.00001){ //checks for duplicates
		return r;
	}
	if(e->x < r->data->x){//determines which side of tree to go based on x values
		r->left = insert(e, r->left);
	}
	else{
		r->right = insert(e, r->right);
	}
	return r;

}


/*
*Adds all entries in the array to my binary tree
*
* The "c" parameter is a pointer to an array of all the entries to be added, and n is the length of
* the array.
*
*As suggested, I first copy the array and point to it to avoid dangling pointers.
*
*I realize this isn't the best way of building the binary tree. I should have scrambled the entries 
* after quicksorting to find the median. Since I use a for-loop to add the entries, I am basically 
* creating a list from the right and left pointers. However, since I end up searching the whole tree 
* in getNearest, it really does not affect it.
*/
void hornehmStarbucks::build(Entry* c, int n){
	Entry* copiedArray = new Entry[n]; 
	for(int i = 0; i < n; i++){
		copiedArray[i].x = c[i].x;
		copiedArray[i].y = c[i].y;
		copiedArray[i].identifier = c[i].identifier;
	}
	c = copiedArray; //point to copied array
	root = new node(&c[n/2]);//make the root the median

	//Use for-loop to add items. As I stated above, this was not the best way to build 
	// my binary tree, but I have run out of time.
	for(int i = 0; i < n; i++){
		insert(&c[i], root);
	}

}

/*
* Return a pointer to the entry that is closest to the given coordinates. 
*
*/
Entry* hornehmStarbucks::getNearest(double x, double y){
	return find(x, y, root, root);
}

/*
*Finds the distance between the closest x and y and "current" x and y
*
*@param x2 - current x value
*@param y2 - current y value
*@param x - closest x value
*@param y - closest y value
*/
double hornehmStarbucks::distance(double x2, double y2, double x, double y){
	return sqrt(((x2-x)*(x2-x))+((y2-y)*(y2-y)));
}

/*
*Finds the closest x,y values to the current x,y values and returns the data of the closest
*
*I did not have time to come up with a better solution so that I would not have to check both branches.
*	I ended up checking both, so that I could get accuracy points (although I am sure it won't be the 
*	fastest.
*
*@param x - Position of x
*@param y - Position of y
*@param current - current node to check x, y values
*@param closest - keeps track of closest node/entry data
*/

Entry* hornehmStarbucks::find(double x, double y, node* current, node* closest){
	if(closest == NULL){//should only ring true the first time through
		closest->data = current->data;
	}
	if(current==NULL){
		return closest->data;
	}

	double d = distance(x, y, current->data->x, current->data->y); //distance from current x,y values
	double distanceClosest = distance(x,y, closest->data->x, closest->data->y);//distance of closest values
	
	if(d <= distanceClosest){
		closest->data = current->data;
	}

	find(x, y, current->left, closest);//check left branch
	find(x, y, current->right, closest);//check right branch

	return closest->data;//return the closest entry values

}
