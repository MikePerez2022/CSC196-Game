#include "Enemy.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Bullet.h"
#include "SpaceGame.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		jojo::vec2 direction = m_transform.position - player->m_transform.position;

		m_transform.rotation = direction.Angle() * jojo::HalfPi;
	}

	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());

	if (m_fireTimer <= 0) {
		jojo::Transform transform{m_transform.position, 0, m_transform.scale};
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(Bullet{ 200, transform, jojo::g_modelManager.Get("ship.txt")});
		bullet->m_tag = "Enemy";
		m_scene->Add(std::move(bullet));

		m_fireTimer = 2.0f;
	}
}

void Enemy::OnCollision(Actor* other)
{
	//dynamic_cast<Player*>(other);

	if (other->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_destroyed = true;
	}
}
