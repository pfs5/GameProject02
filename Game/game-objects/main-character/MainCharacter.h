#pragma once
#include "game_objects/GameObject.h"
#include "animation/AnimationController.h"

class MainCharacter : public GameObject
{
public:
	MainCharacter();
	~MainCharacter();

	// GameObject
public:
	void update(float _dt) override;
	void draw() override;
	void onCollision(Collider* _this, Collider* _other) override;
	GameObject* clone() override;

	void setLocalPosition(const sf::Vector2f& _pos) override;

private:
	AnimationController _animationController;
	bool _isMoving;

private:
	void handleMovement(float dt);
	void handleJumping(float dt);
};
