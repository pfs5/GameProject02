#pragma once
#include "game_objects/GameObject.h"
#include "animation/AnimationController.h"
#include "ui/UILine.h"
#include "../projectiles/Projectile.h"
#include "HookProjectile.h"

class HookGunObserver
{
public:
	virtual void onHook() = 0;
};

class HookGun : public GameObject, public ProjectileObserver
{
public:
	enum class LookDirection
	{
		Left,
		Right
	};
	
public:
	HookGun();

public:
	void setLookDirection(LookDirection value);		// #TODO replace this with vector direction
	void setUnnormalizedLookDirection(const sf::Vector2f& dir);
	bool isHooked() const;

	void shoot();
	void attachHookGunObserver(HookGunObserver* observer);
	void dettachHookGunObserver();

	// GameObject
public:
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setLocalPosition(const sf::Vector2f &_pos) override;

// ProjectileObserver
public:
	virtual void onProjectileCollision(const Projectile& projectile) override;
	virtual void onProjectileDestroy(const Projectile& projectile) override;

private:
	const sf::Vector2f _rotationPoint_Left = sf::Vector2f{ -1.f, -2.f};
	const sf::Vector2f _rotationPoint_Right = sf::Vector2f{ -5.f, -2.f };

	// Debug visuals ---
	sf::CircleShape _rotationPointVisual;
	// -----------------

	AnimationController _animationController;
	UILine _hookChain;

	LookDirection _lookDirection;
	sf::Vector2f _unnormalizedLookDirection;

	bool _isHooked;
	HookProjectile* _currentHook;
	sf::Vector2f _currentHookPoint;

	HookGunObserver* _observer;
};
