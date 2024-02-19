#pragma once
#include "Scene.h"
#include "TextGo.h"
//배경 텍스처를 출력할 다른 방법이 없나?  스프라이트로 받자

class Title : public Scene
{
protected:
	TextGo* Titletext;
	TextGo* textcomt;
	//sf::Sprite player2

public:

	Title(SceneIds id);
	virtual ~Title() = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};

