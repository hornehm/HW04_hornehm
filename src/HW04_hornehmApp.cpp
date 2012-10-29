#include "HW04_hornehmApp.h"

void HW04_hornehmApp::setup()
{
	numItems = 0;
	starbucks = readInFile();//reads in csv file into entry arrays
	quickSort(0, numItems-1);//quicksort on the array to find median
	hornehmStarbucks* stores = new hornehmStarbucks;
	stores->build(starbucks, numItems);//build binary search tree
	//printInOrder(stores->root);
	delEntries();//delete array of entries
	console() << (stores->getNearest(0.5645,0.59846104))->identifier << std::endl;//find the closest
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

/*
*Reads in Starbucks_2006.csv file into an array of entries. Returns pointer to the
*	array of entries.
*
*
*/
Entry* HW04_hornehmApp::readInFile(){
	string line;
	double xp, yp;
	ifstream myFile;

	myFile.open("Starbucks_2006.csv");

	//Finds number of items in the file.
	while(myFile.good()){
		getline(myFile, line, ',');
		myFile >> xp;
		myFile.get();
		myFile >> yp;
		myFile.get();
		numItems++;
	}

	//Go back to the beginning of the file
	myFile.clear();
	myFile.seekg(0);

	//Create array of entries
	Entry* test = new Entry[numItems];
	numItems = 0;

	//Do the same to count items, but this time input
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

/**
*This was implemented from www.myctutorials.com/articles/sorting/quicksort
*
*This quicksorts the array of entries. The main reason I wanted to do this was to
* split the entries on the median. 
*
*I noticed when I was building my array with the for loop that I was basically creating
* a list from the left and right pointers of the root... 
*
*I think it might be best to scramble the data after finding the median in order to get rid
*of that list
*
*
*@param start - left index
*@param end - right index
*/
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

/*
*Swaps the data of two indexes (index1 and index2)
*
*/
void HW04_hornehmApp::swap(int index1, int index2){
	Entry temp = starbucks[index1];
	starbucks[index1] = starbucks[index2];
	starbucks[index2] = temp;

}

/*
*Prints the order of the tree 
*/
void HW04_hornehmApp::printInOrder(node* r){{
	if(r==NULL){
	return;
	}
	printInOrder(r->left);
	console() << r->data->x << std::endl;
	printInOrder(r->right);
}

}

/*
*Deletes the array of entries
*/
void HW04_hornehmApp::delEntries(){
	delete [] starbucks;
}


CINDER_APP_BASIC( HW04_hornehmApp, RendererGl )
