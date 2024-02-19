#pragma once
#include "SpriteGo.h"

class EffectLog : public SpriteGo
{
protected:
	sf::Vector2f gravity = { 0.f, 1000.f };
	sf::Vector2f velocity;

public:
	EffectLog(const std::string& name = "");
	virtual ~EffectLog() = default;

	float duration = 3.f;
	float timer = 0.f;

	void Fire(const sf::Vector2f v);
	void Update(float dt) override;
};

