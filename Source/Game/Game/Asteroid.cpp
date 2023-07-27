#include "Asteroid.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Bullet.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Core/Random.h"

void Asteroid::Update(float dt)
{
	Actor::Update(dt);

	float rotate = jojo::randomf(0.0f, 20.0f);

	m_transform.rotation += rotate * m_turnRate * jojo::g_time.GetDeltaTime();

	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * 1 * jojo::g_time.GetDeltaTime();
	m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());

}

void Asteroid::OnCollision(Actor* other)
{

	if (other->m_tag == "Player")
	{
		m_game->AddPoints(-50);
		m_destroyed = true;

		jojo::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = jojo::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = jojo::Color{ 200, 0, 0, 255 };
		jojo::Transform transform{ m_transform.position, 0, 6 };
		auto emitter = std::make_unique<jojo::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}