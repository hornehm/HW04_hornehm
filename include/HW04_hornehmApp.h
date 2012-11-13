#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "hornehmStarbucks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;

/*
*CensusEntry:
* Location x, and y, plus the population for those coordinates
*/
class CensusEntry{
public:
	int population;
	double x;
	double y;
};
/*
*@author: Heather Horne
*
*Homework 4 app for phase 3
*
*For this phase, I implemented A, B, possibly F, H, and Youtube video. I had a hard time
*with making the regions. I wanted to color each pixel according to the getNearest method
*for each pixel, but for one, it took 7 minutes to load, and it also did not color each
*pixel.
*
*Brown-Represents starbucks locations
*Cyan-Represents the nearest starbucks when you left click on teh map
*Light Green-High area of population
*Medium Green-Medium area of population
*Dark Green- low area of population
*
*My app also displays the location of the nearest starbucks when clicked.
*
*Note: You can right click to get the image map of the US to pop up. Was not able to do
*much with it, but show where everything is.
*
*YOUTUBE LINK: http://youtu.be/53ahmW_Ich4
*/
class HW04_hornehmApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	
	//Phase 2 methods
	Entry* readInFile();
	void quickSort(int start, int end);
	void swap(int index1, int index2);
	void delEntries();

	//Phase 3 methods
	CensusEntry* readInCensus(string filename);
	void drawMap(uint8_t* pixels, node* r);
	void drawPopulationMap(uint8_t* pixels, CensusEntry* arr, int items);
	void drawRectangle(uint8_t* pixels, int x, int y, int width, int height, Color8u color);
	void nearestMap(uint8_t* pixels);
	int reflectY(int y);
	

private:
	//Surface and dataArray for map
	Surface* mySurface;
	uint8_t* dataArray;

	//Array of entries for each file
	CensusEntry* census2000;
	CensusEntry* census2010;

	//Variables for the added map
	gl::Texture map;
	bool showMap, showMessage;
	string message;

	//Widths/Height/Texturesize
	static const int appWidth = 600;
	static const int appHeight = 400;
	static const int textureSize = 1024;


	Entry* starbucks;//entry array
	int numItems, numItems2010, numItems2000;//number of items in the array
	hornehmStarbucks* stores;//used to build tree

	//Font variables for message
	Font f;
	gl::TextureFontRef textFont;
	
};

