#pragma once
#include "SceneGame.h"
#include "uiStartTimer.h"

class SceneGameMulti : public Scene
{
protected:
	SCENE_GAME* scenePlayer1 = nullptr;
	SCENE_GAME* scenePlayer2 = nullptr;
	sf::View* viewPlayer1 = nullptr;
	sf::View* viewPlayer2 = nullptr;
	sf::View* viewReset = nullptr;

	uiStartTimer* startTimer = nullptr;
	TextGo* uiWinner = nullptr;
	sf::RectangleShape uiWinnerBack;

	SCENE_GAME::Status currStatus = SCENE_GAME::Status::Awake;

public:
	SceneGameMulti(SceneIds id);
	virtual ~SceneGameMulti() = default;
	SceneGameMulti(const SceneGameMulti&) = delete;
	SceneGameMulti(SceneGameMulti&&) = delete;
	SceneGameMulti& operator=(const SceneGameMulti&) = delete;
	SceneGameMulti& operator=(SceneGameMulti&&) = delete;
	
	void Init() override;
	void Release() override;
	void Reset();

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	Scene* GetScenePlayer1() { return scenePlayer1; }
	Scene* GetScenePlayer2() { return scenePlayer2; }
};