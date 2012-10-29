#include "HW04_hornehmApp.h"

void HW04_hornehmApp::setup()
{
	numItems = 0;
	starbucks = readInFile();
	quickSort(0, numItems-1);
	hornehmStarbucks* stores = new hornehmStarbucks;
	stores->build(starbucks, numItems);
	//printInOrder(stores->root);
	delEntries();
	console() << (stores->getNearest(0.778605645,0.59846104))->identifier << std::endl;
}

void HW04_hornehmApp::mouseDown( MouseEvent event )
{
}

void HW04_hornehmApp::update()
{
	
}

void HW04_hornehmApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

Entry* HW04_hornehmApp::readInFile(){
	string line;
	double xp, yp;
	ifstream myFile;

	myFile.open("Starbucks_2006.csv");

	while(myFile.good()){
		getline(myFile, line, ',');
		myFile >> xp;
		myFile.get();
		myFile >> yp;
		myFile.get();
		numItems++;
	}

	myFile.clear();
	myFile.seekg(0);

	Entry* test = new Entry[numItems];
	numItems = 0;

	while(myFile.good()){
		getline(myFile, line, ',');
		myFile >> xp;
		myFile.get();
		myFile >> yp;
		myFile.get();
		test[numItems].identifier = line;
		test[numItems].x = xp;
		test[numItems].y = yp;
		numItems++;
	}	
	myFile.close();
	return test;
}

//This was implemented from www.myctutorials.com/articles/sorting/quicksort
void HW04_hornehmApp::quickSort(int start, int end){
	int i = start;
	int k = end;
	if(end-start >= 1){
		double pivot = starbucks[start].x;
		while(k>i){
			while(starbucks[i].x <= pivot && i <= end && k>i){
				i++;
			}
			while(starbucks[k].x > pivot && k>= start && k>= i){
				k--;
			}
			if(k>i){
				swap(i, k);
			}
		}
		swap(start, k);

		quickSort(start, k-1);
		quickSort(k+1, end);
	}	
	else{
		return;
	}
}

void HW04_hornehmApp::swap(int index1, int index2){
	Entry temp = starbucks[index1];
	starbucks[index1] = starbucks[index2];
	starbucks[index2] = temp;

}

void HW04_hornehmApp::printInOrder(node* r){{
	if(r==NULL){
	return;
	}
	printInOrder(r->left);
	console() << r->data->x << std::endl;
	printInOrder(r->right);
}

}


void HW04_hornehmApp::delEntries(){
	delete [] starbucks;
}


CINDER_APP_BASIC( HW04_hornehmApp, RendererGl )
