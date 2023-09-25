#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>

#include <glm/glm.hpp>
#include "glut/glut.h"

#include "Vertex.h"
#include "Particle.h"
#include "OBJLoader.h"

#pragma once
class ClothSimulator
{

	enum springType{structural, shear, flexion};

private:

	OBJLoader *startCloth;
	float vertexMass = 0.3f;
	int width; //the cloth is a square
	glm::vec3 gravityVector = glm::vec3(0.0f, -9.8f, 0.0f);
	glm::vec3 windVector;
	//Spring constants
	float stiffnessStructural = 100.0f; 
	float stiffnessShear = 100.0f;
	float stiffnessFlexion = 100.0f;
	float kD = 10.0f;
	float startHeight;
	float deltaT;


	glm::vec3 sphereOrigin;
	float sphereRadius;


public:

	OBJLoader* cloth;
	std::vector<std::vector<Particle>> particles;
	std::vector<std::vector<Particle>> initParticles;

	//actual constructor
	ClothSimulator(std::string flname, float startPos, glm::vec3 sphereOrig, float sphereR, glm::vec3 windForce);

	int SimulateStep();

	int SimulateStepFixedCorners();

	float DistancePoints(glm::vec3 p1, glm::vec3 p2);

	glm::vec3 ComputeSpringForceDamping(Particle* v1C, Particle* v2C, Particle* v1R, Particle* v2R, springType type);

	glm::vec3 ComputeSpringForce(Particle* v1C, Particle* v2C, Particle* v1R, Particle* v2R, springType type);

	float VectorLength(glm::vec3 v);

	int ResendFromGrid();

	int SetupGrids();

	int CenterCloth();

	glm::vec3 ComputeSpringForceSum(int i, int j);


};

