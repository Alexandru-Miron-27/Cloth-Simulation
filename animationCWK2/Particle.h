#pragma once

#include <glm/glm.hpp>
#include "Vertex.h";

struct Particle {
	Vertex vertex;
	float mass;
	float acceleration;
	glm::vec3 springForce;
	glm::vec3 velocity;
};