#include "ClothSimulator.h"


float ClothSimulator::DistancePoints(glm::vec3 p1, glm::vec3 p2)
{
	float distance = 0.0f;
	distance = sqrt((p2.x - p1.x) * (p2.x - p1.x) +
					(p2.y - p1.y) * (p2.y - p1.y) +
					(p2.z - p1.z) * (p2.z - p1.z));

	return distance;
}

float ClothSimulator::VectorLength(glm::vec3 v)
{
	float length = 0;
	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return length;
}

int ClothSimulator::ResendFromGrid()
{


	//sending changed vertex info back from grid
	//to this->cloth->verticesPositions, Texcoord and Normals
	for (size_t i = 0; i < this->width; i++)
	{ //for each row of square grid
		for (size_t j = 0; j < this->width; j++)
		{ // for each column of square grid
			this->cloth->vertexPositions[i * this->width + j] = this->particles[i][j].vertex.position;
			this->cloth->vertexNormals[i * this->width + j] = this->particles[i][j].vertex.normal;
			this->cloth->vertexTexCoord[i * this->width + j] = this->particles[i][j].vertex.texCoord;
			//only vertex data is necessary for initial grid
			//this->particles[i][j].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}

	this->cloth->ReloadVertices();
	return 1;
}

int ClothSimulator::SetupGrids()
{
	//n is number of vertices on row
	int n = sqrt(this->cloth->vertexPositions.size());
	//create Particles grid (n*n)
	this->particles.resize(n, std::vector<Particle>(n));
	for (size_t i = 0; i < sqrt(this->cloth->vertexPositions.size()); i++)
	{ //for each row of square grid
		for (size_t j = 0; j < sqrt(this->cloth->vertexPositions.size()); j++)
		{ // for each column of square grid
			this->particles[i][j].vertex.position = this->cloth->vertexPositions[i * n + j];
			this->particles[i][j].vertex.normal = this->cloth->vertexNormals[i * n + j];
			this->particles[i][j].vertex.texCoord = this->cloth->vertexTexCoord[i * n + j];
			this->particles[i][j].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}

	this->initParticles.resize(n, std::vector<Particle>(n));
	for (size_t i = 0; i < sqrt(this->cloth->vertexPositions.size()); i++)
	{ //for each row of square grid
		for (size_t j = 0; j < sqrt(this->cloth->vertexPositions.size()); j++)
		{ // for each column of square grid
			this->initParticles[i][j].vertex.position = this->cloth->vertexPositions[i * n + j];
			this->initParticles[i][j].vertex.normal = this->cloth->vertexNormals[i * n + j];
			this->initParticles[i][j].vertex.texCoord = this->cloth->vertexTexCoord[i * n + j];
			//only vertex data is necessary for initial grid
			this->initParticles[i][j].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	return 1;
}

glm::vec3 ClothSimulator::ComputeSpringForceDamping(Particle* v1C, Particle* v2C,
	Particle* v1R, Particle* v2R, springType type)
{
	glm::vec3 springForce = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 p1C = v1C->vertex.position;
	glm::vec3 p2C = v2C->vertex.position;
	glm::vec3 p1R = v1R->vertex.position;
	glm::vec3 p2R = v2R->vertex.position;
	//lengths between particles
	float currentLength = DistancePoints(p1C, p2C);
	float restLength = DistancePoints(p1R, p2R);
	glm::vec3 directionVector = (v2C->vertex.position - v1C->vertex.position)
							/ VectorLength(v2C->vertex.position - v1C->vertex.position);


	//figure out how to make the connection between v1C, v2C and v1R, v2R
	if (type == structural)
	{
		springForce = (this->stiffnessStructural * (currentLength - restLength) 
			- this->kD * glm::dot(v2C->velocity - v1C->velocity, directionVector)) * directionVector;
	}
	else if (type == shear)
	{
		springForce = (this->stiffnessShear * (currentLength - restLength)
			- this->kD * glm::dot(v2C->velocity - v1C->velocity, directionVector)) * directionVector;
	}
	else if (type == flexion)
	{
		springForce = (this->stiffnessFlexion * (currentLength - restLength)
			- this->kD * glm::dot(v2C->velocity - v1C->velocity, directionVector)) * directionVector;
	}

	return springForce;
}

glm::vec3 ClothSimulator::ComputeSpringForce(Particle* v1C, Particle* v2C,
	Particle* v1R, Particle* v2R, springType type)
{
	glm::vec3 springForce = glm::vec3(0.0f, 0.0f, 0.0f);

	if (type == structural)
	{
		springForce = this->stiffnessStructural *
			(DistancePoints(v1C->vertex.position, v2C->vertex.position) - DistancePoints(v1R->vertex.position, v2R->vertex.position))
			* (v1C->vertex.position - v2C->vertex.position) / VectorLength(v1C->vertex.position - v2C->vertex.position);
	}
	else if (type == shear)
	{
		springForce = this->stiffnessShear *
			(DistancePoints(v1C->vertex.position, v2C->vertex.position) - DistancePoints(v1R->vertex.position, v2R->vertex.position))
			* (v1C->vertex.position - v2C->vertex.position) / VectorLength(v1C->vertex.position - v2C->vertex.position);
	}
	else if (type == flexion)
	{
		springForce = this->stiffnessFlexion *
			(DistancePoints(v1C->vertex.position, v2C->vertex.position) - DistancePoints(v1R->vertex.position, v2R->vertex.position))
			* (v1C->vertex.position - v2C->vertex.position) / VectorLength(v1C->vertex.position - v2C->vertex.position);
	}
	return springForce;
}

int ClothSimulator::CenterCloth()
{
	float xOffset, zOffset;
	xOffset = this->initParticles[this->width / 2][this->width / 2].vertex.position.x;
	zOffset = this->initParticles[this->width / 2][this->width / 2].vertex.position.z;

	for (size_t i = 0; i < sqrt(this->cloth->vertexPositions.size()); i++)
	{ //for each row of square grid
		for (size_t j = 0; j < sqrt(this->cloth->vertexPositions.size()); j++)
		{ // for each column of square grid
			this->particles[i][j].vertex.position.x -= xOffset;
			this->particles[i][j].vertex.position.z -= zOffset;
			this->initParticles[i][j].vertex.position.x -= xOffset;
			this->initParticles[i][j].vertex.position.z -= zOffset;
		}
	}
	return 1;
}

ClothSimulator::ClothSimulator(std::string flname, float startPos, glm::vec3 sphereOrig, float sphereR, glm::vec3 windForce)
{
	this->cloth = new OBJLoader(flname);
	this->cloth->Load();

	//saved cloth mesh in initial state;  
	this->startCloth = new OBJLoader(flname);
	this->startCloth->Load();

	//setting initial members
	this->width = sqrt(this->cloth->vertexPositions.size());
	this->startHeight = startPos;
	this->deltaT = 0.005f;
	this->sphereOrigin = sphereOrig;
	this->sphereRadius = sphereR;
	this->windVector = windForce;
	

	//adding surface offset
	float sphereSurfaceOffset = 0.05f;
	if (this->sphereRadius > 0.0f)
	{
		this->sphereRadius = this->sphereRadius + sphereSurfaceOffset;
	}

	//move cloth at startPos height
	this->cloth->AddHeightOffset(this->startHeight);
	this->startCloth->AddHeightOffset(this->startHeight);

	//creating particles and initial particles grids
	this->SetupGrids();
	this->CenterCloth();
	this->ResendFromGrid();

}

glm::vec3 ClothSimulator::ComputeSpringForceSum(int i, int j) {
	//compute the sum of all spring forces
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	//structural springs
	if (j + 1 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i][j + 1],
			&this->initParticles[i][j], &this->initParticles[i][j + 1],
			structural);
	}
	if (j - 1 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i][j - 1],
			&this->initParticles[i][j], &this->initParticles[i][j - 1],
			structural);
	}
	if (i - 1 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i - 1][j],
			&this->initParticles[i][j], &this->initParticles[i - 1][j],
			structural);
	}
	if (i + 1 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i + 1][j],
			&this->initParticles[i][j], &this->initParticles[i + 1][j],
			structural);
	}
	//shear springs
	if (i + 1 < this->width && j + 1 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i + 1][j + 1],
			&this->initParticles[i][j], &this->initParticles[i + 1][j + 1],
			shear);
	}
	if (i - 1 >= 0 && j - 1 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i - 1][j - 1],
			&this->initParticles[i][j], &this->initParticles[i - 1][j - 1],
			shear);
	}
	if (i - 1 >= 0 && j + 1 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i - 1][j + 1],
			&this->initParticles[i][j], &this->initParticles[i - 1][j + 1],
			shear);
	}
	if (i + 1 < this->width && j - 1 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i + 1][j - 1],
			&this->initParticles[i][j], &this->initParticles[i + 1][j - 1],
			shear);
	}
	//flexion springs
	if (j + 2 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i][j + 2],
			&this->initParticles[i][j], &this->initParticles[i][j + 2],
			flexion);
	}
	if (j - 2 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i][j - 2],
			&this->initParticles[i][j], &this->initParticles[i][j - 2],
			flexion);
	}
	if (i - 2 >= 0)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i - 2][j],
			&this->initParticles[i][j], &this->initParticles[i - 2][j],
			flexion);
	}
	if (i + 2 < this->width)
	{
		sum = sum + ComputeSpringForce(&this->particles[i][j], &this->particles[i + 2][j],
			&this->initParticles[i][j], &this->initParticles[i + 2][j],
			flexion);
	}
	return sum;
}

int ClothSimulator::SimulateStep()
{ //this starts the simulation
	std::ofstream sumOutput;
	sumOutput.open("./objs/sumOutput.txt");

	if (!sumOutput)
	{
		exit(553);
	}

	//for each vertex on grid
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
		{ //compute total spring force for every grid particle
			this->particles[i][j].springForce = ComputeSpringForceSum(i, j);
		}
	}

	sumOutput.close();

	//change positions using velocity and grid position
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			glm::vec3 fnet = glm::vec3(0.0f, 0.0f, 0.0f);
			//Computing net force applied
			fnet = this->vertexMass * this->gravityVector + this->windVector - this->particles[i][j].springForce;

			float distanceToOrigin;
				
			glm::vec3 newPosition = this->particles[i][j].vertex.position + deltaT * this->particles[i][j].velocity;
			distanceToOrigin = DistancePoints(newPosition, this->sphereOrigin);

			if (distanceToOrigin >= this->sphereRadius)
			{ // we are not inside the sphere, update position
				//position at t + deltaT
				//current velocity
				this->particles[i][j].velocity = this->particles[i][j].velocity + deltaT * fnet / this->vertexMass;
				this->particles[i][j].vertex.position = this->particles[i][j].vertex.position + deltaT * this->particles[i][j].velocity;
				
			}	
			else
			{
				this->particles[i][j].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			//check for floor collision
			if (this->particles[i][j].vertex.position.y <= 0.0f)
			{
				//stop if on floor level
				this->particles[i][j].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				this->particles[i][j].vertex.position = glm::vec3(this->particles[i][j].vertex.position.x
					, 0.0f, this->particles[i][j].vertex.position.z);
				
			}
			
		}
	}
	this->ResendFromGrid();

	return 1;
}


int ClothSimulator::SimulateStepFixedCorners()
{ //this starts the simulation
	std::ofstream sumOutput;
	sumOutput.open("./objs/sumOutput.txt");

	if (!sumOutput)
	{
		exit(553);
	}

	//for each vertex on grid
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
		{ 
			//compute total spring force for every grid particle
			this->particles[i][j].springForce = ComputeSpringForceSum(i, j);
		}
	}

	sumOutput.close();

	//change positions using velocity and grid position
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (!(i == 0 && j == 0) && !(i == 0 && j == this->width - 1))
			{
				glm::vec3 fnet = glm::vec3(0.0f, 0.0f, 0.0f);
				//computing force 
				fnet = this->vertexMass * this->gravityVector + this->windVector - this->particles[i][j].springForce;
				//current velocity
				this->particles[i][j].velocity = this->particles[i][j].velocity + deltaT * fnet / this->vertexMass;
				//position at t + deltaT
				this->particles[i][j].vertex.position = this->particles[i][j].vertex.position + deltaT * this->particles[i][j].velocity;
				
				if (this->particles[i][j].vertex.position.y <= 0.0f)
				{
					//stop if on floor level
					this->particles[i][j].vertex.position = glm::vec3(this->particles[i][j].vertex.position.x
						, 0.0f, this->particles[i][j].vertex.position.z);

				}
				
			}
		}
	}
	this->ResendFromGrid();
	
	return 1;
}