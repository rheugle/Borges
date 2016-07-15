//
//  ofxParticle.cpp
//  BrgesFinal1
//
//  Created by Ravi Heugle on 3/23/16.
//
//

#include "ofxParticle.h"

ofxParticle::ofxParticle(){

    WIDTH = ofGetWidth();
    HEIGHT = ofGetHeight();
    
    float r = ofRandom(1);
    if (r>0.2){
        attractor=TRUE;
        loc = ofVec2f(ofRandom(WIDTH/2-clamp_r+1, WIDTH/2+clamp_r-1),ofRandom(HEIGHT/2-clamp_r+1, HEIGHT/2+clamp_r-1));
    }
    else{
        attractor=FALSE;
        loc = ofVec2f(ofRandom( 0, WIDTH), ofRandom(0, HEIGHT));
    }
    
    
    //Attract more heavily to specific facial features
    if(percent<20){
        k=0.2;
    }
    else if(percent>=20 && percent <40){
        k=0.2;
    }
    else{
        k=0.2;
    }

}

void ofxParticle::draw(ofColor col){
    
    ofSetColor(col,80);
    ofFill();
    ofDrawCircle(loc.x, loc.y, 2);
}

void ofxParticle::steer() {
    
    
    float mass = 0.2;
    float dt = 1.0/60.0;
    
    ofPoint direction = target - loc;
    
    float len = direction.length();
    float h = k*(len);
    direction.normalize();
    
    ofPoint force = direction*(h) - 0.5*direction;
    ofPoint a = force/mass;
    
    if(vel.length()>200){
        vel.scale(200);
    }
    
    vel += a * dt;
    loc += vel * dt;
    
}

void ofxParticle::move(){
 
    float dt = 1.0/60.0;
    loc += vel * dt;

}

void ofxParticle::clamp(float WIDTH, float HEIGHT){
    
    int buffer = 2;
    
    if( loc.x > WIDTH - clamp_border_x - buffer){
        loc.x = WIDTH - clamp_border_x - buffer;
        vel.x *= -1.0;
    }else if( loc.x < clamp_border_x + buffer){
        loc.x = clamp_border_x + buffer;
        vel.x *= -1.0;
    }
    if( loc.y > HEIGHT - clamp_border_y - buffer){
        loc.y = HEIGHT - clamp_border_y - buffer;
        vel.y *= -1.0;
    }
    else if( loc.y < clamp_border_y + buffer ){
        loc.y = clamp_border_y + buffer;
        vel.y *= -1.0;
    }
}

void ofxParticle::clamp_circ(float WIDTH, float HEIGHT){

    float r = ofDist(loc.x,loc.y, WIDTH/2, HEIGHT/2);
    
    ofLog()<<"R: "<<r<<"CLAMP R"<<clamp_r;

    if (r>clamp_r){
        
        float theta = atan((loc.y-HEIGHT/2)/(loc.x-WIDTH/2));
        ofLog()<<"THETA: "<<theta;
        
        loc.x = clamp_r*cos(theta);
        loc.y = clamp_r*sin(theta);
        
        vel.x*=-1;
        vel.y*=-1;
        
    }
    
}





