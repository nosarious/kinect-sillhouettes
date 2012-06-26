#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
        void exit();
    
        void makeMasked(ofImage mask, ofImage toBeMasked);
        void createMasks(int start);
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		bool                frameByframe;
    
        int movieIndex;
    
    int					angle;
    
    
    ofxKinect 			kinect;
    ofxKinectRecorder 	kinectRecorder;
    ofxKinectPlayer 	kinectPlayer;
    /// used to switch between the live kinect and the recording player
    ofxBase3DVideo* 	kinectSource;
    
    
    ofxCvGrayscaleImage grayImage,grayedImage, graySmall;			// grayscale depth image
    
    
    unsigned char * masked; 
    
    ofImage  mask, makeMe; 
    
    ofImage mask01; // used to create the mask for the cutout
	
	ofImage backdrop, cutout;
    
	ofShader maskShader;
    ofImage depthImage;
    
    
    int HEIGHT, WIDTH;
    int step, vRatio;
};

