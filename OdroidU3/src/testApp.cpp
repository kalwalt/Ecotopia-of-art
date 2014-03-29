//copyright by @kalwalt https://www.kalwaltart.it for @Ecotopiaofart https://twitter.com/Ecotopiaofart please, leave this comment in place!

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {


    ofSetLogLevel(OF_LOG_VERBOSE);
    //ofLogToFile("myLogFile.txt", true);
    ofBackgroundHex(0xfdefc2);

    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
    receiver.setup(PORT);
    current_msg_string = 0;
    buttonTweet = false;
    actualTweet = 0;
    snapCounter = 0;
    bSnapshot = false;
    memset(snapString, 0, 255);		// clear the string by setting all chars to 0

    unsigned delay = 2000;
	unsigned duration = 1000;
    tweenbounce.setParameters(2,easingbounce,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
    font.loadFont("verdana.ttf", 12);


    // load the all the words from a text file and split them
    // up in to a vector of strings

    ecology = ofBufferFromFile("ecology.txt").getText();
    hashtags = ofBufferFromFile("hashtags.txt").getText();
    pixelpoetry = ofBufferFromFile("pixelpoetry.txt").getText();
    step = 0;

    if(ecology.empty() == false) {

        words = ofSplitString(ecology, "|");
    }
    if(hashtags.empty() == false) {

        hashTags = ofSplitString(hashtags, "|");
    }
    if(pixelpoetry.empty() == false) {

        pixelPtry = ofSplitString(pixelpoetry, ",");
    }
    //cout<< words.size()<<endl;

    // we are running the systems commands
    // in a sperate thread so that it does
    // not block the drawing

    currentIndex = 0;

    dna.setup(120);



    string const CONSUMER_KEY = "";
    string const CONSUMER_SECRET = "";

    twitterClient.authorize(CONSUMER_KEY, CONSUMER_SECRET);
    //ar.setup(ofGetWidth(),ofGetHeight());
    ar.setup(1024,768);

           startThread();
}

//--------------------------------------------------------------
void testApp::threadedFunction() {

    while (isThreadRunning()) {

        data = dna.getDna();
        val = data->at(step);
        // cout << "val:"<< val << endl;
        ofSeedRandom();
        //posting an image and a tweet
        currentIndex = (float)ofRandom(1,pixelPtry.size());
        //status = words[ofRandom(10)]+" "+pixelPtry[currentIndex]+" "+words[val] +" "+ hashTags[ofRandom(hashTags.size())];
        status = words[ofMap(val,0,1,0,words.size())] + pixelPtry[currentIndex] + hashTags[(float)ofRandom(0,hashTags.size())];
        ofStringReplace(status, "\n", "");
        ofStringReplace(status, "\t", "");
        hashT= hashTags[ofRandom(hashTags.size())];
        if(status.size()>130){ofDrawBitmapString("status > 130 char!!!",40,20); }
            if(buttonTweet){

                string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";

                //twitterClient.postStatus(status);
                twitterClient.postStatus(status,fileName);

                buttonTweet = false;

            }

        // step to the next word
        step ++;
        step %= words.size();
        // cout << "step:" << step << endl;
        // slowdown boy
        ofSleepMillis(3000);
    }
}

//--------------------------------------------------------------
void testApp::update() {
    ar.update();
    dna.mutate(ofRandom(8));

    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for mouse moved message
		if(m.getAddress() == "/buttonPressed"){
			// both the arguments are int32's
		int	buttonPressed = m.getArgAsInt32(0);
		//int	mouseY = m.getArgAsInt32(1);
		if (buttonPressed==true){

		buttonTweet = true;
            }
		}

	}
}


//--------------------------------------------------------------
void testApp::draw() {

    glEnable(GL_NORMALIZE);
   
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    // twitterClient.printDebugInfo();

    ofPushView();
	ofPushStyle();

  
    ar.draw(hashtags, hashT);
   
    ofPopStyle();
	ofPopView();
    ofDrawBitmapString(ofToString(ar.artk.getNumDetectedMarkers()) + " marker(s) found", 10, 20);

    int strWidth = (status.length()*8) + 5;
     // x and y for the drawing
    float x = (ofGetWidth()-strWidth)/2;
    float y = ofGetHeight()/2;
    float down = ((ofGetWindowHeight()/9)*8) - 20;
    //cout << down<< endl;

    ofPushView();
	ofPushStyle();
    // draw the word
    ofSetColor(0,0,255);
  
    ofRectRounded(10,down- font.getLineHeight()-10,ofGetWidth()-20,font.getLineHeight()*3,10);

    ofSetColor(255);
   
    if(font.stringWidth(status)>(ofGetWidth()-20)){

        //ofDrawBitmapString("staus > 130 char!!!",40,40);
        vector <string> text = ofSplitString(status,"#");
        string statusBreak = text[0] + "\n#" + text[1];
        status = statusBreak;

      }
    font.drawString(status, 20,down);
    string tweeterMsg = "Push the blue button to tweet!";
    int strtweeterMsgWidth = (tweeterMsg.length()*8) + 5;
    ofSetColor(255);
    
    ofRectRounded(10,down- font.getLineHeight()+40,strtweeterMsgWidth+40,font.getLineHeight()*2,10);
    ofSetColor(0,0,255);
   
    font.drawString(tweeterMsg, 20,down+45);
    ofPopStyle();
	ofPopView();

    if(buttonTweet==true){

        if (bSnapshot == true){

        grabImage.grabScreen(0,0,ofGetWidth(), ofGetHeight());

		string fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
		grabImage.saveImage(fileName);
		sprintf(snapString, "saved %s", fileName.c_str());
		snapCounter++;

		bSnapshot = false;
        }

    ofPushView();
	ofPushStyle();
    ofSetColor(220,35,0);
   
    ofRect(strtweeterMsgWidth+60,down- font.getLineHeight()+40,tweenbounce.update(),30);
  
    ofSetColor(0,0,255);
   
    font.drawString("Tweet send!", strtweeterMsgWidth+70,down+45);
    
    ofPopStyle();
	ofPopView();
     }

}
void testApp::exit(){

ar.exit();
//ar.sawSynth->free();

}
//--------------------------------------------------------------
void testApp::keyPressed(int key) {

    if(key == 'b') {

        unsigned delay = 0;
        unsigned duration = 1000;
        buttonTweet = true;
        bSnapshot = true;
        tweenbounce.setParameters(2,easingbounce,ofxTween::easeOut,0,ofGetWidth()-100,duration,delay);
       

    }
    if(key == 'o') {

        buttonTweet = false;
    }


  if(key == OF_KEY_UP) {

		t++;
		ar.thresMod(t);

	} else if(key == OF_KEY_DOWN) {

		t--;
		ar.thresMod(t);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
