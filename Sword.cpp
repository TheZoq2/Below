#include "Sword.h"


Sword::Sword(void)
{
}


Sword::~Sword(void)
{
}

void Sword::create(std::string filename, Vec3 scale)
{
	objID = agk::LoadObject(filename.data());

	agk::SetObjectScale(objID, scale.x, scale.y, scale.z);
}

void Sword::setPosition(Vec3 pos)
{
	//this->pos = pos;

	agk::SetObjectPosition(objID, pos.x, pos.y, pos.z);
}
void Sword::setAngle(float x, float y, float z)
{
	this->angle.x = x;
	this->angle.y = y;
	this->angle.z = z;

	agk::SetObjectRotation(objID, x, y, z);
}