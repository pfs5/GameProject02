#pragma once
#include "game_objects/GameObject.h"
class Projectile;

class ProjectileObserver
{
public:
	virtual void onProjectileCollision(const Projectile& projectile) = 0;
	virtual void onProjectileDestroy(const Projectile& projectile) = 0;
};

class Projectile : public GameObject
{
public:
	virtual ~Projectile() = default;

	void attachProjectileObserver(ProjectileObserver* observer);
	void dettachProjectileObserver(ProjectileObserver* observer);

	virtual void shoot(const sf::Vector2f& shootVector) = 0;

	// GameObject
public:
	virtual void setLocalPosition(const sf::Vector2f &_pos) override;
	virtual void onCollision(Collider * _this, Collider * _other) override;

protected:
	std::vector<ProjectileObserver*> _projectileObservers;
};