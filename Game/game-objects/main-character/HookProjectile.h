#pragma once
#include "../projectiles/Projectile.h"

class HookProjectile : public Projectile
{
public:
	HookProjectile();

	// Projectile
public:
	virtual void setLocalPosition(const sf::Vector2f &_pos) override;
	virtual void shoot(const sf::Vector2f& shootVector) override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * clone() override;

private:
	sf::CircleShape _visual;

};