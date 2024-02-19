#pragma once
#include "SpriteGo.h"

class Branch : public SpriteGo
{
protected:
	Sides originalDir = Sides::RIGHT;
	Sides side = Sides::NONE;

public:
	Branch(const std::string& name = "");
	virtual ~Branch() = default;

	void Reset() override;

	void SetSide(Sides side);
	Sides GetSide() const { return side; }
};

