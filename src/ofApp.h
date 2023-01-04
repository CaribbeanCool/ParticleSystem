#pragma once

#include "ofMain.h"
#include "Particle.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		particleMode currentMode;
		string currentModeStr;

		bool presS = false;
		int colorCounter = 0;
		int fpsCounter = 0;

		int x1;
		int y1;
		int x2;
		int y2;
		ofRectangle rect;

		bool isRecording = false;
		bool isReplaying = false;

		vector<char> keys;
		unsigned int kIndex = 0;

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;
		
};
