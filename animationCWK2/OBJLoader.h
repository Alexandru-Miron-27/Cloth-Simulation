#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glm/glm.hpp>
#include "glut/glut.h"

#include "Vertex.h"


#pragma once
class OBJLoader
{
private:
	std::string filename;
	
	bool loaded;

public:

	std::vector<Vertex> vertices;
	
	std::vector<int> positionIndices;
	std::vector<int> texcoordIndices;
	std::vector<int> normalIndices;

	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexTexCoord;
	std::vector<glm::vec3> vertexNormals;

	unsigned int textureID;

	OBJLoader()
	{
		this->loaded = false;
	}

	OBJLoader(std::string flname);

	std::string GetFilename();

	std::vector<Vertex> Load();

	bool IsLoaded();

	int SaveToFile(std::string filename);

	int DrawObject();

	int AddHeightOffset(float heightOffset);

	int ReloadVertices();

	int addTexture(std::string textureFilename);

	
};

