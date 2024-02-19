#pragma once
#include "GameObject.h"
class UiTimeBar : public GameObject
{
protected:
	sf::RectangleShape shape;

	sf::Vector2f maxSize;
	sf::Vector2f currentSize;

public:
	UiTimeBar(const std::string& name);
	virtual ~UiTimeBar() = default;

	void Reset() override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetFlipX(bool filp) override;
	void SetFlipY(bool filp) override;

	void Draw(sf::RenderWindow& window) override;

	void Set(const sf::Vector2f& max, const sf::Color& color);

	float GetValue() const { return currentSize.x / maxSize.x; }
	void SetValue(float value);
};

