#include "HW04_hornehmApp.h"
/*
*This method was implemented from class as well as HW04_Sonodabe
*
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


/*
*
*This method was implemented from class as well as HW04_Sonodabe
*
*Imports x, y, and population from the census files.
*
*@param filename - either "Census_2010.csv" or "Census_2000.csv".. or whatever else
*/
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
*Swaps the data of two indices (index1 and index2)
*
*/
void HW04_hornehmApp::swap(int index1, int index2){
	Entry temp = starbucks[index1];
	starbucks[index1] = starbucks[index2];
	starbucks[index2] = temp;

}


/*
*Deletes the array of entries
*/
void HW04_hornehmApp::delEntries(){
	delete [] starbucks;
}

/*
*Draw rectangle for each starbucks location. I thought this was nice to see the points a little better.
*
*I used this same method from my first homework.
*
*@param pixels - dataArray
*@param x - top-left x coordinate
*@param y - top-left y coordinate
*@param width - width of rectangle
*@param height - height of rectangle
*@param color - color of rectangle
*/
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

/*
*Draws the starbucks locations (They are brown. You can change the size of them
* by changing the width and height of the triangle)
*
*I used the same idea that was presented in Brinkman's class for PrintInOrder. 
* Instead, I decided to draw a map.
*
*@param pixels - dataArray
*@param r - root node
*/
void HW04_hornehmApp::drawMap(uint8_t* pixels, node* r){
	if (r == NULL)
		return;
	drawMap(pixels, r->left);
	drawRectangle(pixels, (int)(r->data->x*appWidth), (int)(r->data->y*appHeight), 2, 2, Color8u(218,165,32));
	drawMap(pixels, r->right);
	//nearestMap(pixels);
}

/*
*Colors each pixel according to how many people at that point
*@param pixels - dataArray
*@param arr - Array of CensusEntries
*@param items - number of items in arr
*/
void HW04_hornehmApp::drawPopulationMap(uint8_t* pixels, CensusEntry* arr, int items){
	Color8u color;
	for(int i = 0; i<items; i++){
		if(arr[i].population < 1500){
			color = Color8u(34,139,34);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
		else if(arr[i].population < 3000){
			color = Color8u(50,205,50);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
		else{
			color = Color8u(173,255,47);
			drawRectangle(pixels, (int)(arr[i].x*appWidth), (int)(arr[i].y*appHeight), 1, 1, color);
		}
	}
}

/*
*This method is supposed to color each pixel in the map according to the color of the starbucks
* location. It doesn't work, however, in order to test it out, the values for color need to be random 
* when the map is originally drawn.
*
*@param pixels - dataArray
*/
void HW04_hornehmApp::nearestMap(uint8_t* pixels){
	int x2, y2;
	for(int y = 0; y < appHeight; y++){
		for(int x = 0; x < appWidth; x++){
			Entry* tmp = stores->getNearest((double)x/((double)appWidth),((double)y)/((double)appHeight));
			x2 = (int)(tmp->x*appWidth);
			y2 = (int)(tmp->y*appHeight);
			pixels[3*(x+y*textureSize)] = pixels[3*(x2+y2*textureSize)];
			pixels[3*(x+y*textureSize)+1] = pixels[3*(x2+y2*textureSize)+1];
			pixels[3*(x+y*textureSize)+2] = pixels[3*(x2+y2*textureSize)+2];
		}
	}
}
/*
*Reflects the Y value so that it will draw map correctly
*
*@param y - y value to be reflected
*/
int HW04_hornehmApp::reflectY(int y){
	if(y<appHeight/2){
		y = y+2*(abs(y-appHeight/2));
	}
	else if(y >appHeight/2){
		y = y-2*(abs(y-appHeight/2));
	}
	return y;
}

void HW04_hornehmApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void HW04_hornehmApp::setup()
{
	//loads image
	Surface surf(loadImage("../resources/usa.png"));
	map = gl::Texture(surf);
	//sets messages and map to false
	showMessage = false;
	showMap = false;
	//initialize font
	f = Font( "Arial", 24 );
	textFont = gl::TextureFont::create(f);

	numItems2000 = numItems2010 = numItems = 0;
	//census2000 = readInCensus("Census_2000.csv");
	census2010 = readInCensus("Census_2010.csv");
	
	starbucks = readInFile();//reads in csv file into entry arrays
	quickSort(0, numItems-1);//quicksort on the array to find median
	stores = new hornehmStarbucks;
	stores->build(starbucks, numItems);//build binary search tree
	delEntries();//delete array of entries
	
	//Draw map
	mySurface = new Surface(textureSize, textureSize, false);
	dataArray = (*mySurface).getData();
	//drawPopulationMap(dataArray, census2000, numItems2000);
	drawPopulationMap(dataArray, census2010, numItems2010);
	drawMap(dataArray, stores->root);
	
}

void HW04_hornehmApp::mouseDown( MouseEvent event )
{
	//If left is down, highlight nearest starbucks at that point
	if(event.isLeftDown()){
		drawMap(dataArray, stores->root);
		double x = (double)event.getX();
		int y = event.getY();
		y = reflectY(y);
		Entry* tmp = stores->getNearest(x/((double)appWidth),((double)y)/((double)appHeight));
		drawRectangle(dataArray, (int)(tmp->x*appWidth), (int)(tmp->y*appHeight), 3, 3, Color8u(0,255,255));
		message = tmp->identifier;
		showMessage = true;
		
	}
	//if right is down, show the image in resources
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
	else{
		//Displays the location of the starbucks
		// when getNearest is called.
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
	
}


CINDER_APP_BASIC( HW04_hornehmApp, RendererGl )
