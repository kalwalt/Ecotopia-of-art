#pragma once

#include "ofMain.h"
#include "ofx3DModelLoader.h"
#include "ofxOpenCv.h"
#include "ofxARToolkitPlus.h"
#include "ofxBox2d.h"
//#include "ofxOsc.h"




// A simple little Data class. This is were
// you can store anything you want.
class Data {
public:
	ofColor color;
	string  name;
	int		id;
};

// A Custom Particle extedning the box2d Rect

class CustomParticle : public ofxBox2dRect {

public:

    ofImage img;

void setupTheCustomData(string hashtags) {
    img.loadImage("3831.png");

    static int colors[] = {0x4bc3a0, 0x4025e2, 0x2bb0e7, 0x4a4dd3};

    vector <string> hashTags;
    hashTags = ofSplitString(hashtags, " ");

    // we are using a Data pointer because
    // box2d needs to have a pointer not
    // a referance
    setData(new Data());
    Data * theData = (Data*)getData();
    theData->id = ofRandom(0, 100);
    theData->name += hashTags[(int)ofRandom(0, hashTags.size())];
    theData->color.setHex(colors[(int)ofRandom(0, 4)]);
   // printf("setting the custom data!\n");

	}

void draw() {
		Data* theData = (Data*)getData();
		if(theData) {

			// Evan though we know the data object lets just
			// see how we can get the data out from box2d
			// you would use this when using a contact listener
			// or tapping into box2d's solver.

			float width = getWidth();
			ofPushMatrix();
			ofTranslate(getPosition());
			ofRotateZ(getRotation());
			ofEnableAlphaBlending();
			ofSetColor(theData->color,120);
			ofFill();
            ofEnableDepthTest();
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);

            img.draw(0,0, width*2, width*2);

			ofRect(0,0,width*2,width*2);

			ofDisableAlphaBlending();
            ofDisableBlendMode();

            float textSize = width/22;
            ofPushMatrix();
            ofScale(textSize, textSize);
			ofSetColor(255);
			ofDrawBitmapString(theData->name, -textSize/2, textSize);
            ofPopMatrix();

			ofPopMatrix();
            ofDisableDepthTest();
		}
	}


};


class ARtk {

	public:

		/* Size of the image */
		int m_width, m_height;

		/* Use a camera  */

		ofVideoGrabber vidGrabber;

		/* ARToolKitPlus class */
		ofxARToolkitPlus artk;
		int m_threshold;
		bool thresoldV;

		/* OpenCV images */
		ofxCvColorImage colorImage;
		ofxCvGrayscaleImage grayImage;
		ofxCvGrayscaleImage	grayThres;

		ofx3DModelLoader scultura_3831;
		ofx3DModelLoader scultura_3677;
		ofx3DModelLoader scultura_3767;
		ofx3DModelLoader scultura_3895;
		ofx3DModelLoader scultura_129;

        	ofxBox2d                            box2d;
        	vector <ofPtr<CustomParticle> >		particles;

       

        	ofMaterial material;
        	ofLight pointLight;


        	int num;
        	float soundSpeed;
        	float lfo;
        	float amp;
        	float radius;
        	ofVec2f center;
       
		int i;
//--------------------------
		ARtk(){


		}

void drawHashT(string hashT){

ofPushStyle();
        ofSetColor(0,0,255);
        ofDrawBitmapString(hashT ,10,10,2);
ofPopStyle();

}
void setup(int width, int height, int threshold = 85){

		    // find all the texture files and load them
        ofSetSmoothLighting(true);
        ofDisableArbTex();
        ofEnableSeparateSpecularLight();
        m_width = width;
        m_height = height;
        m_threshold = threshold;
	//vidGrabber.listDevices();
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(25);
        vidGrabber.initGrabber(width, height);
	//ofSetVerticalSync(true);
	colorImage.allocate(width, height);
	grayImage.allocate(width, height);
	grayThres.allocate(width, height);
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	scultura_129.loadModel("ecotopia/ecotopia_129.3ds",15.0);
	scultura_3831.loadModel("ecotopia/ecotopia_3831.3ds",15.0);
	scultura_3677.loadModel("ecotopia/ecotopia_3677.3ds",20.0);
	scultura_3895.loadModel("ecotopia/ecotopia_3895.3ds",20.0);
	scultura_3767.loadModel("ecotopia/ecotopia_3767.3ds",20.0);
	

	//material.setDiffuseColor(ofColor(0.03f, 0.02f, .0f, 255.0f));
	pointLight.setDiffuseColor( ofColor(5.f, 5.f, 255.f));

        // specular color, the highlight/shininess color //
        pointLight.setSpecularColor( ofColor(2.f, 2.f, 2.f));
        pointLight.setPosition(ofVec3f(0,10,10));
        pointLight.setPointLight();
		// This uses the default camera calibration and marker file
		artk.setup(width, height);
		// The camera calibration file can be created using GML:
		// http://graphics.cs.msu.ru/en/science/research/calibration/cpp
		// and these instructions:
		// http://studierstube.icg.tu-graz.ac.at/doc/pdf/Stb_CamCal.p
		// This only needs to be done once and will aid with detection
		// for the specific camera you are using
		// Put that file in the data folder and then call setup like so:
		 //artk.setup(width, height, "myCamParamFile.cal", "markerboard_480-499.cfg");

		// Set the threshold
		// ARTK+ does the thresholding for us
		// We also do it in OpenCV so we can see what it looks like for debugging

		artk.setThreshold(threshold);
      

		// Box2d
        box2d.init();
        box2d.setGravity(0, 0);
        box2d.createBounds();
        box2d.setFPS(30.0);
        box2d.registerGrabbing();

       
       

  };
void thresMod(int threshold){
artk.setThreshold(threshold);
}
void exit(){

}

void update(){

                    vidGrabber.update();

					bool bNewFrame = vidGrabber.isFrameNew();

					if(bNewFrame) {


					colorImage.setFromPixels(vidGrabber.getPixels(), m_width, m_height);
					grayImage = colorImage;
					// apply a threshold so we can see what is going on
					grayThres = grayImage;
					grayThres.threshold(m_threshold);
					artk.update(grayImage.getPixels());

					}

					box2d.update();
                   


        }





void draw(string hashtags, string hashT){

        //glEnable(GL_DEPTH_BUFFER);
        //grayImage.draw(0,0,1024,768);
 	grayImage.draw(0,0);
    ofPopMatrix();
        artk.draw(0, 0);
        for(int i=0; i<particles.size(); i++) {
		particles[i].get()->draw();
	}
		//int IDnumber = artk.getMarkerID(1);

        ofPushView();
            ofPushStyle();

		//ofDrawBitmapString("center:" + ofToString(artk.getTranslation(IDnumber).x) + " " + ofToString(artk.getTranslation(IDnumber).y),10,40,0);

            ofPopStyle();
        ofPopView();

        artk.applyProjectionMatrix();
	// Find out how many markers have been detected
	int numDetected = artk.getNumDetectedMarkers();


	// Draw for each marker discovered
	for(int i=0; i<numDetected; i++) {
		int IDnumber = artk.getMarkerID(i);
		int num;
		num = 0;
		string IDstring;
		// Set the matrix to the perspective of this marker
		// The origin is in the middle of the marker
		artk.applyModelMatrix(i);
		ofPoint detMarkerCenter = artk.getDetectedMarkerCenter(i);
		if(thresoldV){


		ofPushMatrix();
		ofRotateX(180);
		ofDrawBitmapString("ID number:" + ofToString(IDnumber),10,20,0);
		ofPopMatrix();
		}
      
        if(IDnumber==3766)
		{

			ofPushMatrix();

            ofEnableDepthTest();
			
            float randWidth = ofRandom(20, 60);

            ofPtr<CustomParticle> p = ofPtr<CustomParticle>(new CustomParticle);

	    
            p.get()->setPhysics(1.0, 0.5, 0.3);
            p.get()->setup(box2d.getWorld(), detMarkerCenter.x, detMarkerCenter.y, randWidth, randWidth);
            p.get()->setVelocity(ofRandom(-10, 10), ofRandom(-10, 10));
          
            p.get()->setupTheCustomData(hashtags);
            p.get()->update();
            particles.push_back(p);
           
             if(particles.size()>40) {
                 particles.clear();
          

             }

			ofDisableDepthTest();
			ofPopMatrix();
			
			}else if(IDnumber==3831){
           
ofPushMatrix();
	ofPushView();
		ofPushStyle();
       
		ofVec2f pos = ofVec2f(detMarkerCenter.x,detMarkerCenter.y);
		float shiftX = ofGetWidth() - 800.0f;
		float shiftY = ofGetHeight() - 600.0f;
		    glShadeModel(GL_SMOOTH);
		    ofDisableArbTex();
		    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            		//ofEnableAlphaBlending();
			
            		pointLight.enable();
            		

			ofEnableDepthTest();
			ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			
			
			
           		scultura_3831.draw();
			
           		 pointLight.disable();
           	 	glDisable(GL_LIGHTING);
            		glDisable(GL_LIGHT0);
			ofDisableDepthTest();
            		ofDisableBlendMode();
			//ofDisableAlphaBlending();

			ofPopStyle();
	ofPopView();
ofPopMatrix();
             
			}else if(IDnumber==3894){
			   
			    ofPushMatrix();
               		    ofRotateX(180);
			
			    drawHashT(hashT);
			    ofPopMatrix();

       			}else if (IDnumber==3895){

            ofEnableDepthTest();
            
                ofPushStyle();
                    ofPushMatrix();

			scultura_3895.draw();
                       

                    ofPopMatrix();
                ofPopStyle();
            ofDisableDepthTest();
         
 			}else if (IDnumber==3830){
            ofEnableDepthTest();
            
                ofPushStyle();
                    ofPushMatrix();

			scultura_3767.draw();
                      
                    ofPopMatrix();
                ofPopStyle();
            ofDisableDepthTest();
         
			}else if (IDnumber==3677){
            ofEnableDepthTest();
            
                ofPushStyle();
                    ofPushMatrix();

			scultura_3677.draw();
                       

                    ofPopMatrix();
                ofPopStyle();
            ofDisableDepthTest();
         
			}else if (IDnumber==129){
            ofEnableDepthTest();
            
                ofPushStyle();
                    ofPushMatrix();

			scultura_129.draw();
                    

                    ofPopMatrix();
                ofPopStyle();
            ofDisableDepthTest();
         
			}else if (IDnumber==65){
            ofEnableDepthTest();
            
                ofPushStyle();
                    ofPushMatrix();

			 drawHashT(hashT);
                       

                    ofPopMatrix();
                ofPopStyle();
            ofDisableDepthTest();
         }
        }
};
		};

