#pragma once
#include "Scene.h"

class UiScore;
class TextGo;
class UiTimeBar;
class Tree;
class EffectLog;
class Player;

class SCENE_GAME : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	UiScore* uiScore = nullptr;
	TextGo* uiMsg = nullptr;
	UiTimeBar* uiTimeBar = nullptr;

	Tree* tree = nullptr;
	Player* player = nullptr;
	std::list<EffectLog*> useEffectList;
	std::list<EffectLog*> unuseEffectList;

	Status currStatus;
	GameMode currGameMode;

	float duration = 3.f;
	float timer = 0.f;

	sf::Sound sfxTimeOver;

public:
	SCENE_GAME(SceneIds id, GameMode gameMode);
	virtual ~SCENE_GAME();

	void SetStatus(Status newStatus);
	Status GetStatus() const { return currStatus; }
	GameMode GetGameMode() const { return currGameMode; }

	void PlayEffectLog(Sides side);

	void Init() override;
	void Release() override;
	void Reset();

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void OnChop();
	void OnPlayerDie();

};

