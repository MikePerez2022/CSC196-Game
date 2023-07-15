#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{
	float rotate = 0;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * jojo::g_time.GetDeltaTime();


	float thrust = 0;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());
}

