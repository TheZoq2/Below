#pragma once

#include "agk.h"

#include <string>

#include "Vec.h"

class Sword
{
public:
	Sword(void);
	~Sword(void);

	void create(std::string filename, Vec3 scale);

	void setPosition(Vec3 pos);
	void setAngle(float x, float y, float z);
private:
	int objID;

	Vec3 pos;
	Vec3 angle;
};

