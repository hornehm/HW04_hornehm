#include "HW04_hornehmApp.h"
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

CensusEntry* HW04_hornehmApp::readInCensus(string filename){
	int pop;
	double x, y;
	string line;
	ifstream myFile;

	myFile.open(filename);

	//Finds number of items in the file.
	while(myFile.good()){
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		myFile >> pop;
		myFile.get();
		myFile >> x;
		myFile.get();
		myFile >> y;
		myFile.get();
		numItems++;
	}

	//Go back to the beginning of the file
	myFile.clear();
	myFile.seekg(0);

	//Create array of entries
	CensusEntry* test = new CensusEntry[numItems];
	numItems = 0;

	//Do the same to count items, but this time input
	while(myFile.good()){
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		getline(myFile, line, ',');
		myFile >> pop;
		myFile.get();
		myFile >> x;
		myFile.get();
		myFile >> y;
		myFile.get();
		test[numItems].population = pop;
		test[numItems].x = x;
		test[numItems].y = y;
		numItems++;
	}	
	myFile.close();
	if(filename == "Census_2010.csv"){
		numItems2010 = numItems;
	}
	else{
		numItems2000 = numItems;
	}
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

void HW04_hornehmApp::drawRectangle(uint8_t* pixels, int x, int y, int width, int height, Color8u color){
	y = reflectY(y);
	for(int i = y; i<= y+height; i++){
		for(int j = x; j<=x+width; j++){
			pixels[3*(j+i*textureSize)] = color.r;
			pixels[3*(j+i*textureSize)+1] = color.g;
			pixels[3*(j+i*textureSize)+2] = color.b;
		}
	}
}

void HW04_hornehmApp::drawMap(uint8_t* pixels, node* r){
	if (r == NULL)
		return;
	drawMap(pixels, r->left);
	drawRectangle(pixels, (int)(r->data->x*appWidth), (int)(r->data->y*appHeight), 3, 3, Color8u(255,255,0));
	drawMap(pixels, r->right);
	//nearestMap(pixels);
}

void HW04_hornehmApp::drawPopulationMap(uint8_t* pixels, CensusEntry* arr, int items, Color8u color){
	for(int i = 0; i<items; i++){
		if(arr[i].population < 1000){
			color = Color8u(34,139,34);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
		else if(arr[i].population < 5000){
			color = Color8u(50,205,50);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
		else{
			color = Color8u(173,255,47);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
	}
}

void HW04_hornehmApp::nearestMap(uint8_t* pixels){
	
}

int HW04_hornehmApp::reflectY(int y){
	if(y<appHeight/2){
		y = y+2*(abs(y-appHeight/2));
	}
	else if(y >appHeight/2){
		y = y-2*(abs(y-appHeight/2));
	}
	return y;
}

void HW04_hornehmApp::keyDown(KeyEvent event){
	if(event.getChar()=='1'){
		nearestMap(dataArray);
	}
	if(event.KEY_ESCAPE){
		showMessage = false;
	}
}

void HW04_hornehmApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void HW04_hornehmApp::setup()
{
	Surface surf(loadImage("../resources/usa.png"));
	map = gl::Texture(surf);
	showMessage = false;
	showMap = false;

	f = Font( "Arial", 24 );
	textFont = gl::TextureFont::create(f);

	numItems2000 = numItems2010 = numItems = 0;
	//census2000 = readInCensus("Census_2000.csv");
	//census2010 = readInCensus("Census_2010.csv");
	
	starbucks = readInFile();//reads in csv file into entry arrays
	quickSort(0, numItems-1);//quicksort on the array to find median
	stores = new hornehmStarbucks;
	stores->build(starbucks, numItems);//build binary search tree
	//printInOrder(stores->root);
	delEntries();//delete array of entries
	
	mySurface = new Surface(textureSize, textureSize, false);
	dataArray = (*mySurface).getData();
	//drawPopulationMap(dataArray, census2000, numItems2000, Color8u(0, 255, 0));
	//drawPopulationMap(dataArray, census2010, numItems2010, Color8u(255, 0, 0));
	drawMap(dataArray, stores->root);
}

void HW04_hornehmApp::mouseDown( MouseEvent event )
{
	if(event.isLeftDown()){
		double x = (double)event.getX();
		int y = event.getY();
		y = reflectY(y);
		Entry* tmp = stores->getNearest(x/((double)appWidth),((double)y)/((double)appHeight));
		drawRectangle(dataArray, (int)(tmp->x*appWidth), (int)(tmp->y*appHeight), 5, 5, Color8u(0, 0, 255));
		message = tmp->identifier;
		showMessage = true;
		
	}
	if(event.isRightDown()){
		showMap =!showMap;
	}
	
}


void HW04_hornehmApp::update()
{
	dataArray = (*mySurface).getData();
	
}

void HW04_hornehmApp::draw()
{
	if(showMap){
		gl::draw(map, getWindowBounds());
	}
	else{ //if(showMessage){
		gl::clear(Color(0, 0, 0));
		gl::draw(*mySurface);
		gl::color(Color8u(255, 255, 255));
		std::string str("Store Location: " + message);
		gl::color(Color8u(0, 0, 0));
		gl::enableAlphaBlending();
		gl::color(Color(255, 50, 50));
		Rectf boundsRect(40, textFont->getAscent() + 350, getWindowWidth() - 40, 
				getWindowHeight() - 40);
		textFont ->drawStringWrapped(str, boundsRect);
		gl::color(Color8u(255, 255, 255));
	}
	//else{
	//gl::clear(Color(0, 0, 0));
	//gl::draw(*mySurface);
	//}
}


CINDER_APP_BASIC( HW04_hornehmApp, RendererGl )
