#include "Actor.h"

void Actor::Draw(jojo::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform);
}
