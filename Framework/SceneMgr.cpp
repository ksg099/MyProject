#include "pch.h"
#include "SceneMgr.h"


#include "Title.h"
#include "Menu.h"
#include "SceneGame.h"
#include "SceneCharacter.h"
#include "SceneGameMulti.h"

SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Init()
{
	Release();

	scenes.insert(std::make_pair(SceneIds::SCENE_TITLE, new Title(SceneIds::SCENE_TITLE)));
	scenes.insert(std::make_pair(SceneIds::SCENE_MENU, new Menu(SceneIds::SCENE_MENU)));
	scenes.insert(std::make_pair(SceneIds::SCENE_CHARACTER, new SceneCharacter(SceneIds::SCENE_CHARACTER)));
	scenes.insert(std::make_pair(SceneIds::SCENE_GAME, new SCENE_GAME(SceneIds::SCENE_GAME, GameMode::Single)));
	scenes.insert(std::make_pair(SceneIds::SCENE_GAME_2, new SceneGameMulti(SceneIds::SCENE_GAME_2)));

	for (auto& scene : scenes)
	{
		scene.second->Init();
	}

	currentScene = startScene;
	scenes[currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto& scene : scenes)
	{
		scene.second->Release();
		delete scene.second;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	doSceneChange = true;
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	scenes[currentScene]->Update(dt);

	if (doSceneChange)
	{
		doSceneChange = false;
		scenes[currentScene]->Exit();
		currentScene = nextScene;
		scenes[currentScene]->Enter();
	}
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[currentScene]->Draw(window);
}
