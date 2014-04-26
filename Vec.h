#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);

	float x;
	float y;

	Vec2 operator=(Vec2);
	Vec2 operator-(Vec2 other);
};

class Vec3
{
public:
	Vec3();
	Vec3(float x, float y, float z);

	float x;
	float y;
	float z;

	Vec3 operator=(Vec3);
};