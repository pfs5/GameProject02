#pragma once
#include "game_objects/GameObject.h"
#include "animation/AnimationController.h"
#include "HookGun.h"

class HookGun;

class MainCharacter : public GameObject, HookGunObserver
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

// HookGunObserver
public:
	virtual void onHook() override;

// Getters and setters
public:
	void attachHookGun(HookGun* gun);

private:
	HookGun* _hookGun;

	AnimationController _animationController;
	bool _isMoving;
	
	// Swinging
	bool _isSwinging;
	sf::Vector2f _swingingVelocity;

private:
	void handleMovement(float dt);
	void handleJumping(float dt);
	void handleAiming(float dt);
	void handleShooting(float dt);
	void handleSwinging(float dt);

#pragma region Parameters
private:
	const float MOVEMENT_SPEED = 300.f;
	const float JUMP_SPEED = 8e2f;
	const float ADDITIONAL_GRAVITY = 1e3f;
#pragma endregion
};
