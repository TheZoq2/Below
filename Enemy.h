#pragma once

#include <string>
#include <vector>

#include "agk.h"

#include "World.h"
#include "Sword.h"
#include "Player.h"
#include "Character.h"

#include <vector>

class Enemy
{
public:
	Enemy(void);
	~Enemy(void);

	void create(Vec3 spawnpoint);

	void update(World* world, Player* player);
private:
	Character character;

	Vec3 pos;
	Vec3 angle;

	Sword sword;
};

