#pragma once
#include "GameObject.h"

class Branch;

class Tree : public GameObject
{
protected:
	sf::Sprite tree;
	std::list<Branch*> branches;

public:
	Tree(const std::string& name = "");
	virtual ~Tree();

	int branchCount = 6;
	std::string treeTexureId = "graphics/tree2.png";
	std::string branchTextureId = "graphics/branch.png";
	float branchOffsetY = 150.f;

	static Sides RandomSide(int range = 4);

	Sides Chop(Sides side);
	void UpdateBranchPos();

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetPosition(const sf::Vector2f& pos)  override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

