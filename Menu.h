#pragma once
#include "Scene.h"
#include "TextGo.h"
class Menu : public Scene
{
protected:

	TextGo* Single;
	TextGo* Multi;

public:

	Menu(SceneIds id);
	virtual ~Menu() = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;


};

