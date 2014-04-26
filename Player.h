#pragma once

#include "agk.h"

#include "World.h"
#include "Vec.h"
#include "Input.h"
#include "Global.h"

class Player
{
public:
	Player(void);
	~Player(void);

	void setup();
	void update(World* world);

	void setPosition(Vec3 pos);
private:
	int objID;

	Vec3 pos;

	float angleY;
	float rotationX;
};

