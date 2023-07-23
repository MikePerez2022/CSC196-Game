#include "Bullet.h"

void Bullet::Update(float dt)
{
	Actor::Update(dt);

	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());
}

void Bullet::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag)
	{
		//m_destroyed = true;
	}
}
