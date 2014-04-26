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
/*void Sword::update()
{
	//Resetting the position/angle
	agk::SetObjectRotation(objID, baseAngle.x, baseAngle.y, baseAngle.z);
	agk::SetObjectPosition(objID, basePos.x, basePos.y, basePos.z);

	Vec3 pos = basePos;

	if(targetState == PREPARE)
	{
		//If the state is none, the actual state can switch to prepare
		if(state == NONE)
		{
			state = PREPARE;

			swingStart = Global::gameTime;

			swingTargetAngleX = 0;
		}
	}

	if(state == PREPARE)
	{
		if(targetState == NONE)
		{
			state = NONE;
		}
	}
	if(state == PREPARE || state == READY)
	{
		float prepareTime = 0.3; //The time it takes to prepare the swing

		float prepareAmount = (Global::gameTime - swingStart) / prepareTime;

		if(prepareAmount > 1)
		{
			prepareAmount = 1;

			state = READY;
		}

		float targetRotationZ = 35;
		float targetPosY = 0.1;

		////////////////////////////////////////
		float cRotationZ = targetRotationZ * prepareAmount;

		agk::RotateObjectLocalZ(objID, cRotationZ);

		pos.y = pos.y + targetPosY * prepareAmount;

		//Setting the current gamespeed
		Global::gamespeed = 1 - 0.85 * prepareAmount;

		agk::RotateObjectLocalX(objID, swingTargetAngleX);
	}

	if(state == READY)
	{
		if(targetState == SWING)
		{
			state = SWING;

			swingStart = Global::gameTime;

			//Saving the current angle
			swingAngle.x = agk::GetObjectAngleX(objID) - baseAngle.x;
			swingAngle.y = agk::GetObjectAngleY(objID) - baseAngle.y;
			swingAngle.z = agk::GetObjectAngleZ(objID) - baseAngle.z;

			swingPos = pos;

			swingAmount = 0;
		}
	}

	if(state == SWING)
	{
		float swingSpeed = 14 * Global::speedMod;
		//Resetting the gametime
		float gameTimeResetTime = 0.05;
		float resetAmount = (Global::gameTime - swingStart) / gameTimeResetTime;

		if(resetAmount > 1)
		{
			resetAmount = 1;
		}
		Global::gamespeed = 1 - 0.85 * (1 - resetAmount);

		agk::SetObjectRotation(objID, baseAngle.x + swingAngle.x, baseAngle.y + swingAngle.y, baseAngle.z + swingAngle.z);
		
		pos.y = swingPos.y;

		//Actually swinging the sword
		swingAmount = swingAmount - swingSpeed;

		if(swingAmount < -130)
		{
			state = NONE;
		}

		agk::RotateObjectLocalZ(objID, swingAmount);
	}

	agk::SetObjectPosition(objID, pos.x, pos.y, pos.z);

	cAngle.x = agk::GetObjectAngleX(objID);
	cAngle.y = agk::GetObjectAngleY(objID);
	cAngle.z = agk::GetObjectAngleZ(objID);
	cPos = pos;
}*/

void Sword::update()
{
	
}

void Sword::setPosition(Vec3 basePos)
{
	this->basePos = basePos;

	agk::SetObjectPosition(objID, basePos.x, basePos.y, basePos.z);
}
void Sword::setBaseAngle(float x, float y, float z)
{
	this->baseAngle.x = x;
	this->baseAngle.y = y;
	this->baseAngle.z = z;
}
void Sword::setSwingTargetState(SWINGSTATE targetState)
{
	this->targetState = targetState;
}
void Sword::setSwingTargetAngleX(float swingTargetAngleX)
{
	this->swingTargetAngleX = swingTargetAngleX;
}

Sword::SWINGSTATE Sword::getSwingState()
{
	return state;
}
Vec3 Sword::getCurrentAngle()
{
	return cAngle;
}
Vec3 Sword::getCurrentPosition()
{
	return this->cPos;
}