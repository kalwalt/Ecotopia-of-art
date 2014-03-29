//copyright by @kalwalt https://www.kalwaltart.it for @Ecotopiaofart https://twitter.com/Ecotopiaofart please, leave this comment in place!

#pragma once
#include "ofMain.h"
#include "ofxDna.h"
#include "ofxTween.h"
#include "ofxTwitter.h"
#include "ofxThreadedImage.h"
#include "ARtk.h"

#define PORT 12345
#define NUM_MSG_STRINGS 20

// ---------------------------------------------
class testApp : public ofBaseApp, public ofThread {


public:

    void setup();
    void update();
    void draw();
    void exit();

    void threadedFunction();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofTrueTypeFont font;

    vector <string> words;
    vector <string> hashTags;
    vector<string> text;
    vector<string> pixelPtry;
    string hashtags ;
    string ecology;
    string pixelpoetry;
    int currentIndex;
    int step;

    bool bRandomVoice;
    string voice;
    string status;
    string hashT;
    float val;
    vector<float> * data;

    bool buttonTweet;



    ofxDna dna;

    ofxTween tweenbounce;
    ofxEasingBounce 	easingbounce;

    ofxTwitter twitterClient;

    int actualTweet;

    ofxThreadedImage grabImage;
    int 				snapCounter;
    char 				snapString[255];
    bool 				bSnapshot;

    ARtk ar;
    int t;

    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];

};
