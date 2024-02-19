#include "pch.h"
#include "SceneCharacter.h"

SceneCharacter::SceneCharacter(SceneIds id)
	:Scene(id)
{
}

void SceneCharacter::Init()
{
	texResMgr.Load("graphics/player.png");
	texResMgr.Load("graphics/player3.png");


	fontResMgr.Load("fonts/KOMIKAP_.ttf");

	player1.setTexture(texResMgr.Get("graphics/player.png"));
	player1.setPosition({ 1920 / 2 - 300, 1080 / 2 });
	player1.setColor(sf::Color::White);

	player2.setTexture(texResMgr.Get("graphics/player3.png"));
	player2.setScale(1.1f, 1.1f);
	player2.setPosition({ 1920 / 2 + 300, 1080 / 2 });
	player2.setColor(sf::Color::White);

	num1.setFont(fontResMgr.Get("fonts/KOMIKAP_.ttf"));
	num1.setString("Left");
	num1.setCharacterSize(24);
	num1.setFillColor(sf::Color::White);
	num1.setPosition({ 1920 / 2 - 260, 740 });


	num2.setFont(fontResMgr.Get("fonts/KOMIKAP_.ttf"));
	num2.setString("Right");
	num2.setCharacterSize(24);
	num2.setFillColor(sf::Color::White);
	num2.setPosition({ 1920 / 2 + 370, 740 });

}

void SceneCharacter::Release()
{
}

void SceneCharacter::Enter()
{
	player1choice = false;
	player2choice = false;
}

void SceneCharacter::Exit()
{

}

void SceneCharacter::Update(float dt)
{
	if (SCENE_MGR.playMode == GameMode::Single)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			SCENE_MGR.player1 = "graphics/player.png";
			player1.setColor(sf::Color::Black);

			SCENE_MGR.player1 = "graphics/player3.png";
			player2.setColor(sf::Color::White);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			SCENE_MGR.player2 = "graphics/player.png";
			player1.setColor(sf::Color::White);

			SCENE_MGR.player2 = "graphics/player3.png";
			player2.setColor(sf::Color::Black);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_MENU);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_GAME);
		}
	}
	if (SCENE_MGR.playMode == GameMode::Multi)  //미완
	{
		//왼쪽을 선택했을때
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{

			SCENE_MGR.player1 = "graphics/player.png";
			player1.setColor(sf::Color::Yellow);

			SCENE_MGR.player1 = "graphics/player3.png";
			player2.setColor(sf::Color::White);

			player1choice = true;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			SCENE_MGR.player1 = "graphics/player.png";
			player1.setColor(sf::Color::White);

			SCENE_MGR.player1 = "graphics/player3.png";
			player2.setColor(sf::Color::Yellow);

			player1choice = true;

		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			SCENE_MGR.player2 = "graphics/player.png";
			player2.setColor(sf::Color::Black);

			SCENE_MGR.player1 = "graphics/player3.png";
			player2.setColor(sf::Color::White);
			
			player2choice = true;
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			SCENE_MGR.player2 = "graphics/player3.png";
			player1.setColor(sf::Color::Black);

			SCENE_MGR.player2 = "graphics/player1.png";
			player2.setColor(sf::Color::White);
			
			player2choice = true;
		}

		if (player1choice && player2choice)
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_GAME_2);
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
		{
			SCENE_MGR.ChangeScene(SceneIds::SCENE_MENU);
		}
	}

}

void SceneCharacter::Draw(sf::RenderWindow& window)
{
	
	window.draw(player1);
	window.draw(player2);
	window.draw(num1);
	window.draw(num2);
	
}
