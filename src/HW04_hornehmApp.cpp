#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_hornehmApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

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
