#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
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

class CensusEntry{
public:
	int population;
	double x;
	double y;
};
/*
*@author: Heather Horne
*
*Homework 4 app for phase 2
*
*For this phase, I decided to try the binary tree, however, I did not implement
* correctly. Since I quicksorted the array and then imported entries into the tree 
* in that order, I am pretty sure the left and right pointers from the node look 
* like lists.
*
*Everything for this phase is in the setup() method
*
*/
class HW04_hornehmApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	Entry* readInFile();
	CensusEntry* readInCensus(string filename);
	void quickSort(int start, int end);
	void swap(int index1, int index2);
	void delEntries();
	void printInOrder(node* r);
	void drawMap(uint8_t* pixels, node* r);
	void drawPopulationMap(uint8_t* pixels, CensusEntry* arr, int items);
	void drawRectangle(uint8_t* pixels, int x, int y, int width, int height, Color8u color);
	void nearestMap(uint8_t* pixels);
	void keyDown( KeyEvent event);
	int reflectY(int y);
	

private:

	Surface* mySurface;
	uint8_t* dataArray;

	CensusEntry* census2000;
	CensusEntry* census2010;

	gl::Texture map;
	bool show;

	static const int appWidth = 600;
	static const int appHeight = 400;
	static const int textureSize = 1024;

	Entry* starbucks;//entry array
	int numItems, numItems2010, numItems2000;//number of items in the array
	hornehmStarbucks* stores;//used to build tree

	
};

