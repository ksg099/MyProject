#pragma once
#include "SpriteGo.h"
#include "SceneGame.h"

class Tree;

class Player : public SpriteGo
{
protected:
	sf::Sound sfxChop;
	sf::Sound sfxDeath;

	sf::Sprite spriteAxe;
	sf::Vector2f axeLocalPosition = { -60, -60 };

	Sides playerSide = Sides::RIGHT;
	Sides axeSide = Sides::LEFT;

	Sides side = Sides::RIGHT;
	float offsetPositionX = 300.f;
	bool isAlive = true;
	bool isChopping = true;

	SCENE_GAME* sceneGame;
	GameMode gameMode;
	Tree* tree;

public:
	Player(const std::string& name, GameMode gameMode, SCENE_GAME* sceneGame);
	virtual ~Player() = default;

	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";
	
	bool IsAlive() const { return isAlive; }
	Sides GetSide() const { return side; }
	void SetSide(Sides s);
	void OnDie();

	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void SetScale(const sf::Vector2f& scale);

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	sf::Keyboard::Key KeyLeft() const;
	sf::Keyboard::Key KeyRight() const;
};

