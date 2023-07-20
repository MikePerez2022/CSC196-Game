#pragma once
#include "..\Engine\Framework\Actor.h"

class Player : public jojo::Actor
{
public:
	Player() = default;
	Player(float speed, float turnRate, const jojo::Transform& transform, const jojo::Model& model) : 
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate } 
	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
};