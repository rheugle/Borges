#include "ofApp.h"
using namespace ofxCv;

float	floatData[4] = {1.1, 2.2, 3.3, 4.4};
long	longData[4] = {4, 3, 2, 1};

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFullscreen(true);
    cam.setVerbose(true);
    gui.setup();
    
    ofSetFrameRate(60);

    cam.initGrabber(WIDTH, HEIGHT);
    colorImg.allocate(WIDTH, HEIGHT);

    for (int i=0;i<8000;i++){
        particles.push_back(ofxParticle());
    }

    for (list<ofxParticle>::iterator i = particles.begin(); i != particles.end(); ++i){
        i->WIDTH = WIDTH;
        i->HEIGHT = HEIGHT;
        i->vel = ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
        i->target_rand = ofVec2f(ofRandom(2,WIDTH-2),ofRandom(2,HEIGHT-2));
    }
    
    ofBackground(255);
    
    //OSC
    ofSetVerticalSync(true);
    receiver.setup(PORT);
    
    //SERIAL COMMUNICATION WITH ARDUINO
    int baud = 9600;
    serial.listDevices();
    serial.setup(1, baud);
    serial.startContinuousRead(false);
    serial.listDevices();
    
    //NEEDED AS TAG FOR ARDUINO
    facefound=false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    HOW TO HANDLE ARDUINO UPDATES - perhaps move to draw
    
    ofLog()<<facefound;
    if(facefound==true){
        serial.writeString("y");
        ofLog()<<"FOUND";
        // send packet with easy serial protocol
    }
    else{
        serial.writeString("n");
        ofLog()<<"NOTFOUND";
    }
  }
    
//--------------------------------------------------------------
void ofApp::draw(){

    cam.update();
    colorImg.clear();
    colorImg.setFromPixels(cam.getPixels(), WIDTH, HEIGHT);
    colorImg.mirror(false,true);
    ofPixels p = colorImg.getPixels();
    
    ofxOscMessage m;
    receiver.getNextMessage(m);
    
    if (m.getNumArgs() == 132){
        facefound=true;
        pts.clear();
        int j=0;
        for(int i = 0; i < m.getNumArgs(); i+=2){
            ofVec2f point = ofVec2f(WIDTH-m.getArgAsFloat(i)*2.1,m.getArgAsFloat(i+1)*1.7);
            pts_target[j]=point;
            j+=1;
        }
        for (list<ofxParticle>::iterator i = particles.begin(); i != particles.end(); ++i){
            if (i->attractor==TRUE){
                i->target = pts_target[i->percent];
                i -> steer();
                i -> clamp(WIDTH,HEIGHT);
                //i -> clamp_circ(WIDTH,HEIGHT);
            }
            pts.push_back(i->loc);
            //ofColor col = p.getColor(i ->loc.x, i->loc.y);
            //i -> draw(col);
        }
    }
    else{
        facefound=false;
        pts.clear();
        for (list<ofxParticle>::iterator i = particles.begin(); i != particles.end(); ++i){
            if (i->attractor==TRUE){
                i->target = i->target_rand;
                i -> steer();
                i -> clamp(WIDTH,HEIGHT);
                //i -> clamp_circ(WIDTH,HEIGHT);
            }
            pts.push_back(i->loc);
            //ofColor col = p.getColor(i ->loc.x, i->loc.y);
            //i -> draw(col);
        }
    }

    voronoi.compute(pts, ofRectangle(1.0f, 1.0f, WIDTH-2, HEIGHT-2), 0.0f);

    //BUILD TRIANGULAR MESH
//    ofMesh mesh;
//    voronoi.buildMesh(mesh);
//    
//    //DRAW TRIANGULAR MESH
//    ofColor col1 = ofColor(20,20,255,10);
//    ofSetColor(col1);
//    mesh.drawWireframe();
//    
    //DRAW THE VORONOI DIAGRAM
    int edgecount=0;
    for(ofxSegmentIterator it = voronoi.edges(); it; ++it){
        
        ofxSegment s = *it;
        ofColor col1 = p.getColor(s.p1.x, s.p1.y);
        ofSetColor(col1,150);
        
        ofCircle(s.p1, 3);
        ofCircle(s.p2, 3);
        ofLine(s.p1, s.p2);
        
        edgecount+=1;
    }

    ofLog()<<edgecount;
    mesh.clear();
}
