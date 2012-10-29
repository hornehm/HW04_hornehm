#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "hornehmStarbucks.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_hornehmApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	Entry* readInFile();
	void quickSort(int start, int end);
	void swap(int index1, int index2);
	void delEntries();
	void printInOrder(node* r);

private:
	Entry* starbucks;
	int numItems;
	hornehmStarbucks stores;
};