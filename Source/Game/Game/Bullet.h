#pragma once
#include "..\Engine\Framework\Actor.h"

class Bullet : public jojo::Actor
{
public:
	Bullet() = default;
	Bullet(float speed, const jojo::Transform& transform, const jojo::Model& model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
};
