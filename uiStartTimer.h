#pragma once
#include "TextGo.h"
class uiStartTimer : public TextGo
{
protected:
	float duration;
	float timer;
	int ceilSecond;

public:
	uiStartTimer(const std::string& name = "");
	virtual ~uiStartTimer() = default;

	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Reset() override;

	inline void SetDuration(float asSecond) { duration = asSecond; }
	inline float GetDuration() const { return duration; }

};

