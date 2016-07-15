/*
 *  Particle.h
 *  ParticleSystem
 *
 *  Created by nathan_laptop on 7/17/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

class ofxParticle {
public:
    
    // constructors
    ofxParticle();
    
    // properties
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f accel;
    ofVec2f weight;
    // float force;
    ofVec2f force;
    ofVec2f direction;
    ofVec2f target;
    ofVec2f target_rand;
    
    bool attractor;
    
    int WIDTH;
    int HEIGHT;
    
    float maxforce=10;
    
    ofColor color;
    int percent = int(ofRandom(65));
    
    float k;
    
    // methods
    void update();
    void addForce(ofVec2f force);
    void draw(ofColor col);
    void checkEdges();
    void steer();
    void clamp(float WIDTH, float HEIGHT);
    void clamp_circ(float WIDTH, float HEIGHT);
    void move();
    
    float mass;
    float topSpeed;
    float bounce;
    float radius;

    float coe_x = ofRandom(1);
    float coe_y = ofRandom(1);
    
    float clamp_max = ofGetHeight()/2;
    float clamp_r = ofRandom(200,clamp_max);

    float clamp_border_x = 400*(1-coe_x);
    float clamp_border_y = 400*(1-coe_y);
    
};
