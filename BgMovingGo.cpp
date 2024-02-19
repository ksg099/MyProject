#include "pch.h"
#include "BgMovingGo.h"

BgMovingGo::BgMovingGo(const std::string& name)
	: SpriteGo(name)
{
}

void BgMovingGo::Reset()
{
	speed = Utils::RandomRange(speedMin, speedMax);
	direction.x = Utils::RandomValue() > 0.5f ? 1.f : -1.f;

	float rand = Utils::RandomRange(scaleMin, scaleMax);
	sf::Vector2f newScale(rand, rand);
	newScale.x = abs(newScale.x);
	if (direction.x < 0)
	{
		newScale.x = -newScale.x;
	}
	SetScale(newScale);

	sf::Vector2f newPos;
	newPos.x = Utils::RandomRange(bounds.left, bounds.left + bounds.width);
	newPos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);

	SetPosition(newPos);
}

void BgMovingGo::Reposition()
{
	speed = Utils::RandomRange(speedMin, speedMax);
	sf::Vector2f newPos;

	if (Utils::RandomValue() > 0.5f)
	{
		direction.x = 1.f;
		newPos.x = bounds.left;
	}
	else
	{
		direction.x = -1.f;
		newPos.x = bounds.left + bounds.width;
	}
	newPos.y = Utils::RandomRange(bounds.top, bounds.top + bounds.height);

	float rand = Utils::RandomRange(scaleMin, scaleMax);
	sf::Vector2f newScale(rand, rand);
	newScale.x = abs(newScale.x);
	if (direction.x < 0)
	{
		newScale.x = -newScale.x;
	}

	SetScale(newScale);

	SetPosition(newPos);
}

void BgMovingGo::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (position.x < bounds.left  || position.x > bounds.left + bounds.width)
	{
		Reposition();
	}
}
