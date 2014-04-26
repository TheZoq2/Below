#include "Global.h"

float Global::gameTime;
float Global::time;
float Global::frameTime;
float Global::speedMod;

float Global::gamespeed = 1;

Global::Global(void)
{
}


Global::~Global(void)
{
}

void Global::update()
{
	float oldTime = time;

	time = agk::Timer();

	frameTime = time - oldTime;

	speedMod = frameTime * 60 * gamespeed;

	gameTime = gameTime + frameTime * gamespeed;
}