#include "HookProjectile.h"
#include "rendering/Rendering.h"
#include "../GameEngine/physics/Collider.h"
#include "game_objects/GameStateManager.h"

HookProjectile::HookProjectile()
{
	float radius = 10.f;
	_visual.setRadius(radius);
	_visual.setOrigin(radius, radius);
	_visual.setFillColor(sf::Color::Red);

	auto mainCol = createCollider(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ radius * 2.f, radius * 2.f });

	auto rb = createRigidBody();
	rb->setGravity(false);
}

void HookProjectile::setLocalPosition(const sf::Vector2f &_pos)
{
	Projectile::setLocalPosition(_pos);

	_visual.setPosition(getGlobalPosition());
}

void HookProjectile::shoot(const sf::Vector2f& shootVector)
{
	getRigidBody()->setVelocity(shootVector);
}

void HookProjectile::onCollision(Collider * _this, Collider * _other)
{
	if (_other->getGameObject()->getObjectTag() == "terrain")
	{
		for (auto o : _projectileObservers)
		{
			o->onProjectileCollision(*this);
		}
		GameStateManager::destroyObject(this);
	}
}

void HookProjectile::update(float _dt)
{

}

void HookProjectile::draw()
{
	Rendering::draw(_visual);
}

GameObject * HookProjectile::clone()
{
	return new HookProjectile();
}