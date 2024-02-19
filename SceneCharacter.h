#pragma once
#include "Scene.h"
class SceneCharacter : public Scene
{
protected:
	sf::Sprite player1;
	sf::Sprite player2;

	sf::Text num1;
	sf::Text num2;

	
	bool player1choice = false;
	bool player2choice = false;



public:
	SceneCharacter(SceneIds id);
	virtual ~SceneCharacter() = default;

	void Init() override;
	void Release()override;

	void Reset()

	void Enter()override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

