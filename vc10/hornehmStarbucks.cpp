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

	root = new node(&e[n/2]);
	
	for(int i = 0; i < n; i++){
		insert(&e[i], root);
	}

}

Entry* hornehmStarbucks::getNearest(double x, double y){
	Entry* e = new Entry;
	return e;
}