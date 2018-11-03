#include "HookGun.h"
#include <iostream>
#include "rendering/Rendering.h"
#include "utility/VectorOperations.h"
#include "HookProjectile.h"
#include "game_objects/GameStateManager.h"

HookGun::HookGun() :
	_isHooked{false},
	_currentHook{nullptr},
	_observer{nullptr}
{
	_animationController.load("hook-gun", true);
	_animationController.setSize(sf::Vector2f{ 100.f, 100.f });

	attachChild(&_hookChain);
	_hookChain.setThickness(5.f);

	_rotationPointVisual.setRadius(5.f);
	_rotationPointVisual.setFillColor(sf::Color::Red);
	_rotationPointVisual.setOrigin(sf::Vector2f{ 2.5f, 2.5f });
}

void HookGun::setLookDirection(LookDirection value)
{
	switch (value)
	{
		case LookDirection::Left:
			_animationController.setInvertion(sf::Vector2f{ 1.f, 1.f });
			break;
		case LookDirection::Right:
			_animationController.setInvertion(sf::Vector2f{ -1.f, 1.f });
			break;
	}

	_lookDirection = value;
}

void HookGun::setUnnormalizedLookDirection(const sf::Vector2f& dir)
{
	_unnormalizedLookDirection = dir;

	// Rotate weapon
	switch (_lookDirection)
	{
		case LookDirection::Left:
		{
			_animationController.setOrigin( _rotationPoint_Left);
			float angle = Util::radianToDegree(VectorOperations::vectorAngle(dir, sf::Vector2f{ -1.f, 0.f }));
			angle *= dir.y > 0.f ? -1.f : 1.f;
			_animationController.setRotation(angle);
			break;
		}
		case LookDirection::Right:
		{
			_animationController.setOrigin(_rotationPoint_Right);
			float angle = Util::radianToDegree(VectorOperations::vectorAngle(dir, sf::Vector2f{ 1.f, 0.f }));
			angle *= dir.y < 0.f ? -1.f : 1.f;
			_animationController.setRotation(angle);
			break;
		}
	}
}

bool HookGun::isHooked() const
{
	return _isHooked;
}

void HookGun::shoot()
{
	if (_currentHook != nullptr)
	{
		return;
	}

	const sf::Vector2f shootVector = VectorOperations::normalize(_unnormalizedLookDirection) * 1e3f;

	_currentHook = dynamic_cast<HookProjectile*>(GameStateManager::instantiate(&HookProjectile{}));
	_currentHook->setLocalPosition(getGlobalPosition());
	_currentHook->attachProjectileObserver(this);
	_currentHook->shoot(shootVector);
}

void HookGun::attachHookGunObserver(HookGunObserver* observer)
{
	_observer = observer;
}

void HookGun::dettachHookGunObserver()
{
	_observer = nullptr;
}

void HookGun::update(float _dt)
{
	if (_currentHook != nullptr)
	{
		_hookChain.setStartPoint(getGlobalPosition());
		_hookChain.setEndPoint(_currentHook->getGlobalPosition());
	}

	if (isHooked())
	{
		_hookChain.setStartPoint(getGlobalPosition());
		_hookChain.setEndPoint(_currentHookPoint);
	}
}

void HookGun::draw()
{
	_animationController.draw();

	if (_currentHook != nullptr || _isHooked)
	{
		_hookChain.draw();
	}

	/*
	// Debug draw
	switch (_lookDirection)
	{
		case LookDirection::Left:
			_rotationPointVisual.setPosition(getGlobalPosition() + _rotationPoint_Left);
			break;
		case LookDirection::Right:
			_rotationPointVisual.setPosition(getGlobalPosition() + _rotationPoint_Right);
			break;
	}

	Rendering::draw(_rotationPointVisual);
	*/
}

void HookGun::onCollision(Collider * _this, Collider * _other)
{

}

GameObject * HookGun::clone()
{
	return new HookGun{};
}

void HookGun::setLocalPosition(const sf::Vector2f &_pos)
{
	GameObject::setLocalPosition(_pos);

	_animationController.setPosition(getGlobalPosition());
}

void HookGun::onProjectileCollision(const Projectile& projectile)
{
	_currentHookPoint = projectile.getGlobalPosition();
	_isHooked = true;
	_currentHook = nullptr;

	if (_observer)
	{
		_observer->onHook();
	}
}

void HookGun::onProjectileDestroy(const Projectile& projectile)
{
	_currentHook = nullptr;
}
