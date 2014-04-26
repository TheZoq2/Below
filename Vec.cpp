#include "Vec.h"

Vec2::Vec2()
{

}
Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2 Vec2::operator=(Vec2 n)
{
	this->x = x;
	this->y = y;

	return *this;
}
Vec2 Vec2::operator-(Vec2 other)
{
	Vec2 newVec = *this;
	newVec.x -= other.x;
	newVec.y -= other.y;

	return newVec;
}

Vec3::Vec3()
{
}
Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3 Vec3::operator=(Vec3 n)
{
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;

	return *this;
}
Vec3 Vec3::operator+(Vec3 n)
{
	Vec3 newVec = *this;
	newVec.x += n.x;
	newVec.y += n.y;
	newVec.z += n.z;

	return newVec;
}