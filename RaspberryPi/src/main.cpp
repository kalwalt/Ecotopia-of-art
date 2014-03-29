//copyright by @kalwalt https://www.kalwaltart.it for @Ecotopiaofart https://twitter.com/Ecotopiaofart please, leave this comment in place!

#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
