#include "MainCharacter.h"
#include "utility/FloatOperations.h"
#include "input/Input.h"
#include "physics/PhysicsEngine.h"

MainCharacter::MainCharacter():
	_isMoving {false}
{
	_animationController.load("dummy-character", true);
	_animationController.setSize(sf::Vector2f{ 100.f, 100.f });

	auto baseCol = createCollider(sf::Vector2f{}, sf::Vector2f{ 50.f, 50.f });
	auto rb = createRigidBody();
	rb->setGravity(true);
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

void MainCharacter::handleMovement(float dt)
{
	const float speed = 100.f;

	float dx = 0.f;
	dx += Input::getKey(Input::D) ? speed : 0.f;
	dx += Input::getKey(Input::A) ? -speed : 0.f;

	if (FloatOperations::compare(dx, 0.f) != 0)
	{
		// Start move
		if (!_isMoving)
		{
			_isMoving = true;
			_animationController.setTrigger("start-walk", true);
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

	move(sf::Vector2f{ dx, 0.f } * dt);
}

void MainCharacter::handleJumping(float dt)
{
	if (Input::getKeyDown(Input::W))
	{
		getRigidBody()->setVelocity(sf::Vector2f{ 0.f, -300.f });
	}
}

