#include "Scene.h"
#include "GameStateManager.h"
#include "../rendering/Camera.h"
#include "../rendering/Rendering.h"
#include "../physics/PhysicsEngine.h"

Scene::Scene()
{
	for (int i = 0; i < GameStateManager::objectLayers; ++i)
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}
}

Scene::~Scene()
{
	for (auto layer : _gameObjects)
	{
		for (GameObject * g : layer)
		{
			delete g;
		}
	}
}

void Scene::update(float dt)
{
	// Map
	if (_map != nullptr)
	{
		_map->update(dt);
	}

	// Update game objects
	for (int i = _gameObjects.size() - 1; i >= 0; --i)
	{
		for (GameObject * g : _gameObjects[i])
		{
			if (g->isActive())
			{
				g->update(dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(dt);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = _gameObjects.size() - 1; i >= 0; --i)
	{
		while (newObj = GameStateManager::popNewGameObject(i))
		{
			_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject())
	{
		for (auto &layer : _gameObjects)
		{
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}
}

void Scene::draw()
{
	// Map
	if (_map != nullptr)
	{
		_map->draw();
	}

	// Draw game objects
	for (int i = _gameObjects.size() - 1; i >= 0; --i)
	{
		for (GameObject * g : _gameObjects[i])
		{
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * Scene::instantiateObject(GameObject * gameObject)
{
	GameObject * newInstance = gameObject->clone();

	return newInstance;
}

void Scene::destroyObject(GameObject * gameObject)
{
	gameObject->setActive(false);
}

void Scene::addGameObjectToState(GameObject* gameObject, unsigned int layer /*= 0*/)
{
	while (_gameObjects.size() < layer + 1)
	{
		_gameObjects.emplace_back(std::vector<GameObject*>());
	}

	_gameObjects[layer].push_back(gameObject);
}

void Scene::setCurrentMap(Map* map)
{
	_map = map;
}

void Scene::setupDefaultCamera()
{
	Camera* defaultCamera = Rendering::createCamera();
	defaultCamera->setView(Display::getWindow().getDefaultView());

}