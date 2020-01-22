#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->radius = 12;
	auto x_span = this->radius * sqrt(3);
	auto flg = true;
	for (float y = 0; y < ofGetHeight() + this->radius; y += this->radius * 1.5) {

		for (float x = 0; x < ofGetWidth() + this->radius; x += x_span) {

			glm::vec2 location;
			if (flg) {

				location = glm::vec2(x, y);
			}
			else {

				location = glm::vec2(x + (this->radius * sqrt(3) / 2), y);
			}

			this->hexagon_list.push_back(location);
			this->noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
			this->alpha_list.push_back(0);
		}
		flg = !flg;
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (int k = 0; k < 4; k++) {

		glm::vec2 noise_location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 0, ofGetHeight()));

		for (int i = 0; i < this->hexagon_list.size(); i++) {

			if (glm::distance(this->hexagon_list[i], noise_location) < 50) {

				this->alpha_list[i] = this->alpha_list[i] < 255 ? this->alpha_list[i] + 50 : 255;
			}
			else {

				this->alpha_list[i] = this->alpha_list[i] > 0 ? this->alpha_list[i] - 2 : 0;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (int i = 0; i < this->hexagon_list.size(); i++) {

		vector<glm::vec2> vertices;
		for (auto deg = 90; deg < 450; deg += 60) {

			vertices.push_back(this->hexagon_list[i] + glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD)));
		}

		color.setHsb(ofMap(ofNoise(glm::vec3(this->noise_seed_list[i], ofGetFrameNum() * 0.05)), 0, 1, 0, 255), 130, 255);
		//color = ofColor(ofMap(ofNoise(glm::vec3(this->noise_seed_list[i], ofGetFrameNum() * 0.05)), 0, 1, 39, 139));

		ofFill();
		ofSetColor(color, this->alpha_list[i]);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(239);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}