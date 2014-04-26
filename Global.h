#pragma once

#include "agk.h"

class Global
{
public:
	Global(void);
	~Global(void);

	static void update();

	static float gameTime;
	static float time;
	static float frameTime;
	static float speedMod;
};

