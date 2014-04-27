#include "Enemy.h"


Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}

void Enemy::create(Vec3 spawnpoint)
{
	character.create();
	character.setPosition(spawnpoint);
	character.setAngleY(45);

	float swordScale = 0.03;
	sword.create("media/sword.obj", Vec3(swordScale, swordScale, swordScale));
}

void Enemy::update(World* world, Player* player)
{
	pos = character.getPos();
	angle = character.getAngle();

	//Calculating the distance between the player and the character
	Vec3 distVec = pos - player->getPos();

	float dist = sqrt(pow(distVec.x, 2) + pow(distVec.z, 2));

	if(dist < 1)
	{
		sword.setSwingTargetState(Sword::PREPARE);

		if(sword.getSwordReady() == true && sword.getSwingState() == Sword::PREPARE)
		{
			sword.setSwingTargetState(Sword::SWING);
		}

		character.setTarget(pos);
	}
	else
	{
		character.setTarget(player->getPos());
	}
	//character.setTarget(player->getPos());

	character.update(world);

	//Calculating the base position of the sword
	float swordOffsetX = 0.6;
	float swordOffsetZ = 0.3;
	Vec3 swordOffset = pos;
	swordOffset.x = swordOffset.x + agk::Cos(-angle.y) * swordOffsetX;
	swordOffset.z = swordOffset.z + agk::Sin(-angle.y) * swordOffsetX;
	swordOffset.x = swordOffset.x + agk::Cos(-angle.y - 90) * swordOffsetZ;
	swordOffset.z = swordOffset.z + agk::Sin(-angle.y - 90) * swordOffsetZ;

	Vec3 swordAnlge = angle;
	swordAnlge.y = swordAnlge.y + 90;

	//Changing the sword target
	Vec3 plrDiff = pos - player->getPos();

	float plrAngle = agk::ATanFull(plrDiff.x, -plrDiff.z) + 45;
	float swordAngle = plrAngle - angle.y;

	sword.setSwingTargetAngleX(swordAngle);

	sword.setPosition(swordOffset);
	sword.setBaseAngle(swordAnlge);
	sword.update();


	//Pointing the characters arm at the sword
	character.setHandTarget(sword.getCurrentPosition());
}