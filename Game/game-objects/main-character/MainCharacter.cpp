#include "MainCharacter.h"
#include "utility/FloatOperations.h"
#include "input/Input.h"
#include "physics/PhysicsEngine.h"
#include "HookGun.h"
#include <iostream>
#include "rendering/Rendering.h"
#include "utility/VectorOperations.h"

MainCharacter::MainCharacter():
	_isMoving {false},
	_isSwinging{false}
{
	_animationController.load("dummy-character", true);
	_animationController.setSize(sf::Vector2f{ 100.f, 100.f });

	auto baseCol = createCollider(sf::Vector2f{}, sf::Vector2f{ 50.f, 50.f });
	auto rb = createRigidBody();
	rb->setGravity(true);
	rb->setAcceleration(sf::Vector2f{ 0.f, ADDITIONAL_GRAVITY });
	baseCol->setTrigger(false, rb);
}

MainCharacter::~MainCharacter()
{

}

void MainCharacter::update(float _dt)
{
	_animationController.update(_dt);

	handleMovement(_dt);
	handleJumping(_dt);
	handleAiming(_dt);
	handleShooting(_dt);
	handleSwinging(_dt);
}

void MainCharacter::draw()
{
	_animationController.draw();
}

void MainCharacter::onCollision(Collider* _this, Collider* _other)
{

}

GameObject* MainCharacter::clone()
{
	return new MainCharacter{};
}

void MainCharacter::setLocalPosition(const sf::Vector2f& _pos)
{
	GameObject::setLocalPosition(_pos);

	_animationController.setPosition(getGlobalPosition());
}

void MainCharacter::onHook()
{
	_isSwinging = true;

	getRigidBody()->setGravity(false);
	getRigidBody()->setAcceleration(sf::Vector2f{ 0.f, 0.f });
	getRigidBody()->setVelocity(sf::Vector2f{ 0.f, 0.f });
}

void MainCharacter::attachHookGun(HookGun* gun)
{
	_hookGun = gun;
	attachChild(_hookGun);
	_hookGun->attachHookGunObserver(this);
}

void MainCharacter::handleMovement(float dt)
{
	if(_isSwinging)
	{
		return;
	}

	float dx = 0.f;
	dx += Input::getKey(Input::D) ? MOVEMENT_SPEED : 0.f;
	dx += Input::getKey(Input::A) ? -MOVEMENT_SPEED : 0.f;

	if (FloatOperations::compare(dx, 0.f) != 0)
	{
		// Start move
		if (!_isMoving)
		{
			_isMoving = true;
			_animationController.setTrigger("start-walk", true);
		}
	
		if (_hookGun != nullptr)
		{
			_hookGun->setLookDirection(dx > 0.f ? HookGun::LookDirection::Right : HookGun::LookDirection::Left);
		}
	}
	else
	{
		// Stop move
		if (_isMoving)
		{
			_isMoving = false;
			_animationController.setTrigger("stop-walk", true);
		}
	}

	auto velocity = getRigidBody()->getVelocity();
	velocity.x = dx;
	getRigidBody()->setVelocity(velocity);
}

void MainCharacter::handleJumping(float dt)
{
	if (_isSwinging)
	{
		return;
	}

	if (Input::getKeyDown(Input::W))
	{
		getRigidBody()->setVelocity(sf::Vector2f{ 0.f, -JUMP_SPEED });
	}
}

void MainCharacter::handleAiming(float dt)
{
	auto mousePos = static_cast<sf::Vector2f>(Input::getMousePosition());
	auto screenPos = Display::worldToScreenPosition(getLocalPosition());

	sf::Vector2f aimDirection = mousePos - screenPos;
	if (_hookGun != nullptr)
	{
		_hookGun->setUnnormalizedLookDirection(aimDirection);
	}
}

void MainCharacter::handleShooting(float dt)
{
	if (Input::getKeyDown(Input::SPACE))
	{
		if (_hookGun != nullptr)
		{
			_hookGun->shoot();
		}
	}
}

void MainCharacter::handleSwinging(float dt)
{
	if (!_isSwinging)
	{
		return;
	}


}
