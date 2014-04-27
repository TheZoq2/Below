#include "Character.h"


Character::Character(void)
{
}


Character::~Character(void)
{
}

void Character::create()
{
	bodyOffset = 0.1; //Relative to pos.y
	bodyHeight = 0.7;
	headHeight = 0.3;
	legHeight = 1 + bodyOffset - bodyHeight / 2;
	armHeight = 0.9 + bodyOffset - bodyHeight / 2;

	bodyID = agk::CreateObjectBox(0.5, bodyHeight, 0.3);
	headID = agk::CreateObjectBox(0.3, headHeight, 0.3);

	for(unsigned int i = 0; i < 2; i++)
	{
		legs[i] = agk::LoadObject("media/leg.obj");

		agk::SetObjectScale(legs[i], 0.2, legHeight, 0.2);
	}
	for(unsigned int i = 0; i < 2; i++)
	{
		arms[i] = agk::LoadObject("media/leg.obj");

		agk::SetObjectScale(arms[i], 0.1, armHeight, 0.1);
	}
}
void Character::update(World* world)
{
	float speed = 0.05 * Global::speedMod;
	//calculating the angle between the character and the target
	float diffX = target.x - pos.x;
	float diffZ = target.z - pos.z;

	//'moving towards the target
	if(abs(diffX) > 0.1 || abs(diffZ) >0.1)
	{
		angle.y = agk::ATanFull(diffX, diffZ);

		pos.x = pos.x + agk::Cos(angle.y - 90) * speed;
		pos.z = pos.z + agk::Sin(angle.y - 90) * speed;

		angle.y = -angle.y;
	}

	//Updating the "model"
	setPosition(pos);
	
	agk::SetObjectRotation(bodyID, 0, angle.y, 0);
	agk::SetObjectRotation(headID, 0, angle.y, 0);

	for(unsigned int i = 0; i < 2; i++)
	{
		agk::SetObjectRotation(legs[i], 0, angle.y, 0);
		agk::SetObjectRotation(arms[i], 0, angle.y, 0);
	}

	//"animating" the legs
	for(unsigned int i = 0; i < 2; i++)
	{
		float legAngle = 30 * agk::Sin(Global::gameTime * 360 + 180*i);

		agk::RotateObjectLocalX(legs[i], legAngle);
	}

	agk::SetObjectLookAt(arms[1], swordHandTarget.x, swordHandTarget.y, swordHandTarget.z,  agk::GetObjectAngleX(arms[1]));
	//agk::SetObjectPosition(arms[1], swordHandTarget.x, swordHandTarget.y, swordHandTarget.z);
	agk::RotateObjectLocalX(arms[1], -90);
}

void Character::setPosition(Vec3 pos)
{
	this->pos = pos;

	agk::SetObjectPosition(bodyID, pos.x, pos.y + bodyOffset, pos.z);
	agk::SetObjectPosition(headID, pos.x, pos.y + bodyOffset + bodyHeight / 2 + headHeight / 2, pos.z);

	for(unsigned int i = 0; i < 2; i++)
	{
		float legOffsetX;
		if(i == 0)
		{
			legOffsetX = -0.25 + 0.1;
		}
		else
		{
			legOffsetX = 0.25 - 0.1;
		}

		Vec3 legPos(pos.x, pos.y - bodyHeight / 2 + bodyOffset, pos.z);

		legPos.x = legPos.x + agk::Cos(-angle.y) * legOffsetX;
		legPos.z = legPos.z + agk::Sin(-angle.y) * legOffsetX;

		agk::SetObjectPosition(legs[i], legPos.x, legPos.y, legPos.z);
	}
	for(unsigned int i = 0; i < 2; i++)
	{
		float armOffsetX;
		if(i == 0)
		{
			armOffsetX = -0.25;
		}
		else
		{
			armOffsetX = 0.25;
		}

		Vec3 armPos(pos.x, pos.y + bodyHeight / 2 + bodyOffset / 2, pos.z);

		armPos.x = armPos.x + agk::Cos(-angle.y) * armOffsetX;
		armPos.z = armPos.z + agk::Sin(-angle.y) * armOffsetX;

		agk::SetObjectPosition(arms[i], armPos.x, armPos.y, armPos.z);
	}
}
void Character::setAngleY(float angleY)
{
	this->angle.y = angleY;
}
void Character::setTarget(Vec3 target)
{
	this->target = target;
}
void Character::setHandTarget(Vec3 swordHandTarget)
{
	this->swordHandTarget = swordHandTarget;
}

Vec3 Character::getPos()
{
	return pos;
}
Vec3 Character::getAngle()
{
	return angle;
}