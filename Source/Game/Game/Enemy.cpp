#include "Enemy.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());
}