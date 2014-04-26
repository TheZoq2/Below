#pragma once

#include "agk.h"

#include "Vec.h"

#include <string>
#include <vector>

class PartBase
{
public:
	void createBox(float w, float h, float d);
	void setTexture(int index, std::string texturePath);
	void reset();

	int getObjID();
private:
	int objID;
	int shaderID;

	int textures[8];
};

class Part
{
public:
	void setup();
	void create(PartBase* base, float x, float y, float z);
	void remove();

	int getObjID();
private:
	int objID;

	float x;
	float y;
	float z;
};

class World
{
public:
	World(void);
	~World(void);

	void setup(); //Load all the base media

	void loadFile(std::string file);
	void clear();

	Vec3 getSpawnpos();
	bool getTileWalkable(Vec2 pos);
private:
	std::vector<PartBase>* floorBase;
	std::vector<PartBase>* wallBase;

	std::vector<std::vector<Part>*>* floor;
	std::vector<std::vector<Part>*>* walls;
};

