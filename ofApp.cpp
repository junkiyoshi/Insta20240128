#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	ofSeedRandom(39);

	float span = 0.5;
	ofColor color;
	for (int i = 0; i < 5; i++)	{

		auto noise_seed = ofRandom(1000);
		for (float x = 30; x < 690; x += span) {

			for (float y = 30; y < 690; y += span) {

				float noise_value = ofNoise(noise_seed, x * 0.005, y * 0.005, glm::distance(glm::vec2(360, 360), glm::vec2(x, y)) * 0.01 + ofGetFrameNum() * 0.03);
				if (noise_value > 0.55 && noise_value < 0.65) {


					this->mesh.addVertex(glm::vec3(x, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
					this->mesh.addVertex(glm::vec3(x, y + span, 0));

					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

					color.setHsb(ofMap(i, 0, 5, 0, 255), 255, 255);
					for (int i = 0; i < 4; i++) {

						this->mesh.addColor(color);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	int start = 1;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}