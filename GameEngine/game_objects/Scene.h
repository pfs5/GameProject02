#pragma once
#include "GameState.h"
#include <vector>
#include "Map.h"

class Scene : public GameState
{
public:
	Scene();
	~Scene();

// GameState
public:
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * gameObject) override;
	virtual void destroyObject(GameObject * gameObject) override;

protected:
	void setupDefaultCamera();
	void addGameObjectToState(GameObject* gameObject, unsigned int layer = 0);
	void setCurrentMap(Map* map);

private:
	std::vector<std::vector<GameObject*>> _gameObjects;
	Map* _map;
};
