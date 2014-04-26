#pragma once

#include "agk.h"

#include <string>

#include "Vec.h"
#include "Global.h"

class Sword
{
public:
	Sword(void);
	~Sword(void);

	enum SWINGSTATE{NONE, PREPARE, READY, SWING};

	void create(std::string filename, Vec3 scale);
	void update();
	void setSwingTargetState(SWINGSTATE state);
	void setSwingTargetAngleX(float swingTargetAngleX);

	void setPosition(Vec3 pos);
	void setBaseAngle(float x, float y, float z);

	SWINGSTATE getSwingState();
	Vec3 getCurrentAngle();
	Vec3 getCurrentPosition();
private:
	int objID;
	int targetPosObj;
	int targetPointObj;
	int swingPosObj;

	Vec3 basePos;
	Vec3 baseAngle;

	SWINGSTATE targetState;
	SWINGSTATE state;

	Vec3 cAngle;
	Vec3 cPos;

	float swingTargetAngleX;
	float finalSwingTAngle; //The angle of the swingTarget when the swing starts
	float swingStartTime;

	Vec3 targetPos;
	Vec3 targetPoint;
	Vec3 swingPos;

	Vec3 posPos;
	Vec3 pointPos;
	/*float swingStart;

	Vec3 basePos;
	Vec3 baseAngle;

	Vec3 cPos;
	Vec3 cAngle;

	Vec3 swingAngle;
	Vec3 swingPos;

	float swingAmount;

	SWINGSTATE targetState;
	SWINGSTATE state;

	float swingTargetAngleX;*/
};

