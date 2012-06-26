#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

		// get the image which you will use as a backdrop
	backdrop.loadImage("hwy1.jpg");
	
		// get the image you will use as a cutout
	cutout.loadImage("yellowleaf.jpg");
	
    
    //kinect.init();
	kinect.init(true);  // shows infrared instead of RGB video image
	//kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps)
	kinect.setVerbose(true);
	kinect.open();
    
	// start with the live kinect source
	kinectSource = &kinect;
    
    // zero the tilt on startup
//	angle = 10;
//	kinect.setCameraTiltAngle(angle);
    
    int f = 80;
    int g = 60;
    int vRatio = (f*g);
    
    grayImage.allocate(kinect.width, kinect.height);
    grayedImage.allocate(kinect.width, kinect.height);
    mask.allocate(f,g,OF_IMAGE_GRAYSCALE);
    graySmall.allocate(f,g);

    mask01.allocate(f,g,OF_IMAGE_GRAYSCALE);

    
    //need this for alpha to come through
	ofEnableAlphaBlending();
    
    // turn off vertical sync so we can evaluate performance
    ofSetVerticalSync(false);
    
    //set the texture parameters for the maks shader. just do this at the beginning
	maskShader.load("composite");
	maskShader.begin();
    maskShader.setUniformTexture("Tex0", grayImage.getTextureReference(), 0);
	maskShader.setUniformTexture("Tex1", grayImage.getTextureReference(), 1);
	maskShader.end();
	
    
    HEIGHT = cutout.getHeight();
    WIDTH = cutout.getWidth();    
	
}

//--------------------------------------------------------------
void testApp::update(){
    kinectSource->update();
    
    // load grayscale depth image from the kinect source
    grayedImage.setFromPixels(kinectSource->getDepthPixels(), kinect.width, kinect.height);
    graySmall.scaleIntoMe(grayedImage);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    backdrop.draw(0,0, ofGetWidth(),ofGetHeight());
		//comment this next line out to hide the kinect output
	graySmall.draw(0,0);
    	// 100 can be set to change to find best distance for project
    createMasks(100);
    
	makeMasked(mask01, cutout);
}




//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}


void testApp::makeMasked(ofImage mask, ofImage toBeMasked){
		// if you want blurrier outlines, try smaller numbers, fewer cycles than blurring.
		// mask.resize(40,30);
    mask.resize(80,60);
    mask.resize(WIDTH,HEIGHT);
    
    makeMe.setFromPixels(toBeMasked.getPixels(),WIDTH,HEIGHT,OF_IMAGE_COLOR);
    
    //then draw a quad for the top layer using our composite shader to set the alpha
	maskShader.begin();
        
        //our shader uses two textures, the top layer and the alpha
        //we can load two textures into a shader using the multi texture coordinate extensions
        glActiveTexture(GL_TEXTURE0_ARB);
        makeMe.getTextureReference().bind();
        
        glActiveTexture(GL_TEXTURE1_ARB);
        mask.getTextureReference().bind();
        //draw a quad the size of the frame
        glBegin(GL_QUADS);
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);		
            glVertex2f( 0, 0);
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, WIDTH, 0);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, WIDTH, 0);		
            glVertex2f( ofGetWidth(), 0);
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, WIDTH, HEIGHT);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, WIDTH, HEIGHT);		
            glVertex2f( ofGetWidth(), ofGetHeight());
            
            glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, HEIGHT);
            glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, HEIGHT);		
            glVertex2f( 0, ofGetHeight());

        glEnd();
        
        //deactive and clean up
        glActiveTexture(GL_TEXTURE1_ARB);
        mask.getTextureReference().unbind();
        //mask.unbind();
        glActiveTexture(GL_TEXTURE0_ARB);
        makeMe.getTextureReference().unbind();
        
	maskShader.end();
}


// get an image, and create five masks from it.
void testApp::createMasks(int start){
		// load grayscale depth image from the kinect source
    grayImage = graySmall.getPixels();
    unsigned char * pix = grayImage.getPixels();
	
    
		//we could do this with opencv as well
	
    int h = mask01.height;
    int w = mask01.width;
	for(int y = 0; y < h; y ++) {
		for(int x = 0; x < w; x ++) {
        
            int i= x+(y*w);
            int testNum = pix[i];


            if (testNum > start) {
                mask01.getPixelsRef()[i] = 255;
            } else {
                
                mask01.getPixelsRef()[i] = 0;
            }        }
    }
    
    mask01.update();
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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
//--------------------------------------------------------------
void testApp::exit() {
    kinect.close();
}
