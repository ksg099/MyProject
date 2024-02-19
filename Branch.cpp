#include "pch.h"
#include "Branch.h"

Branch::Branch(const std::string& name)
	: SpriteGo(name)
{
}

void Branch::Reset()
{
	SetSide(Sides::NONE);
}

void Branch::SetSide(Sides side)
{
	this->side = side;
	switch (this->side)
	{
	case Sides::LEFT:
	case Sides::RIGHT:
		SetActive(true);
		SetFlipX(originalDir != side);
		break;
	default:
		SetActive(false);
		break;
	}

}
