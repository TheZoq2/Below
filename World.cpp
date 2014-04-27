#include "World.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void PartBase::createBox(float w, float h, float d)
{
	objID = agk::CreateObjectBox(w, h, d);

	agk::SetObjectVisible(objID, 0);
}
void PartBase::reset()
{
	objID = 0;
	shaderID = 0;
	
	for(unsigned int i = 0; i < 8; i++)
	{
		textures[i] = 0;
	}
}

void PartBase::setTexture(int index, std::string texturePath)
{
	if(index < 0 || index > 7)
	{
		return;
	}
	
	textures[index] = agk::LoadImage(texturePath.data());
	agk::SetImageMagFilter(textures[index], 1);
	agk::SetImageMinFilter(textures[index], 1);

	agk::SetObjectImage(objID, textures[index], index);
}
void PartBase::setShader(std::string vertex, std::string fragment)
{
	shaderID = agk::LoadShader(vertex.data(), fragment.data());

	agk::SetObjectShader(objID, shaderID);
}
void PartBase::setShaderConstant(std::string name, float x, float y, float z, float w)
{
	agk::SetShaderConstantByName(shaderID, name.data(), x, y, z, w);
}

int PartBase::getObjID()
{
	return objID;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void Part::setup()
{
	objID = 0;
}
void Part::create(PartBase* base, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	objID = agk::InstanceObject(base->getObjID());

	agk::SetObjectPosition(objID, x, y, z);
	agk::SetObjectVisible(objID, 1);
}
void Part::remove()
{

}

int Part::getObjID()
{
	return objID;
}
bool Part::getInPart(Vec2 pos, float border)
{
	float xDiff = abs(x - pos.x);
	float zDiff = abs(z - pos.y);

	if(xDiff < border + 0.5 && zDiff < border + 0.5)
	{
		return true;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

World::World(void)
{
	
}


World::~World(void)
{
}

void World::setup()
{
	floorBase = new std::vector<PartBase>;
	wallBase = new std::vector<PartBase>;
	floor = new std::vector<std::vector<Part>*>;
	walls = new std::vector<std::vector<Part>*>;

	//Loading all the base floors
	PartBase tempBase;
	tempBase.createBox(1, 1, 1);
	tempBase.setTexture(0, "media/floor2.png");
	tempBase.setShader("shaders/floor.vert", "shaders/floor.frag");

	floorBase->push_back(tempBase);

	//Loading base walls
	tempBase.reset();
	tempBase.createBox(1, 2, 1);
	tempBase.setTexture(0, "media/wall2.png");
	tempBase.setShader("shaders/floor.vert", "shaders/floor.frag");
	wallBase->push_back(tempBase);
}
void World::update()
{
	for(unsigned int i = 0; i < floorBase->size(); i++)
	{
		float camX = agk::GetCameraX(1);
		float camY = agk::GetCameraY(1);
		float camZ = agk::GetCameraZ(1);
		floorBase->at(i).setShaderConstant("camPos", camX, camY, camZ, 1);
	}

	for(unsigned int i = 0; i < wallBase->size(); i++)
	{
		float camX = agk::GetCameraX(1);
		float camY = agk::GetCameraY(1);
		float camZ = agk::GetCameraZ(1);
		wallBase->at(i).setShaderConstant("camPos", camX, camY, camZ, 1);
	}
}

void World::loadFile(std::string file)
{
	char wallChar = '#';
	char floorChar = 'f';

	if(agk::GetFileExists(file.data()))
	{
		//Opening the file
		int fileID = agk::OpenToRead(file.data());

		int cX = 0; //The current x row
		while(agk::FileEOF(fileID) == 0)
		{
			Part noPart;
			noPart.setup();
			//Fixing vectors
			std::vector<Part>* tempVec = new std::vector<Part>;
			floor->push_back(tempVec);
			tempVec = new std::vector<Part>;
			walls->push_back(tempVec);

			char* linePtr = agk::ReadLine(fileID);
			std::string line = linePtr;

			for(unsigned int z = 0; z < line.size(); z++)
			{
				if(line.at(z) == wallChar)
				{
					//Selecting a base
					int baseIndex = rand() % wallBase->size();
					
					PartBase* base = &wallBase->at(baseIndex);

					Part part;
					part.create(base, cX, 1, z);

					walls->at(cX)->push_back(part);
				}
				else
				{
					walls->at(cX)->push_back(noPart);
				}

				if(line.at(z) == floorChar)
				{
					//Selecting a base
					int baseIndex = rand() % floorBase->size();
					
					PartBase* base = &floorBase->at(baseIndex);

					Part part;
					part.create(base, cX, -0.5, z);

					floor->at(cX)->push_back(part);
				}
				else
				{
					floor->at(cX)->push_back(noPart);
				}
			}

			delete[] linePtr;

			cX++;
		}
	}
}
void World::clear()
{
	if(floor != NULL)
	{
		for(unsigned int x = 0; x < floor->size(); x++)
		{
			for(unsigned int y = 0; y < floor->size(); y++)
			{
				floor->at(x)->at(y).remove();
			}

			floor->at(x)->clear();
		}

		floor->clear();
	}

	if(walls != NULL)
	{
		for(unsigned int x = 0; x < walls->size(); x++)
		{
			for(unsigned int y = 0; y < walls->size(); y++)
			{
				walls->at(x)->at(y).remove();
			}

			walls->at(x)->clear();
		}

		floor->clear();
	}
}

Vec3 World::getSpawnpos()
{
	Vec3 pos;
	bool posFound = false;
	//Selecting a floor
	while(posFound == false)
	{
		unsigned int x = rand() % floor->size();
		unsigned int z = rand() % floor->at(x)->size();

		if(floor->at(x)->at(z).getObjID() != 0)
		{
			pos.x = x;
			pos.y = 1;
			pos.z = z;

			posFound = true;
		}
	}

	return pos;
}
Vec3 World::getEnemySpawnPos()
{
	return getSpawnpos();
}
bool World::getTileWalkable(Vec2 pos, float border)
{
	//Checking if there is a wall there
	//Converting to tile coords
	/*int tileX = agk::Round(pos.x);
	int tileZ = agk::Round(pos.y);

	if(tileX >= 0 && tileX < walls->size())
	{
		if(tileZ >= 0 && tileZ < walls->at(tileX)->size())
		{
			if(walls->at(tileX)->at(tileZ).getObjID() != 0)
			{
				return true; //This is not walkable
			}
		}
	}*/
		
	for(unsigned int x = 0; x < walls->size(); x++)
	{
		for(unsigned int y = 0; y < walls->size(); y++)
		{
			if(walls->at(x)->at(y).getInPart(pos, border))
			{
				return true;
			}
		}
	}
	

	return false;
}