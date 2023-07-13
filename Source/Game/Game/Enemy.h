#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy() = default;
	Enemy(float speed, float turnRate, const jojo::Transform& transform, const jojo::Model& model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
};