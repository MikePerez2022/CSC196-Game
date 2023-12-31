#pragma once
#include "..\Engine\Framework\Actor.h"
#include "Renderer/ModelManager.h"

class Enemy : public jojo::Actor
{
public:
	Enemy() = default;
	Enemy(float speed, float turnRate, const jojo::Transform& transform, const std::shared_ptr<jojo::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;	
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};