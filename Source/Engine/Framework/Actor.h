#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"


namespace jojo
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const jojo::Transform& transform, const jojo::Model& model) : 
			m_transform{ transform },
			m_model{ model } 
		{}

		virtual void Update(float dt);
		virtual void Draw(jojo::Renderer& renderer);

		float GetRadius() { return m_model.GetRadius() * m_transform.scale; }
		virtual void OnCollision(Actor* other) {}
	

		
		class Scene* m_scene = nullptr;
		friend class Scene;

		jojo::Transform m_transform;
		std::string m_tag;
		float m_health;

	protected:
		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		jojo::Model m_model;
	};
}

