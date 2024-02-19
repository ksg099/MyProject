#include "pch.h"
#include "SceneGameMulti.h"
#include "UiScore.h"

SceneGameMulti::SceneGameMulti(SceneIds id)
	:Scene(id),
	scenePlayer1(new SCENE_GAME(SceneIds::SCENE_GAME, GameMode::Player1)),
	scenePlayer2(new SCENE_GAME(SceneIds::SCENE_GAME, GameMode::Player2))
{
	float windowSizeX = Framework::Instance().GetWindowSize().x;
	float windowSizeY = Framework::Instance().GetWindowSize().y;

	viewPlayer1 = new sf::View({ windowSizeX * 0.5f,windowSizeY * 0.5f }, { windowSizeX * 0.495f,windowSizeY });
	viewPlayer1->setViewport({ 0.f, 0.f, 0.495f, 1.f });

	viewPlayer2 = new sf::View({ windowSizeX * 0.5f,windowSizeY * 0.5f }, { windowSizeX * 0.495f,windowSizeY });
	viewPlayer2->setViewport({ 0.505f, 0.f, 0.495f, 1.f });

	viewReset = new sf::View({ windowSizeX * 0.5f,windowSizeY * 0.5f }, { windowSizeX, windowSizeY });
	viewReset->setViewport({ 0.f, 0.f, 1.f, 1.f });
}

void SceneGameMulti::Init()
{
	scenePlayer1->Init();
	scenePlayer2->Init();



	startTimer = new uiStartTimer();
	startTimer->SetFont("fonts/KOMIKAP_.ttf");
	AddGo(startTimer);

	uiWinner = new TextGo("winner");
	uiWinner->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 80, sf::Color::Cyan);
	uiWinner->SetPosition({ 960.f, 540.f });
	AddGo(uiWinner);
	uiWinnerBack.setFillColor(sf::Color::Black);
	uiWinnerBack.setPosition(uiWinner->GetPosition().x, uiWinner->GetPosition().y+15.f);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
	uiWinner->SetActive(false);
}

void SceneGameMulti::Release()
{
	scenePlayer1->Release();
	scenePlayer2->Release();
	Scene::Release();
}

void SceneGameMulti::Reset()
{
	for (auto& i : gameObjects)
	{
		i->Reset();
	}
	uiWinner->SetActive(false);
	startTimer->Reset();
	startTimer->SetActive(true);
	scenePlayer1->Reset();
	scenePlayer2->Reset();
	currStatus = SCENE_GAME::Status::Awake;
}

void SceneGameMulti::Enter()
{
	Scene::Enter();
	scenePlayer1->Enter();
	scenePlayer2->Enter();
	Reset();
}

void SceneGameMulti::Exit()
{
	scenePlayer1->Exit();
	scenePlayer2->Exit();
}

void SceneGameMulti::Update(float dt)
{
	scenePlayer2->Update(dt);
	scenePlayer1->Update(dt);
	Scene::Update(dt);

	switch (currStatus)
	{
	case SCENE_GAME::Status::Awake:
		if (!startTimer->GetActive())
		{
			scenePlayer1->SetStatus(SCENE_GAME::Status::Game);
			scenePlayer2->SetStatus(SCENE_GAME::Status::Game);
			currStatus = SCENE_GAME::Status::Game;
		}
		break;
	case SCENE_GAME::Status::Game:
		if (scenePlayer1->GetStatus() == SCENE_GAME::Status::GameOver && scenePlayer2->GetStatus() == SCENE_GAME::Status::GameOver)
		{
			currStatus = SCENE_GAME::Status::GameOver;
		}
		break;
	case SCENE_GAME::Status::GameOver:
		uiWinner->SetActive(true);
		if (dynamic_cast<UiScore*>(scenePlayer1->FindGo("Ui Score"))->GetScore() == dynamic_cast<UiScore*>(scenePlayer2->FindGo("Ui Score"))->GetScore())
		{
			uiWinner->SetString("\t\t\tDraw!\nPress ENTER to restart");
			uiWinner->SetOrigin(Origins::MC);
			uiWinnerBack.setSize(uiWinner->GetRect().getSize()*1.08f);
			Utils::SetOrigin(uiWinnerBack, Origins::MC);
		}
		else if (dynamic_cast<UiScore*>(scenePlayer1->FindGo("Ui Score"))->GetScore() > dynamic_cast<UiScore*>(scenePlayer2->FindGo("Ui Score"))->GetScore())
		{
			uiWinner->SetString("Winner!\nPress ENTER to restart");
			uiWinner->SetOrigin(Origins::MC);
			uiWinnerBack.setSize(uiWinner->GetRect().getSize() * 1.08f);
			Utils::SetOrigin(uiWinnerBack, Origins::MC);
		}
		else
		{
			uiWinner->SetString("\t\t\t\t\tWinner!\nPress ENTER to restart");
			uiWinner->SetOrigin(Origins::MC);
			uiWinnerBack.setSize(uiWinner->GetRect().getSize() * 1.08f);
			Utils::SetOrigin(uiWinnerBack, Origins::MC);
		}
		scenePlayer1->SetTimeScale(0.f);
		scenePlayer2->SetTimeScale(0.f);
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			Reset();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::F5))
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
		}
		break;
	case SCENE_GAME::Status::Pause:
		if (InputMgr::GetKeyDown(sf::Keyboard::F5))
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
		}
		break;
	default:
		break;
	}


}

void SceneGameMulti::Draw(sf::RenderWindow& window)
{
	window.setView(*viewPlayer1);
	scenePlayer1->Draw(window);

	window.setView(*viewPlayer2);
	scenePlayer2->Draw(window);

	window.setView(*viewReset);
	if(currStatus == SCENE_GAME::Status::GameOver)
		window.draw(uiWinnerBack);
	Scene::Draw(window);
}
