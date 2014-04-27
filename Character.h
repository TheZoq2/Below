#pragma once

#include "agk.h"

#include "World.h"
#include "Global.h"

#include "Vec.h"

class Character
{
public:
	Character(void);
	~Character(void);

	void create();
	void update(World* world);

	void setPosition(Vec3 pos);
	void setAngleY(float angleY);
	void setTarget(Vec3 target);
	void setHandTarget(Vec3 swordHandTarget);

	Vec3 getPos();
	Vec3 getAngle();
private:
	float bodyHeight;
	float headHeight;
	float bodyOffset;
	float legHeight;
	float armHeight;

	int bodyID;
	int headID;
	int legs[2];
	int arms[2];

	Vec3 pos;
	Vec3 angle;

	Vec3 target;

	Vec3 swordHandTarget;
};

