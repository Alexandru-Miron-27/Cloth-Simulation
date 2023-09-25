#define STB_IMAGE_IMPLEMENTATION
#include "OBJLoader.h"
#include "stb_image.h"
#include "glut/glut.h"

OBJLoader::OBJLoader(std::string flname)
{
	this->filename = flname;
	this->loaded = false;
}
std::string OBJLoader::GetFilename()
{
	return this->filename;
}

bool OBJLoader::IsLoaded()
{
	if (this->loaded == false)
	{
		return false;
	}
	return true;
}

int OBJLoader::ReloadVertices()
{
	for (size_t i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i].position = vertexPositions[positionIndices[i] - 1];
		this->vertices[i].texCoord = vertexTexCoord[texcoordIndices[i] - 1];
		this->vertices[i].normal = vertexNormals[normalIndices[i] - 1];
	}
	return 1;
}

std::vector<Vertex> OBJLoader::Load()
{
	// Vertex vector

	std::stringstream stream;
	std::ifstream objFile(this->filename);
	std::string line = "";

	int value = 0;

	//reading from .obj file
	if (!objFile.is_open())
	{
		std::cerr << "Could not open .obj file: " << this->filename << std::endl;
		exit(404);
	}

	while (std::getline(objFile, line))
	{
		std::string keyword = "";
		stream.clear();
		stream.str(line);
		stream >> keyword;

		if (keyword == "v")
		{
			glm::vec3 tmpPos;
			stream >> tmpPos.x >> tmpPos.y >> tmpPos.z;
			vertexPositions.push_back(tmpPos);
		}
		else if (keyword == "vt")
		{
			glm::vec2 tmpTexcoord;
			stream >> tmpTexcoord.x >> tmpTexcoord.y;
			vertexTexCoord.push_back(tmpTexcoord);
		}
		else if (keyword == "vn")
		{
			glm::vec3 tmpNormals;
			stream >> tmpNormals.x >> tmpNormals.y >> tmpNormals.z;
			vertexNormals.push_back(tmpNormals);
		}
		else if (keyword == "f")
		{
			unsigned int nrValues = 0;
			unsigned int counter = 0;

			while (stream >> value)
			{
				if (counter == 0)
				{
					positionIndices.push_back(value);
					nrValues++;
				}
				else if (counter == 1)
				{
					texcoordIndices.push_back(value);
					nrValues++;
				}
				else if (counter == 2)
				{
					normalIndices.push_back(value);
					nrValues++;
				}

				//Skipping characters
				if (stream.peek() == '/')
				{
					counter++;
					stream.ignore(1, '/');
				}
				else if (stream.peek() == ' ')
				{
					counter++;
					stream.ignore(1, ' ');
				}

				if (counter > 2)
				{
					counter = 0;
				}

				if (nrValues > 9)
				{
					std::cerr << "OBJLoader :: Too many vertices in one face. A face can only be a triangle " << std::endl;
					exit(44);
				}
			}
		}
		else
		{

		}
		//Building final vertices array
		this->vertices.resize(positionIndices.size(), Vertex());

		for (size_t i = 0; i < this->vertices.size(); i++)
		{
			this->vertices[i].position = vertexPositions[positionIndices[i] - 1];
			this->vertices[i].texCoord = vertexTexCoord[texcoordIndices[i] - 1];
			this->vertices[i].normal = vertexNormals[normalIndices[i] - 1];
		}
	}
	this->loaded = true;
	return this->vertices;
}

int OBJLoader::DrawObject()
{ 
	std::ofstream testOutput;
	testOutput.open("./objs/testVertices.txt");
	this->addTexture("./textures/clothTexture.jpg");

	if (!testOutput)
	{
		exit(266);
	}

	testOutput << "----------\n   FILENAME: " << this->GetFilename() << "\n---------------------\n";
	for (size_t i = 0; i < this->vertices.size(); i = i + 3)
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLES);
		/*glColor3f(1.0f, 0.0f, 0.0f);*/
		glTexCoord2f(this->vertices[i].texCoord.x, this->vertices[i].texCoord.y);
		glNormal3f(this->vertices[i].normal.x, this->vertices[i].normal.y, this->vertices[i].normal.z);
		glVertex3f(this->vertices[i].position.x, this->vertices[i].position.y, this->vertices[i].position.z);
		testOutput << this->vertices[i].position.x << " " << this->vertices[i].position.y - 2.0f << " " << this->vertices[i].position.z << "\n";
		/*glColor3f(0.0f, 1.0f, 0.0f);*/
		glTexCoord2f(this->vertices[i + 1].texCoord.x, this->vertices[i + 1].texCoord.y);
		glNormal3f(this->vertices[i + 1].normal.x, this->vertices[i + 1].normal.y, this->vertices[i + 1].normal.z);
		glVertex3f(this->vertices[i + 1].position.x, this->vertices[i + 1].position.y, this->vertices[i + 1].position.z);
		testOutput << this->vertices[i + 1].position.x << " " << this->vertices[i + 1].position.y - 2.0f << " " << this->vertices[i + 1].position.z << "\n";
		/*glColor3f(0.0f, 0.0f, 1.0f);*/
		glTexCoord2f(this->vertices[i + 2].texCoord.x, this->vertices[i + 2].texCoord.y);
		glNormal3f(this->vertices[i + 2].normal.x, this->vertices[i + 2].normal.y, this->vertices[i + 2].normal.z);
		glVertex3f(this->vertices[i + 2].position.x, this->vertices[i + 2].position.y, this->vertices[i + 2].position.z);	
		testOutput << this->vertices[i + 2].position.x << " " << this->vertices[i + 2].position.y - 2.0f << " " << this->vertices[i + 2].position.z << "\n";
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	testOutput.close();
	return 1;

}

int OBJLoader::SaveToFile(std::string filename)
{

	std::ofstream outputFile;
	outputFile.open(filename);

	if (!outputFile)
	{
		std::cerr << "Output file was not able to be closed" << std::endl;
	}

	for (size_t i = 0; i < this->vertexPositions.size(); i++)
	{
		outputFile << "v " << this->vertexPositions[i].x << " " 
						   << this->vertexPositions[i].y << " "
						   << this->vertexPositions[i].z << std::endl;
	}
	for (size_t i = 0; i < this->vertexTexCoord.size(); i++)
	{
		outputFile << "vt " << this->vertexTexCoord[i].x << " "
							<< this->vertexTexCoord[i].y <<std::endl;
	}
	for (size_t i = 0; i < this->vertexNormals.size(); i++)
	{
		outputFile << "vn " << this->vertexNormals[i].x << " "
						   << this->vertexNormals[i].y << " "
						   << this->vertexNormals[i].z << std::endl;
	}

	for (size_t i = 0; i < this->positionIndices.size(); i = i + 3)
	{
		outputFile << "f " << positionIndices[i] <<"/"<< texcoordIndices[i] << "/" << normalIndices[i] <<" "
						   << positionIndices[i + 1] << "/" << texcoordIndices[i + 1] << "/" << normalIndices[i + 1] <<" "
						   << positionIndices[i + 2] << "/" << texcoordIndices[i + 2] << "/" << normalIndices[i + 2] << std::endl;
	}

	outputFile.close();
	return 1;
}

int OBJLoader::AddHeightOffset(float heightOffset)
{
	for (size_t i = 0; i < this->vertices.size(); i++)
	{
		this->vertices[i].position.y += heightOffset;
	}
	for (size_t i = 0; i < this->vertexPositions.size(); i++)
	{
		this->vertexPositions[i].y += heightOffset;
	}
	return 1;
}

int OBJLoader::addTexture(std::string textureFilename)
{
	int width, height, bpp;

	unsigned char* textureImageData = stbi_load("./textures/clothTexture.jpg", &width, &height, &bpp, 0);

	if (!textureImageData)
	{
		exit(770);
	}

	//generating texture
	glGenTextures(1, &this->textureID);

	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImageData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, this->textureID);
	stbi_image_free(textureImageData);


}