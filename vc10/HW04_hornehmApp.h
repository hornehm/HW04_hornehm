#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "hornehmStarbucks.h"
#include <iostream>
#include <fstream>
#include <string>

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
};