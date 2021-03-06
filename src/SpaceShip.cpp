#include "SpaceShip.h"

#include "Util.h"

SpaceShip::SpaceShip() {
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw() {

	TextureManager::Instance()->
		draw("spaceship", getTransform()->position.x, getTransform()->position.y, m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, getTransform()->position + m_orientation * 60.0f);
}

void SpaceShip::update() { 
	
	m_Move();
}

void SpaceShip::clean() { }

void SpaceShip::setDestination(const glm::vec2 _dest) {

	m_destination = _dest;
}

void SpaceShip::setMaxSpeed(const float _speed) { 

	m_maxSpeed = _speed;
}

void SpaceShip::setOrientation(const glm::vec2 _orientation) {

	m_orientation = _orientation;
}

void SpaceShip::setRotation(const float _angle) { 

	m_rotationAngle = _angle;
}

void SpaceShip::m_Move() {

	// Direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;

	// Normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}
