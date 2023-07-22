#include "Actor.h"

namespace jojo
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1) 
		{
			m_lifespan -= jojo::g_time.GetDeltaTime();
			m_destroyed = (m_lifespan <= 0);
		}
	}
	void Actor::Draw(jojo::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}


}

