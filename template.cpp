// Includes
#include "template.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution (agk::GetDeviceWidth(), agk::GetDeviceHeight());
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetPrintSize(16);

	srand(unsigned int( time(NULL) ));

	agk::SetCameraFOV(1, 90);
	agk::SetCameraRange(1, 0.01, 100);

	gamestate = LOAD;

	agk::SetCameraPosition(1, 15, 15, 15);
	agk::SetCameraLookAt(1, 15, 0, 15, 0);
}

void app::Loop (void)
{
	Global::update();
	Input::update();

	Vec2 test1(5, 3);
	Vec2 test2(-2, 6);
	Vec2 test3 = test1-test2;

	if(gamestate == LOAD)
	{
		world.setup();

		gamestate = MENUSETUP;
	}
	if(gamestate == MENUSETUP)
	{
		gamestate = MENU;
	}
	if(gamestate == MENU)
	{
		agk::Print("Press space to start");

		if(agk::GetRawKeyPressed(32) == 1)
		{
			gamestate = GAMESETUP;
		}
	}
	if(gamestate == GAMESETUP)
	{
		float swordScale = 0.03;
		player.setup();
		player.setSword("media/sword.obj", Vec3(swordScale, swordScale, swordScale));

		world.loadFile("levels/level1.txt");

		//Selecting a spawnpoint
		Vec3 spawnPoint = world.getSpawnpos();

		player.setPosition(spawnPoint);

		spawnPoint = world.getEnemySpawnPos();
		enemy.create(spawnPoint);

		gamestate = GAME;
	}
	if(gamestate == GAME)
	{
		player.update(&world);
		world.update();
		enemy.update(&world, &player);
	}


	agk::Print( agk::ScreenFPS() );
	agk::PrintC("Last key: ");agk::Print(agk::GetRawLastKey());
	agk::PrintC("SpeedMod: ");agk::Print(Global::speedMod);
	agk::PrintC("Gamespeed");agk::Print(Global::gamespeed);
	agk::Sync();
}


void app::End (void)
{

}
