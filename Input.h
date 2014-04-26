#pragma once

#include "agk.h"

#include "Vec.h"

class Input
{
public:
	Input(void);
	~Input(void);

	static void update();

	static Vec2 mousePos;
	static Vec2 mouseMove;
};

