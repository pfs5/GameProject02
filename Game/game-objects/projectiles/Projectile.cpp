#include "Projectile.h"

void Projectile::attachProjectileObserver(ProjectileObserver* observer)
{
	_projectileObservers.push_back(observer);
}

void Projectile::dettachProjectileObserver(ProjectileObserver* observer)
{
	_projectileObservers.erase(std::remove(_projectileObservers.begin(), _projectileObservers.end(), observer), _projectileObservers.end());
}

void Projectile::setLocalPosition(const sf::Vector2f &_pos)
{
	GameObject::setLocalPosition(_pos);
}

void Projectile::onCollision(Collider * _this, Collider * _other)
{
	for (ProjectileObserver* o : _projectileObservers)
	{
		o->onProjectileCollision(*this);
	}
}