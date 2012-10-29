#include "hornehmStarbucks.h"

node* hornehmStarbucks::insert(Entry* e, node* r){

	if(r == NULL){
		return new node();
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

	root = new node();
	root->data->x = e[n/2].x;
	root->data->y = e[n/2].y;
	root->data->identifier = e[n/2].identifier;
	
	for(int i = 0; i < n; i++){
		insert(&e[i], root);
	}

}

Entry* hornehmStarbucks::getNearest(double x, double y){
	Entry* e = new Entry;
	return e;
}