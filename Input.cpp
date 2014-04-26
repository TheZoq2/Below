#include "Input.h"

Vec2 Input::mousePos;
Vec2 Input::mouseMove;

Input::Input(void)
{
}


Input::~Input(void)
{
}

void Input::update()
{
	Vec2 oldMouse = mousePos;
	
	mousePos.x = agk::GetPointerX();
	mousePos.y = agk::GetPointerY();

	//mouseMove.x = mousePos.x - oldMouse.x;
	//mouseMove.y = mousePos.y - oldMouse.y;

	mouseMove.x = agk::GetPointerX() - agk::GetVirtualWidth() / 2;
	mouseMove.y = agk::GetPointerY() - agk::GetVirtualHeight() / 2;

	agk::SetRawMousePosition(agk::GetVirtualWidth() / 2, agk::GetVirtualHeight() / 2);
}