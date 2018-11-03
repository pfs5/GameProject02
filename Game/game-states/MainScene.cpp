#include "MainScene.h"
#include "resource_management/ResourceManager.h"
#include "../game-objects/main-character/MainCharacter.h"
#include "../game-objects/main-character/HookGun.h"

MainScene::MainScene()
{
	setupDefaultCamera();

	// Map
	Map* map = new Map();
	MapLayer mapLayer;
	mapLayer.texture = ResourceManager::getTextureStatic("map-1");
	mapLayer.speedCoefficient = 0.f;
	map->setMapLayer(mapLayer, 0);

	map->loadColliders("map-1-colliders");

	setCurrentMap(map);

	// Map character
	auto mainChar = new MainCharacter{};
	mainChar->setLocalPosition(sf::Vector2f{ 500.f, 500.f });
	addGameObjectToState(mainChar);

	auto hookGun = new HookGun{};
	addGameObjectToState(hookGun);
	mainChar->attachHookGun(hookGun);
}

MainScene::~MainScene()
{

}

