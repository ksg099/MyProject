#include "pch.h"
#include "SceneGame.h"
#include "SpriteGo.h"
#include "BgMovingGo.h"
#include "BgBeeGo.h"
#include "UiScore.h"
#include "UiTimeBar.h"
#include "Tree.h"
#include "EffectLog.h"
#include "Player.h"

SCENE_GAME::SCENE_GAME(SceneIds id, GameMode gameMode)
	: Scene(id), currGameMode(gameMode), currStatus(Status::Awake)
{
}

SCENE_GAME::~SCENE_GAME()
{
}

void SCENE_GAME::Init()
{
	texResMgr.Load("graphics/background.png");
	texResMgr.Load("graphics/cloud.png");
	texResMgr.Load("graphics/bee.png");
	texResMgr.Load("graphics/tree2.png");
	texResMgr.Load("graphics/branch.png");
	texResMgr.Load("graphics/log.png");
	texResMgr.Load("graphics/player.png");
	texResMgr.Load("graphics/axe.png");
	texResMgr.Load("graphics/rip.png");

	fontResMgr.Load("fonts/KOMIKAP_.ttf");

	soundResMgr.Load("sound/out_of_time.wav");
	sfxTimeOver.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/out_of_time.wav"));
	sfxTimeOver.setVolume(30.f);

	SpriteGo* newSpriteGo = new SpriteGo("BG");
	newSpriteGo->SetTexture("graphics/background.png");
	AddGo(newSpriteGo);

	sf::FloatRect movingBounds({ -200.f, 0.f }, { 1920.f + 400.f, 600.f });

	for (int i = 0; i < 3; ++i)
	{
		BgMovingGo* newMovingGo = new BgMovingGo(std::string("Cloud") + std::to_string(i));
		newMovingGo->SetTexture("graphics/cloud.png");
		newMovingGo->SetOrigin(Origins::MC);
		newMovingGo->SetFlipX(true);
		newMovingGo->bounds = movingBounds;
		AddGo(newMovingGo);
	}

	tree = new Tree("Tree");
	tree->SetPosition({ 1920.f / 2, 900.f });
	AddGo(tree);

	player = new Player("Player", currGameMode, this);
	AddGo(player);

	BgBeeGo* beeGo = new BgBeeGo("Bee");
	beeGo->SetTexture(texResMgr.Get("graphics/bee.png"));
	beeGo->SetOrigin(Origins::MC);
	beeGo->SetPosition({ 1920.f / 2, 1080.f / 2 });
	AddGo(beeGo);

	sf::Vector2f uiTimeBarPos = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	uiTimeBarPos.x *= 0.5f;
	uiTimeBarPos.x -= 200.f;
	uiTimeBarPos.y *= 0.9f;

	// UI OBJECTS
	uiScore = new UiScore("Ui Score");
	uiScore->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"), "", 40, sf::Color::White);
	AddGo(uiScore);

	uiTimeBar = new UiTimeBar("TimeBar");
	uiTimeBar->Set({ 400, 80 }, sf::Color::Red);
	uiTimeBar->SetOrigin(Origins::ML);
	uiTimeBar->SetPosition(uiTimeBarPos);

	AddGo(uiTimeBar);

	uiMsg = new TextGo("Center Message");
	uiMsg->Set(fontResMgr.Get("fonts/KOMIKAP_.ttf"),
		"", 75, sf::Color::White);
	uiMsg->SetPosition({ 1920.f / 2, 1080.f / 2 });
	uiMsg->SetOrigin(Origins::MC);
	uiMsg->SetDrawLayer(5);
	AddGo(uiMsg);

	for (GameObject* obj : gameObjects)
	{
		obj->Init();
	}
}

void SCENE_GAME::Release() //
{
	Scene::Release();

	uiScore = nullptr;
	uiMsg = nullptr;
}

void SCENE_GAME::Reset() //
{
	for (auto& i : gameObjects)
	{
		i->Reset();
	}
	uiMsg->SetString("");
	while (!useEffectList.empty())
	{
		useEffectList.front()->SetActive(false);
		RemoveGo(useEffectList.front());
		unuseEffectList.push_back(useEffectList.front());
		useEffectList.pop_front();
	}
}

void SCENE_GAME::Enter()
{
	player->SetPosition(tree->GetPosition());

	Scene::Enter();
	Reset();

	SetStatus(Status::Awake);
}

void SCENE_GAME::Exit()
{
	timeScale = 1.f;
}

void SCENE_GAME::Update(float dt)
{
	Scene::Update(dt);

	switch (currStatus)
	{
	case Status::Awake:
		UpdateAwake(dt);
		break;
	case Status::Game:
		UpdateGame(dt);
		break;
	case Status::GameOver:
		UpdateGameOver(dt);
		break;
	case Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SCENE_GAME::UpdateAwake(float dt)
{
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
	}
}

void SCENE_GAME::UpdateGame(float dt)
{
	//1인 모드에서 일시정지
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
	}

	timer -= dt;
	uiTimeBar->SetValue(timer / duration);
	if (uiTimeBar->GetValue() <= 0.f)
	{
		SetStatus(Status::GameOver);
		player->OnDie();
		//sfxTimeOver.play();
		return;
	}

	auto it = useEffectList.begin();
	while (it != useEffectList.end())
	{
		EffectLog* effectGo = *it;
		if (!effectGo->GetActive())
		{
			RemoveGo(effectGo);
			it = useEffectList.erase(it);
			unuseEffectList.push_back(effectGo);
		}
		else
		{
			++it;
		}
	}
}

void SCENE_GAME::UpdateGameOver(float dt)
{
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		Reset();
		SetStatus(Status::Game);
	}
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
	}
}

void SCENE_GAME::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
	if (currGameMode == GameMode::Single && InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
	}
}


void SCENE_GAME::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SCENE_GAME::OnChop()
{
	uiScore->AddScore(10);
	timer += 0.2f;
	if (timer > duration)
		timer = duration;
}

void SCENE_GAME::OnPlayerDie()
{
	SetStatus(Status::GameOver);
}

void SCENE_GAME::SetStatus(Status newStatus)
{
	Status prevStatus = currStatus;
	currStatus = newStatus;

	switch (currStatus)
	{
	case Status::Awake:
		timer = duration;
		uiTimeBar->SetValue(timer / duration);

		if (currGameMode == GameMode::Single)
		{
			timeScale = 0.f;
			uiMsg->SetActive(true);
			uiMsg->SetString("PRESS ENTER TO START!");
		}
		else
		{
			timeScale = 0.f;
		}
		break;
	case Status::Game:
		if (prevStatus == Status::GameOver)
		{
			timer = duration;
			uiTimeBar->SetValue(timer / duration);
		}
			timeScale = 1.f;
			uiMsg->SetActive(false);
			uiMsg->SetString("");
		break;
	case Status::GameOver:
		if (currGameMode == GameMode::Single)
		{
			timeScale = 0.f;
			uiMsg->SetActive(true);
			uiMsg->SetString("\t\t\t\tSCORE : " + std::to_string(uiScore->GetScore()) + "\n\n\nGAME OVER! PRESS ENTER TO RESTART!");
		}
		else
		{
			uiMsg->SetActive(true);
			uiMsg->SetString("\t\tSCORE : " + std::to_string(uiScore->GetScore()) + "\n\n\n\t\tGAME OVER!\nWAIT FOR ANOTHER PLAYER");

		}
		break;
	case Status::Pause:
		if (currGameMode == GameMode::Single)
		{
			timeScale = 0.f;
			uiMsg->SetActive(true);
			uiMsg->SetString("PRESS ESC TO RESUME!");
		}
		break;
	}
}

void SCENE_GAME::PlayEffectLog(Sides side)
{
	EffectLog* effectLog = nullptr;
	if (unuseEffectList.empty())
	{
		effectLog = new EffectLog();
		effectLog->SetTexture("graphics/log.png");
		effectLog->SetOrigin(Origins::BC);
		effectLog->Init();
	}
	else
	{
		effectLog = unuseEffectList.front();
		unuseEffectList.pop_front();
	}

	effectLog->SetActive(true);
	effectLog->Reset();
	effectLog->SetPosition(tree->GetPosition());

	sf::Vector2f velocity(1000.f, -1000.f);
	if (side == Sides::RIGHT)
	{
		velocity.x *= -1.f;
	}
	effectLog->Fire(velocity);

	useEffectList.push_back(effectLog);
	AddGo(effectLog);
}
