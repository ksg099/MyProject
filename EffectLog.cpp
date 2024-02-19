#include "pch.h"
#include "EffectLog.h"

EffectLog::EffectLog(const std::string& name)
	: SpriteGo(name)
{
}

void EffectLog::Fire(const sf::Vector2f v)
{
	velocity = v;
	timer = 0.f;
}

void EffectLog::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		return;
	}

	velocity += gravity * dt;
	SetPosition(position + velocity * dt);
}
