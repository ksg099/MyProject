#pragma once
#include "SpriteGo.h"

class BgMovingGo : public SpriteGo
{
protected:

public:
	BgMovingGo(const std::string& name = "");

	void Update(float dt) override;
	
	void Reset() override;
	void Reposition();

	sf::FloatRect bounds = { 0.f, 0.f, 1920.f, 1080.f };
	sf::Vector2f direction = { 1.0f, 0.f };
	float speed = 100.f;

	float speedMin = 100.f;
	float speedMax = 200.f;

	float scaleMin = 0.5f;
	float scaleMax = 1.5f;
};

