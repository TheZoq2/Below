#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::setup()
{
	//objID = agk::CreateObjectCone(1, 0.5, 20);
	//objID = agk::CreateObjectCylinder(1.5, 0.5, 10);
	objID = agk::CreateObjectBox(1, 1, 1);
	agk::SetObjectRotation(objID, 90, 0, 0);
	agk::SetObjectPosition(objID, 15, 3, 15);
}
void Player::update(World* world)
{
	float lookModX = 0.1;
	float lookModY = 0.13;
	float sensitivity = 1;

	float headOffset = 0.5;
	float moveSpeed = 0.07;

	int forwardKey = 87;
	int leftKey = 65;
	int rightKey = 68;
	int backKey = 83;

	float colWidth = 0.2;

	//Mouse movement
	angleY = angleY + Input::mouseMove.x * lookModY * sensitivity;
	rotationX = rotationX + Input::mouseMove.y * lookModX * sensitivity;

	if(rotationX > 90)
	{
		rotationX = 90;
	}
	if(rotationX < -90)
	{
		rotationX = -90;
	}

	float xMove = 0;
	float zMove = 0;

	//Movement
	if(agk::GetRawKeyState(forwardKey))
	{
		xMove = xMove + agk::Cos(-angleY + 90) * moveSpeed * Global::speedMod;
		zMove = zMove +  agk::Sin(-angleY + 90) * moveSpeed * Global::speedMod;
	}
	if(agk::GetRawKeyState(leftKey))
	{
		xMove = xMove + agk::Cos(-angleY + 180) * moveSpeed * Global::speedMod;
		zMove = zMove +  agk::Sin(-angleY + 180) * moveSpeed * Global::speedMod;
	}
	if(agk::GetRawKeyState(rightKey))
	{
		xMove = xMove + agk::Cos(-angleY) * moveSpeed * Global::speedMod;
		zMove = zMove +  agk::Sin(-angleY) * moveSpeed * Global::speedMod;
	}
	if(agk::GetRawKeyState(backKey))
	{
		xMove = xMove + agk::Cos(-angleY + 270) * moveSpeed * Global::speedMod;
		zMove = zMove +  agk::Sin(-angleY + 270) * moveSpeed * Global::speedMod;
	}

	float newPosX = pos.x + xMove;
	float newPosZ = pos.z + zMove;

	//Checking collision on x axis
	for(int x = -1; x <= 1; x++)
	{
		float chkX = newPosX + colWidth * x;
		Vec2 chkPos(chkX, pos.z);
		
		if(world->getTileWalkable(chkPos))
		{
			newPosX = pos.x;
		}
	}
	for(int z = -1; z <= 1; z++)
	{
		float chkZ = newPosZ + colWidth * z;
		Vec2 chkPos(pos.x, chkZ);

		if(world->getTileWalkable(chkPos))
		{
			newPosZ = pos.z;
		}
	}
	

	pos.x = newPosX;
	pos.z = newPosZ;

	//Positioning the camera
	agk::SetCameraRotation(1, 0, angleY, 0);

	agk::RotateCameraLocalX(1, rotationX);

	agk::SetCameraPosition(1, pos.x, pos.y + headOffset, pos.z);
}

void Player::setPosition(Vec3 pos)
{
	this->pos = pos;

	agk::SetObjectPosition(objID, pos.x, pos.y, pos.z);
}