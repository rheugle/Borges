#pragma once
#include "ofMain.h"
#include "ofxOpenCV.h"
#include "ofxParticle.h"
#include "ofxVoronoi2D.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxSimpleSerial.h"

#define PORT 8338
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
    public:
    
    void setup();
    void update();
    void draw();

    typedef map<ofIndexType, vector<ofIndexType> > VertexGraph;
    ofMesh performSmooth(ofMesh &m, VertexGraph connectivityGraph, float relaxationFactor);
    void smoothMesh(ofMesh & m, VertexGraph connectivityGraph, int iterations);

    ofVideoGrabber cam;
    ofxCvColorImage colorImg;
    
    int WIDTH = ofGetScreenWidth();
    int HEIGHT = ofGetScreenHeight();
    
    std::list<ofxParticle> particles;
    
    ofxVoronoi2D voronoi;
    vector<ofVec2f> pts;
    
    ofMesh mesh;
    
    unsigned int count;
    int dispMode;
    
    ofMesh explode_mesh(ofMesh * inMesh, ofPixels p);
    ofxPanel gui;
    
    ofxOscReceiver receiver;
    ofImage receivedImage;
    ofVec2f pts_target[66];

    //Populate in some extra points for regions around nose etc - which percent correspond to which features?
    ofVec2f pts_target_extra[100];

    //ofSerial serial;
    ofxSimpleSerial serial;

    bool facefound;
  
    ofColor p_1 = ofColor(20,20,250,1);
    ofColor p_2 = ofColor(230,30,230,1);
    ofColor p_3 = ofColor(20,240,240,1);
    ofColor p_4 = ofColor(220,200,230,1);
    ofColor p_5 = ofColor(255,255,255,1);
    
    ofColor col_arr[4] = {p_1, p_2, p_3, p_4,};

    //PERLIN NOISE FOR RANDOM ARDUINO MOVEMENTS - code in random values amplitdue = range. min position = min
    //float value = min + amplitude * ofNoise( timePosition + position0 );
    
};
