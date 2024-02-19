#include "pch.h"
#include "uiStartTimer.h"

uiStartTimer::uiStartTimer(const std::string& name)
	:TextGo(name)
{
	duration = 3.f;
	timer = duration;
	ceilSecond = ceil(timer);
	drawLayer = 5;
}

void uiStartTimer::Init()
{
	text.setCharacterSize(600);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(5.f);
	text.setOutlineColor(sf::Color::White);

	Reset();
}

void uiStartTimer::Update(float dt)
{
	TextGo::Update(dt);
	timer -= dt;
	ceilSecond = ceil(timer);

	SetString(std::to_string(ceilSecond));
	SetOrigin(Origins::MC);

	if (timer <= 0.f)
		SetActive(false);

}

void uiStartTimer::Draw(sf::RenderWindow& window)
{
	TextGo::Draw(window);

}

void uiStartTimer::Reset()
{
	timer = duration;
	ceilSecond = ceil(timer);
	SetString(std::to_string(ceilSecond));
	SetOrigin(Origins::MC);
	SetPosition({ 960, 540 });
}
