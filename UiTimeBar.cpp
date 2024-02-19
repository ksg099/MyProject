#include "pch.h"
#include "UiTimeBar.h"


UiTimeBar::UiTimeBar(const std::string& name)
	: GameObject(name)
{
	drawLayer = 5;
}

void UiTimeBar::Reset()
{
	SetValue(1.f);
}

void UiTimeBar::SetPosition(const sf::Vector2f& pos)
{
	//GameObject::SetPosition(pos);
	position = pos;
	shape.setPosition(pos);
}

void UiTimeBar::SetOrigin(Origins preset)
{
	if (preset == Origins::CUSTOM)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(shape, originPreset);
}

void UiTimeBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::CUSTOM;
	origin = newOrigin;
	shape.setOrigin(newOrigin);
}

void UiTimeBar::SetScale(const sf::Vector2f& s)
{
	sf::Vector2f shapeScale = scale = s;
	if (isFlipX)
	{
		shapeScale.x = -scale.x;
	}
	if (isFlipY)
	{
		shapeScale.y = -scale.y;
	}
	shape.setScale(shapeScale);
}

void UiTimeBar::SetFlipX(bool filp)
{
	if (isFlipX == filp)
		return;

	isFlipX = filp;
	SetScale(scale);
}

void UiTimeBar::SetFlipY(bool filp)
{
	if (isFlipY == filp)
		return;

	isFlipY = filp;
	SetScale(scale);
}

void UiTimeBar::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void UiTimeBar::Set(const sf::Vector2f& max, const sf::Color& color)
{
	shape.setFillColor(color);
	currentSize = maxSize = max;
	shape.setSize(currentSize);
	SetOrigin(originPreset);
}

void UiTimeBar::SetValue(float value)
{
	if (value < 0.f)
	{
		value = 0.f;
	}
	if (value > 1.f)
	{
		value = 1.f;
	}
	currentSize.x = maxSize.x * value;
	shape.setSize(currentSize);
	SetOrigin(originPreset);
}
