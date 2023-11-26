#include "ofFluidSystem.h"

void ofFluidSystem::setup()
{	
	gui_.setup();
	gui_.add(gravity_.setup("Gravity", 9.8f, -100.f, 100.f));
	gui_.add(particleSize_.setup("Particle Size", 0.5f, 0.f, 5.f));
	gui_.add(collisionDamping_.setup("Collision Damping", 1, 0, 5));
	gui_.add(boundsSize_.setup("Bounds Size", ofVec2f(16.f, 11.f), ofVec2f(10.f, 10.f), ofVec2f(100.f, 100.f)));

	// Place particles in a grid formation
	int particlesPerRow = (int)std::sqrt(numParticles);
	int particlesPerCol = (numParticles - 1) / particlesPerRow + 1;
	float spacing = particleSize_ * 2 + particleSpacing;

	for (int i = 0; i < numParticles; ++i) {
		float x = (i % particlesPerRow - particlesPerRow / 2.f + 0.5f) * spacing;
		float y = (i / particlesPerRow - particlesPerCol / 2.f + 0.5f) * spacing;
		positions_.push_back(ofVec2f(x, y));
		velocities_.push_back(ofVec2f(0.f, 0.f));
	}
}

void ofFluidSystem::update()
{
	for (int i = 0; i < positions_.size(); ++i) {
		velocities_[i] += ofVec2f(0, -1) * gravity_ * ofGetLastFrameTime();
		positions_[i] += velocities_[i] * ofGetLastFrameTime();

		resolveCollisions(&positions_[i], &velocities_[i]);		
	}
	
    //std::cout << "Pos: " << position_.x << ":" << position_.y << "; DeltaTime: " << ofGetLastFrameTime() << std::endl;
}

void ofFluidSystem::draw()
{
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
	ofScale(50.f);
	ofRotateDeg(180);
	
    ofSetColor(ofColor::lightBlue);
	for (int i = 0; i < positions_.size(); ++i) {
		ofDrawCircle(positions_[i], particleSize_);		
	}

	ofSetColor(ofColor::green);
	auto halfBoundsSize = boundsSize_ / 2;
	ofDrawLine(-halfBoundsSize.x, -halfBoundsSize.y, halfBoundsSize.x, -halfBoundsSize.y);
	ofDrawLine(halfBoundsSize.x, -halfBoundsSize.y, halfBoundsSize.x, halfBoundsSize.y);
	ofDrawLine(halfBoundsSize.x, halfBoundsSize.y, -halfBoundsSize.x, halfBoundsSize.y);
	ofDrawLine(-halfBoundsSize.x, halfBoundsSize.y, -halfBoundsSize.x, -halfBoundsSize.y);

	ofPopMatrix();
	
    gui_.draw();
}

void ofFluidSystem::resolveCollisions(ofVec2f* position, ofVec2f* velocity) {
	ofVec2f halfBoundsSize = boundsSize_ / 2 - ofVec2f(1., 1.) * particleSize_;

	if (std::abs(position->x) > halfBoundsSize.x) {
		position->x = halfBoundsSize.x * ((int)(position->x > 0) - (int)(position->x < 0));
		velocity->x *= -1 * collisionDamping_;		
	}

	if (std::abs(position->y) > halfBoundsSize.y) {
		position->y = halfBoundsSize.y * ((int)(position->y > 0) - (int)(position->y < 0));
		velocity->y *= -1 * collisionDamping_;
	}
}

