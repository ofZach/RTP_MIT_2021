#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	spot.loadImage("spot.png");
	
	for (int i = 0; i < 200; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		myParticle.img = &spot;
		particles.push_back(myParticle);
		
	}
	
	bRepel		= true;
	radius		= 40;
	strength	= 0.5f; 
	
	
	ofBackground(60, 60, 60);
	
}

//--------------------------------------------------------------
void ofApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		
		particles[i].addAttractionForce(mouseX, mouseY, 1000, 0.4);
		
	
		for (int j = 0; j < i; j++){
			if (bRepel){
				particles[i].addRepulsionForce(particles[j], radius, strength);
			} else {
				particles[i].addAttractionForce(particles[j], radius, strength);
			}
		}
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
		particles[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
    ofBackground(180,180,180);
    
	ofEnableAlphaBlending();
	ofSetColor(0,130,130, 200);
	
	ofSetColor(255,255,255,80);
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	
	string reportString =	"(space) = reset\n(a/s) strength = " + ofToString(strength) + 
							"\n(z/x) radius = " + ofToString(radius) + 
							"\n(r) toggle mode = " + (bRepel ? "repelling" : "attracting");
	
	ofSetColor(40,40,0);
	ofRect(10,10,300,80);
	ofSetColor(255,255,255);
	ofDrawBitmapString(reportString, 30, 30);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':
			// reposition everything: 
			for (int i = 0; i < particles.size(); i++){
				particles[i].setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			}
			break;
		case 'a':
			strength += 0.02f;
			break;
		case 's':
			strength -= 0.02f;
			if (strength <= 0) strength = 0.02f;
			break;
		case 'z':
			radius += 5.0f;
			break;
		case 'x':
			radius -= 5.0f;
			if (radius <= 0) radius = 5.0f;
			break;
		case 'r':
			bRepel = !bRepel;
			break;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	particles.erase(particles.begin());
	particle myParticle;
	myParticle.img = &spot;
	myParticle.setInitialCondition(x,y,0,0);
	particles.push_back(myParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(){
}
