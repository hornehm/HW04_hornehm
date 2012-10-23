#include "HW04_hornehmApp.h"


Entry* HW04_hornehmApp::readInFile(){
	string line;
	double x, y;
	ifstream myFile("starbucks.csv");
	int numItems;

	while(myFile.is_open()){
		getline(myFile, line, ',');
		numItems++;
	}
	myFile.close();
	Entry* arr = new Entry[numItems];
	for(int i = 0; i < numItems; i++){
		getline(myFile, line, ',');
		arr[i].identifier = line;
		getline(myFile, line, ',');
		x = atof(line.c_str());
		arr[i].x = x;
		getline(myFile, line, ',');
		arr[i].y = y;
	}
	return arr;
}

void HW04_hornehmApp::setup()
{
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

CINDER_APP_BASIC( HW04_hornehmApp, RendererGl )
