#pragma once

#include "ActorComponent.h"

struct Vector2D
{
	int x;
	int y;
};

class Cords : public ActorComponent
{
	Vector2D position;

public:
	Cords(Actor* owner, const Vector2D& position) : ActorComponent(owner)
	{
		this->position = position;
	}

	Vector2D getPosition() const
	{
		return position;
	}

	void setPosition(const Vector2D& position)
	{
		this->position = position;
	}

	bool isNear(const Cords& object) const
	{
		int dx = position.x - object.position.x;
		int dy = position.y - object.position.y;

		return dx * dx + dy * dy <= 1;
	}
};