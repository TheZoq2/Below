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

	targetPosObj = agk::CreateObjectBox(0.2, 0.2, 0.2);
	//agk::SetObjectVisible(targetPosObj, 0);
	targetPointObj = agk::CreateObjectBox(0.2, 0.2, 0.2);
	//targetPointObj = agk::CreateObjectCone(.2, 0.2, 10);
	//agk::SetObjectVisible(targetPointObj, 0);

	swingPosObj = agk::CreateObjectSphere(0.2, 20, 20);
	//agk::SetObjectVisible(swingPosObj, 0);

	int texture = agk::LoadImage("media/sword.png");
	agk::SetObjectImage(objID, texture, 0);
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
	agk::SetObjectPosition(objID, basePos.x, basePos.y, basePos.z);
	agk::SetObjectRotation(objID, baseAngle.x, baseAngle.y, baseAngle.z);

	//Swingstates
	if(state == NONE)
	{
		//If a swing should be prepared
		if(targetState == PREPARE)
		{
			state = PREPARE;

			prepareStartTime = Global::gameTime;
		}

		//position the targets
		targetPos = Vec3(0,0,0);

		//Calculating the position of the targe	
		Vec3 targetOffset(0,0,0);

		targetOffset.y = targetOffset.y + 1;

		targetPoint = targetOffset;
	}

	if(state == PREPARE)
	{
		if(targetState == NONE)
		{
			state =  NONE;
		}

		//calculating the target position of the sword
		targetPos = Vec3(0,0,0);
		targetPos.y = targetPos.y + 0.2; //A bit higher than the default position

		//Calculating the "point target"
		//It should be positioned behind the base pos, also depends on the current target angle

		//The x offset will always be the same
		//The y and z offset are based on the angle of the target
		float xOffset = -0.5;
		
		targetPoint = Vec3(0, 0, 0);
		targetPoint.x = agk::Cos(-baseAngle.y) * xOffset;
		targetPoint.z = agk::Sin(-baseAngle.y) * xOffset;
		//targetPoint.y = 1;

		float yOffset = 1;
		targetPoint.y = agk::Cos(-swingTargetAngleX) * yOffset;
		//targetPoint.x = targetPoint.x + agk::Sin(-swingTargetAngleX) * yOffset;
		float zOffsetTarget = agk::Sin(-swingTargetAngleX) * yOffset; //The offset amount relative to the sword

		//Calculating the position of the target in world coords
		targetPoint.x = targetPoint.x + agk::Cos(-baseAngle.y - 90) * zOffsetTarget;
		targetPoint.z = targetPoint.z + agk::Sin(-baseAngle.y - 90) * zOffsetTarget;

		//calculating the swing position
		agk::SetObjectRotation(swingPosObj, 0, baseAngle.y, 0);
		agk::SetObjectPosition(swingPosObj, basePos.x, basePos.y, basePos.z);

		agk::RotateObjectLocalY(swingPosObj, swingTargetAngleX);
		agk::MoveObjectLocalX(swingPosObj, 1.5);

		swingPos.x = agk::GetObjectX(swingPosObj) - basePos.x;
		swingPos.y = agk::GetObjectY(swingPosObj) - basePos.y;
		swingPos.z = agk::GetObjectZ(swingPosObj) - basePos.z;

		if(targetState == SWING)
		{
			state = SWING;

			finalSwingTAngle = swingTargetAngleX;
			
			swingStartTime = Global::gameTime;
		}
	}
	if(state == SWING)
	{
		float swingDuration = 0.7; //The amount of time a swing will last
		//calculating the swing position
		agk::SetObjectRotation(swingPosObj, 0, baseAngle.y, 0);
		agk::SetObjectPosition(swingPosObj, basePos.x, basePos.y, basePos.z);

		agk::RotateObjectLocalY(swingPosObj, finalSwingTAngle);
		agk::MoveObjectLocalX(swingPosObj, 1.5);

		swingPos.x = agk::GetObjectX(swingPosObj) - basePos.x;
		swingPos.y = agk::GetObjectY(swingPosObj) - basePos.y;
		swingPos.z = agk::GetObjectZ(swingPosObj) - basePos.z;

		targetPoint = swingPos;

		//If the swing is finished
		if(Global::gameTime - swingStartTime > swingDuration)
		{
			state = NONE;
		}
	}

	//Moving the pos towards the target
	posPos.x = posPos.x + 0.1*(targetPos.x - posPos.x);
	posPos.y = posPos.y + 0.1*(targetPos.y - posPos.y);
	posPos.z = posPos.z + 0.1*(targetPos.z - posPos.z);

	Vec3 pos = posPos + basePos;

	agk::SetObjectPosition(objID, pos.x, pos.y, pos.z);

	pointPos.x = pointPos.x + 0.05*(targetPoint.x - pointPos.x);
	pointPos.y = pointPos.y + 0.05*(targetPoint.y - pointPos.y);
	pointPos.z = pointPos.z + 0.05*(targetPoint.z - pointPos.z);

	Vec3 lookAtPos = basePos + pointPos;

	agk::SetObjectLookAt(objID, lookAtPos.x, lookAtPos.y, lookAtPos.z, 90);
	//Making the sword face forward
	if(state == NONE)
	{
		agk::RotateObjectLocalZ(objID, baseAngle.y + 90);
	}

	//Positioning the target objects for debugging
	agk::SetObjectPosition(targetPosObj, targetPos.x, targetPos.y, targetPos.z);
	agk::SetObjectPosition(targetPointObj, targetPoint.x + basePos.x, targetPoint.y + basePos.y, targetPoint.z + basePos.z);
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
void Sword::setBaseAngle(Vec3 baseAngle)
{
	this->baseAngle = baseAngle;
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
	return this->posPos + basePos;
}
bool Sword::getSwordReady()
{
	Vec3 posDiff = posPos - targetPos;
	Vec3 pointDiff = pointPos - targetPoint;

	float tolerance = 0.05;

	if(abs(posDiff.x) < tolerance && abs(posDiff.y) < tolerance && abs(posDiff.z) < tolerance)
	{
		if(abs(pointDiff.x) < tolerance && abs(pointDiff.y) < tolerance && abs(pointDiff.z) < tolerance)
		{
			return true;
		}
	}

	return false;
}