#include "pch.h"
#include "Tree.h"
#include "Branch.h"

Tree::Tree(const std::string& name)
	: GameObject(name)
{
}

Tree::~Tree()
{
	Release();
}

Sides Tree::RandomSide(int range)
{
	Sides side = Sides::NONE;
	int rand = Utils::RandomRange(0, range);
	if (rand < 2)
	{
		side = (Sides)rand;
	}
	return side;
}

Sides Tree::Chop(Sides side)
{
	Branch* temp = branches.front();
	branches.pop_front();
	temp->SetSide(RandomSide());
	branches.push_back(temp);
	UpdateBranchPos();
	return branches.front()->GetSide();
}

void Tree::UpdateBranchPos()
{
	sf::Vector2f pos = position;
	pos.y += 80.f;
	for (Branch* branch : branches)
	{
		pos.y -= branchOffsetY;
		branch->SetPosition(pos);
	}
}

void Tree::SetOrigin(Origins preset)
{
	// TODO:
}

void Tree::SetOrigin(const sf::Vector2f& newOrigin)
{
	// TODO:
}

void Tree::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	tree.setPosition(pos);
	UpdateBranchPos();
}

void Tree::Init()
{
	Release();
	
	tree.setTexture(RES_MGR_TEXTURE.Get(treeTexureId), true);
	Utils::SetOrigin(tree, Origins::BC);

	float originBranchX = tree.getLocalBounds().width * -0.5f;

	sf::Texture& branchTexure = RES_MGR_TEXTURE.Get(branchTextureId);
	float originBranchY = branchTexure.getSize().y;

	for (int i = 0; i < branchCount; ++i)
	{
		Branch* branch = new Branch();
		branch->SetTexture(branchTextureId);
		branch->SetOrigin({ originBranchX , originBranchY} );
		branches.push_back(branch);
	}
}

void Tree::Release()
{
	for (Branch* branch : branches)
	{
		delete branch;
	}
	branches.clear();
}

void Tree::Reset()
{
	for (Branch* branch : branches)
	{
		branch->Reset();
	}

	int noneCount = 2;
	int count = 0;

	for (Branch* branch : branches)
	{
		if (count < noneCount)
		{
			branch->SetSide(Sides::NONE);
		}
		else
		{
			branch->SetSide(RandomSide());
		}
		++count;
	}

	UpdateBranchPos();
}

void Tree::Update(float dt)
{
	for (Branch* branch : branches)
	{
		if (branch->GetActive())
		{
			branch->Update(dt);
		}
	}
}

void Tree::Draw(sf::RenderWindow& window)
{
	window.draw(tree);
	for (Branch* branch : branches)
	{
		if (branch->GetActive())
		{
			branch->Draw(window);
		}
	}
}
