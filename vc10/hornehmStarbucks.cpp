#include "hornehmStarbucks.h"

node::node(Entry* e){
	data = e;
	left = NULL;
	right = NULL;
}

node::node(){
	data = NULL;
	left = NULL;
	right = NULL;
}

node* hornehmStarbucks::insert(Entry* e, node* r){

	if(r == NULL){
		return new node(e);
	}
	if(abs(e->x - r->data->x)<= 0.00001 && abs(e->y - r->data->y)<= 0.00001){
		return r;
	}
	if(e->x < r->data->x){
		r->left = insert(e, r->left);
	}
	else{
		r->right = insert(e, r->right);
	}
	return r;

}


void hornehmStarbucks::build(Entry* e, int n){
	Entry* copiedArray = new Entry[n];
	for(int i = 0; i < n; i++){
		copiedArray[i].x = e[i].x;
		copiedArray[i].y = e[i].y;
		copiedArray[i].identifier = e[i].identifier;
	}
	e = copiedArray;
	root = new node(&copiedArray[n/2]);
	for(int i = 0; i < n; i++){
		insert(&copiedArray[i], root);
	}

}

Entry* hornehmStarbucks::getNearest(double x, double y){
	return find(x, y, root, root);
}

double hornehmStarbucks::distance(double x2, double y2, double x, double y){
	return sqrt(((x2-x)*(x2-x))+((y2-y)*(y2-y)));
}

Entry* hornehmStarbucks::find(double x, double y, node* current, node* closest){
	if(closest == NULL){
		closest->data = current->data;
	}
	if(current==NULL){
		return closest->data;
	}

	double d = distance(x, y, current->data->x, current->data->y);
	double distanceClosest = distance(x,y, closest->data->x, closest->data->y);
	
	if(d <= distanceClosest){
		closest->data = current->data;
	}
	find(x, y, current->left, closest);
	find(x, y, current->right, closest);

	return closest->data;

}
