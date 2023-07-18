#include "Actor.h"

namespace jojo
{
	void Actor::Draw(jojo::Renderer& renderer)
	{
		m_model.Draw(renderer, m_transform);
	}
}

