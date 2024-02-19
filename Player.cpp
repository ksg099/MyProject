#include "pch.h"
#include "Player.h"
#include "SceneGame.h"
#include "SceneGameMulti.h"
#include "Tree.h"

Player::Player(const std::string& name, GameMode gameMode, SCENE_GAME* sceneGame)
	: SpriteGo(name) , gameMode(gameMode), sceneGame(sceneGame)
{
	sfxChop.setVolume(50.f);
	sfxDeath.setVolume(30.f);
}

void Player::SetSide(Sides s)
{
	side = s;
	SetScale(scale);
	SetPosition(position);
}

void Player::OnDie()
{
	isAlive = false;
	isChopping = false;

	SetTexture(texIdRip);
	SetOrigin(Origins::BC);
	SetScale(scale);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sf::Vector2f spritePos = position;
	switch (side)
	{
	case Sides::LEFT:
		spritePos.x -= offsetPositionX;
		break;
	case Sides::RIGHT:
		spritePos.x += offsetPositionX;
		break;
	}
	sprite.setPosition(spritePos);
	sf::Vector2f axePos = spritePos;
	switch (side)
	{
	case Sides::LEFT:
		axePos.x -= axeLocalPosition.x;
		axePos.y += axeLocalPosition.y;
		break;
	case Sides::RIGHT:
		axePos.x += axeLocalPosition.x;
		axePos.y += axeLocalPosition.y;
		break;
	}
	spriteAxe.setPosition(axePos);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sf::Vector2f playerScale = scale;
	sf::Vector2f axeScale = scale;

	bool playerFilpX = playerSide != side;
	bool axeFilpX = axeSide != side;

	if (playerFilpX)
	{
		playerScale.x = -scale.x;
	}
	if (axeFilpX)
	{
		axeScale.x = -scale.x;
	}

	if (isFlipY)
	{
		playerScale.y = -scale.y;
		axeScale.y = -scale.y;
	}

	if (isAlive)
	{
		sprite.setScale(playerScale);
	}
	else
	{
		sprite.setScale(scale);
	}
	spriteAxe.setScale(axeScale);
}


void Player::Init()
{
	RES_MGR_SOUND_BUFFER.Load("sound/chop.wav");
	RES_MGR_SOUND_BUFFER.Load("sound/death.wav");

	SpriteGo::Init();
	SetTexture(texIdPlayer);
	spriteAxe.setTexture(ResourceMgr<sf::Texture>::Instance().Get(texIdAxe));

	SetOrigin(Origins::BC);
	Utils::SetOrigin(spriteAxe, Origins::ML);

	sfxChop.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/chop.wav"));
	sfxDeath.setBuffer(RES_MGR_SOUND_BUFFER.Get("sound/death.wav"));

}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	if (gameMode == GameMode::Player2)
	{
		texIdPlayer = SCENE_MGR.player2;
	}
	else
	{
		texIdPlayer = SCENE_MGR.player1;
	}
	SetTexture(texIdPlayer);
	SetOrigin(Origins::BC);
	isAlive = true;
	isChopping = false;

	if (gameMode == GameMode::Single)
	{
		sceneGame = dynamic_cast<SCENE_GAME*>(SCENE_MGR.GetCurrentScene());
	}
	else if (gameMode == GameMode::Player1)
	{
		sceneGame = dynamic_cast<SCENE_GAME*>(dynamic_cast<SceneGameMulti*>(SCENE_MGR.GetCurrentScene())->GetScenePlayer1());
	}
	else
	{
		sceneGame = dynamic_cast<SCENE_GAME*>(dynamic_cast<SceneGameMulti*>(SCENE_MGR.GetCurrentScene())->GetScenePlayer2());
	}
	tree = dynamic_cast<Tree*>(sceneGame->FindGo("Tree"));

	SetSide(Sides::RIGHT);
}

void Player::Update(float dt)
{
	if (sceneGame->GetStatus() != SCENE_GAME::Status::Game)
		return;

	Sides inputSide = Sides::NONE;

	if (InputMgr::GetKeyDown(KeyLeft()))
	{
		inputSide = Sides::LEFT;
	}
	if (InputMgr::GetKeyDown(KeyRight()))
	{
		inputSide = Sides::RIGHT;
	}

	if (inputSide != Sides::NONE)
	{
		isChopping = true;
		//sfxChop.play();

		Sides branchSide = tree->Chop(inputSide);
		sceneGame->PlayEffectLog(inputSide);
		SetSide(inputSide);

		if (side != branchSide)
		{
			sceneGame->OnChop();
		}
		else
		{
			sceneGame->OnPlayerDie();
			OnDie();
			//sfxDeath.play();
		}
	}

	if (InputMgr::GetKeyUp(KeyLeft()) || InputMgr::GetKeyUp(KeyRight()))
	{
		isChopping = false;
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	if (isChopping)
	{
		window.draw(spriteAxe);
	}
}

sf::Keyboard::Key Player::KeyLeft() const
{
	return gameMode == GameMode::Player1 ? sf::Keyboard::A : sf::Keyboard::Left;
}

sf::Keyboard::Key Player::KeyRight() const
{
	return gameMode == GameMode::Player1 ? sf::Keyboard::D : sf::Keyboard::Right;
}
