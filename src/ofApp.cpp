#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!presS){	//* IF KEYPRESSED IS NOT 'S'
		for (unsigned int i = 0; i < p.size(); i++){
			p[i].setMode(currentMode);
			p[i].update();
			p[i].newRect= rect;
		}
	}

	if (isReplaying == true && fpsCounter <= 61){
		fpsCounter++;
		if (keys[kIndex] == '1'){
			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		}
		if (keys[kIndex] == '2'){
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
		}
		if (keys[kIndex] == '3'){
			currentMode = PARTICLE_MODE_NEAREST_POINTS;
			currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
		}
		if (keys[kIndex] == '4' && fpsCounter == 1){
			currentMode = PARTICLE_MODE_NOISE;
			currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
			resetParticles();
		}
		if (keys[kIndex] == 't' && fpsCounter == 1){
			ofColor r = ofColor::red;
			ofColor g = ofColor::green;
			ofColor b = ofColor::blue;

			ofColor list[3] = {r, g, b};

			for (unsigned int i = 0; i < p.size(); i++){
				p[i].color = list[colorCounter];
			}
			if (colorCounter != 2){
				colorCounter++;
			}
			else{
				colorCounter = 0;
			}
		}
		if (keys[kIndex] == 'd' && fpsCounter == 1){
			for (unsigned int i = 0; i < p.size(); i++){
				p[i].vel *= 2;
			}
		}
		if (keys[kIndex] == 'a' && fpsCounter == 1){
			for (unsigned int i = 0; i < p.size(); i++){
				p[i].vel /= 2;
			}
		}
		if (keys[kIndex] == 's' && fpsCounter == 1){
			if (presS == true)
			{
				presS = false;
			}
			else
			{
				presS = true;
			}
		}
		if (keys[kIndex] == ' ' && fpsCounter == 1){
			resetParticles();
		}
		if (fpsCounter == 60){
			kIndex++;
			fpsCounter = 0;
		}
		if (kIndex == keys.size()){
			isReplaying = false;
			kIndex = 0;
		}
	}

	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(ofColor::yellow);
	ofNoFill();
	ofDrawRectangle(rect);

	if (isRecording){
		ofDrawBitmapString("RECORDING...", 925, 20);
		ofSetColor(ofColor::red);
		ofFill();
		ofDrawCircle(900, 15, 10);
	}
	if (isReplaying){
		ofDrawBitmapString("REPLAYING...", 925, 20);
		ofSetColor(149, 231, 251);
		ofFill();
		ofDrawCircle(900, 15, 10);
	}

	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}
	

	ofSetColor(230);
	ofFill();	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(!isReplaying){
		if( key == '1'){
			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		}
		if( key == '2'){
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
		}
		if( key == '3'){
			currentMode = PARTICLE_MODE_NEAREST_POINTS;
			currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 						
		}
		if( key == '4'){
			currentMode = PARTICLE_MODE_NOISE;
			currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
			resetParticles();
		}
		// When the key 't' is pressed, the particles change color between red, green, and blue.
		if( key == 't'){

			ofColor r = ofColor::red;			
			ofColor g = ofColor::green;
			ofColor b = ofColor::blue;

			ofColor list[3] = {r, g, b};
			

			for(unsigned int i = 0; i < p.size(); i++){
				p[i].color = list[colorCounter];
			}
			if (colorCounter != 2){
				colorCounter++;
			}
			else{
				colorCounter = 0;
			}
		}
		// If the key pressed is d, the velocity of the particle doubles.
		if(key == 'd'){
			for(unsigned int i = 0; i < p.size(); i++){
				p[i].vel *= 2;
			}
		}
		// If the key pressed is a, the velocity of the particle halves.
		if(key == 'a'){
			for(unsigned int i = 0; i < p.size(); i++){
				p[i].vel /= 2;
			}
		}
		// If the key 's' is pressed, the particles pause in the air.
		if (key == 's'){
			if (presS == true){
				presS = false;
			}
			else{
				presS = true;
			}
		}
		if( key == ' '){
			resetParticles();
		}
		if (key == 'r'){	// User can't record while replaying
			if (isRecording == false){
				isRecording = true;
				keys.clear();
			}
			else{
				isRecording = false;
			}
		}
		if (key == 'p' && !isRecording && !keys.empty()){	// USER CAN'T REPLAY WHILE RECORDING.
			isReplaying = true;
			presS = false;
		}
		if (isRecording == true && key != 'p'){
			keys.push_back(key);
		}
	}
	if (key == 'c'){
		isReplaying = false;
		kIndex = 0;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 0){
		x1 = x;
		y1 = y;
	}
	else if (button == 2 && rect.inside(x,y)){
		rect = ofRectangle(0, 0, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (button ==0){
		x2 = x;
		y2 = y;
		rect = ofRectangle(x1, y1, x2-x1, y2-y1);
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
