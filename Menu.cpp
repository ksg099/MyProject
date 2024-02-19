#include "pch.h"
#include "Menu.h"
#include "TextGo.h"
#include "SpriteGo.h"

Menu::Menu(SceneIds id) : Scene(id)
{
}

void Menu::Init()
{

	RES_MGR_TEXTURE.Load("graphics/background.png");
	RES_MGR_FONT.Load("graphics/background.png");


	//배경 출력하기
	SpriteGo* background = new SpriteGo("BG");
	background->SetPosition({0.f, 0.f});
	background->SetTexture("graphics/background.png");


	//1번 눌렀을때 문자 출력
	Single = new TextGo("text");
	Single->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Single Play to PRESS 1", 75, sf::Color::Red);
	Single->SetPosition({ 1920.f / 2, 400.f });
	Single->SetOrigin(Origins::MC);

	//2번 눌렀을때 문자 출력
	Multi = new TextGo("text");
	Multi->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Multi Play to PRESS 2", 75, sf::Color::Blue);
	Multi->SetPosition({ 1920.f / 2, 600.f });
	Multi->SetOrigin(Origins::MC);

	AddGo(background);
	AddGo(Single);
	AddGo(Multi);

}

void Menu::Release()
{
}

void Menu::Enter()
{
}

void Menu::Exit()
{
}

void Menu::Update(float dt) //초기상태시
{
    // 위쪽 화살표 키를 눌렀을 때
    if (InputMgr::GetKeyDown(sf::Keyboard::Up))
    {
        // 플레이어 모드를 Single로 설정
        SCENE_MGR.playMode = GameMode::Single;
    }

    // 아래쪽 화살표 키를 눌렀을 때
    if (InputMgr::GetKeyDown(sf::Keyboard::Down))
    {
        // 플레이어 모드를 Multi로 설정
        SCENE_MGR.playMode = GameMode::Multi;
    }

    // Enter 키를 눌렀을 때 다음 씬으로 넘어감
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        SCENE_MGR.ChangeScene(SceneIds::SCENE_CHARACTER);
    }

    // Escape 키를 눌렀을 때 타이틀 씬으로 돌아감
    if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
    {
        SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
    }

    // 플레이어 모드에 따라 텍스트 색상 변경
    if (SCENE_MGR.playMode == GameMode::Single)
    {
        Single->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Multi Play to PRESS 1", 80, sf::Color::White);
        Multi->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Multi Play to PRESS 2", 75, sf::Color::Red);

    }
    else if (SCENE_MGR.playMode == GameMode::Multi)
    {
        Single->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Multi Play to PRESS 1", 75, sf::Color::Red);;
        Multi->Set(RES_MGR_FONT.Get("fonts/KOMIKAP_.ttf"), "Multi Play to PRESS 2", 80, sf::Color::White);
    }

	//Esc누르면 타이틀 화면으로 이동
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F5))
	{
		SCENE_MGR.ChangeScene(SceneIds::SCENE_TITLE);
	}
}

