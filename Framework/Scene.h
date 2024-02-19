#pragma once

class GameObject;

class Scene
{
protected:
	SceneIds id;
	std::list<GameObject*> gameObjects;

	ResourceMgr<sf::Texture>& texResMgr;
	ResourceMgr<sf::Font>& fontResMgr;
	ResourceMgr<sf::SoundBuffer>& soundResMgr;

	float timeScale = 1.f;
public:
	Scene(SceneIds id);

	virtual ~Scene() = default;

	virtual void Init() = 0;
	virtual void Release();

	virtual void Enter();
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual GameObject* FindGo(const std::string& name);
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list);

	virtual GameObject* AddGo(GameObject* obj);
	virtual void RemoveGo(GameObject* obj);

	inline SceneIds GetId() const { return id; }
	inline float GetTimeScale() const { return timeScale; }
	inline void SetTimeScale(float timeScale) { this->timeScale = timeScale; }

	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene& operator=(Scene&&) = delete;
};

