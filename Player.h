#pragma once

#include "agk.h"

#include "World.h"
#include "Vec.h"
#include "Input.h"
#include "Global.h"
#include "Sword.h"

class Player
{
public:
	Player(void);
	~Player(void);

	void setup();
	void update(World* world);

	void setPosition(Vec3 pos);

	void setSword(std::string filename, Vec3 scale);
private:
	int objID;
	int swordTargetObj;
	int swordTargetImg;

	Vec3 pos;

	float angleY;
	float rotationX;

	Sword sword;
	float swordTargetAngle;
};

