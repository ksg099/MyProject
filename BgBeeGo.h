#pragma once
#include "SpriteGo.h"

class BgBeeGo : public SpriteGo
{
protected:
	float timer = 0.f;
	sf::Vector2f direction;

public:
	BgBeeGo(const std::string& name = "");

	void Reset();
	void ReDirection();

	void Update(float dt) override;

	float duration = 1.f;
	float speed = 100.f;
};

