#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::setup()
{
	swordTargetObj = agk::CreateObjectPlane(1, 1);
	agk::SetObjectScale(swordTargetObj, 0.3f, 0.3f, 0.3f);

	agk::SetObjectCullMode(swordTargetObj, 2);
	agk::SetObjectVisible(swordTargetObj, 0);

	swordTargetImg = agk::LoadImage("media/swingTarget.png");
	agk::SetObjectImage(swordTargetObj, swordTargetImg, 0);
	agk::SetObjectTransparency(swordTargetObj, 1);
}
void Player::update(World* world)
{
	float lookModX = 0.1f;
	float lookModY = 0.13f;
	float sensitivity = 1;

	float headOffset = 0.5f;
	float moveSpeed = 0.07f;

	int forwardKey = 87;
	int leftKey = 65;
	int rightKey = 68;
	int backKey = 83;

	float colWidth = 0.2f;

	if(sword.getSwingState() != Sword::READY && sword.getSwingState() != Sword::PREPARE)
	{
		//Mouse movement
		angleY = angleY + Input::mouseMove.x * lookModY * sensitivity;
		rotationX = rotationX + Input::mouseMove.y * lookModX * sensitivity;
	}
	else
	{
		float swordSenisitivty = 0.04f;
		swordTargetAngle = swordTargetAngle - Input::mouseMove.x * swordSenisitivty;

		if(swordTargetAngle > 56)
		{
			swordTargetAngle = 56;
		}
		if(swordTargetAngle < -55)
		{
			swordTargetAngle = -55;
		}

		sword.setSwingTargetAngleX(swordTargetAngle);

		/*//Showing the sword targeting indicator
		agk::SetObjectVisible(swordTargetObj, 1);
		
		Vec3 swordPos = sword.getCurrentPosition();
		Vec3 swordAngle = sword.getCurrentAngle();

		agk::SetObjectPosition(swordTargetObj, swordPos.x, swordPos.y, swordPos.z);
		agk::SetObjectRotation(swordTargetObj, swordAngle.x, swordAngle.y, swordAngle.z);

		agk::MoveObjectLocalX(swordTargetObj, 0.3 * .5);
		agk::MoveObjectLocalY(swordTargetObj, 0.3 * .5);
		//agk::RotateObjectLocalZ(swordTargetObj, 90);*/
	}

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

	//Positioning the sword
	sword.setBaseAngle(0, agk::GetCameraAngleY(1) - 90, -15);

	float swordOffsetX = 0.3f;
	float swordOffsetY = 0.3f;

	Vec3 swordOffset(0,0,0);
	swordOffset.x = agk::Cos(-angleY + 90) * swordOffsetX;
	swordOffset.y = -0;
	swordOffset.z = agk::Sin(-angleY + 90) * swordOffsetX;


	//Adding the offset to the left
	swordOffset.x = swordOffset.x + agk::Cos(-angleY) * swordOffsetY;
	swordOffset.z = swordOffset.z + agk::Sin(-angleY) * swordOffsetY;

	Vec3 swordPos(pos.x + swordOffset.x, pos.y + swordOffset.y, pos.z + swordOffset.z);

	sword.setPosition(swordPos);

	//Updating the sword
	if(agk::GetRawMouseLeftPressed())
	{
		swordTargetAngle = 0;
	}
	if(agk::GetRawMouseLeftState())
	{
		sword.setSwingTargetState(Sword::PREPARE);
	}
	else if(agk::GetRawMouseLeftReleased())
	{
		sword.setSwingTargetState(Sword::SWING);
	}
	else
	{
		sword.setSwingTargetState(Sword::NONE);
	}

	sword.update();

	if(sword.getSwingState() == Sword::PREPARE)
	{
		float speedTarget = 0.2;
		
		Global::gamespeed = Global::gamespeed + 0.1 *(speedTarget - Global::gamespeed);
	}
	else
	{
		float speedTarget = 1;
		
		Global::gamespeed = Global::gamespeed + 0.1 *(speedTarget - Global::gamespeed);
	}
}

void Player::setPosition(Vec3 pos)
{
	this->pos = pos;

	agk::SetObjectPosition(objID, pos.x, pos.y, pos.z);
}

void Player::setSword(std::string filename, Vec3 pos)
{
	sword.create(filename, pos);
}

Vec3 Player::getPos()
{
	return pos;
}